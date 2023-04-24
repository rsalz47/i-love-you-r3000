#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "../../src/mem/memory.h"
#include "../../src/mem/cache.h"
#include "../../src/pipeline/fetch_stage.h"
#include "../../src/pipeline/decode_stage.h"
#include "../../src/pipeline/execute_stage.h"
#include "../../src/pipeline/memory_stage.h"
#include "../../src/pipeline/writeback_stage.h"
#include "../../src/asm/assembler.cpp"
#include <sstream>


#include <QString>
#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <QProcess>
#include <QThread>
#include <QDir>


uint32_t CLK = 0;
uint32_t PROGRAM_COUNTER = 0;
Memory main_mem(3);
Cache main_cache(&main_mem, 3);
uint32_t registers[32];
volatile int clock_cycle = 0;

WritebackStage wb_stage(registers,&PROGRAM_COUNTER);
MemoryStage mem_stage(wb_stage, &main_cache);
ExecuteStage execute_stage(mem_stage);
DecodeStage decode_stage(execute_stage, registers);
FetchStage fetch_stage(&PROGRAM_COUNTER, &main_cache, decode_stage);

void enable_cache(FetchStage& fetch_stage, MemoryStage& memory_stage, Cache* cache) {
    fetch_stage.set_mem_sys(cache);
    memory_stage.set_mem_sys(cache);
}

void disable_cache(FetchStage& fetch_stage, MemoryStage& memory_stage, Memory* memory) {
    fetch_stage.set_mem_sys(memory);
    memory_stage.set_mem_sys(memory);
}



void refreshViews(Ui::MainWindow *ui){
    // update cache view
    ui->cacheView->setColumnCount(8);
    ui->cacheView->setRowCount(16);
    QStringList cacheHeaders;
        cacheHeaders<< "Tag" << "Index" << "Word1(00)" << "Word2(01)" << "Word3(10)" << "Word4(11)" << "Dirty" << "Valid";
    ui->cacheView->setHorizontalHeaderLabels(cacheHeaders);

    for (int i = 0; i < 16; i++){
        for(int j = 0; j<8; j++){
            ui->cacheView->setItem(i,j,new QTableWidgetItem(QString::number(main_cache.cache[i][j])));
        }
    }

    // update memoryView
    ui->memoryView->setColumnCount(WORDS_PER_LINE);
    ui->memoryView->setRowCount(NUM_LINES);
    QStringList memoryHeaders;
        memoryHeaders << "Word1(00)" << "Word2(01)" << "Word3(10)" << "Word4(11)";
    ui->memoryView->setHorizontalHeaderLabels(memoryHeaders);
    for (int i = 0; i < NUM_LINES; i++){
        for(int j = 0; j<WORDS_PER_LINE; j++){
            ui->memoryView->setItem(i,j,new QTableWidgetItem(QString::number(main_mem.memory[i][j])));
        }
    }

    // update registerView
    ui->registerView->setColumnCount(2);
    QStringList registerHeaders;
        registerHeaders << "Register" << "Data";
    ui->registerView->setHorizontalHeaderLabels(registerHeaders);
    ui->registerView->setRowCount(32);
    for (int i = 0; i < 32; i++) {
           ui->registerView->setItem(i,0,new QTableWidgetItem(QString::number(registers[i])));
        }


    // update pipeline view
    ui->fetchView->setItem(0,0,new QTableWidgetItem(QString::number(fetch_stage.blocked)));
    ui->decodeView->setItem(0,0,new QTableWidgetItem(QString::number(decode_stage.blocked)));
    ui->executeView->setItem(0,0,new QTableWidgetItem(QString::number(execute_stage.blocked)));
    ui->memoryViewPipeline->setItem(0,0,new QTableWidgetItem(QString::number(mem_stage.blocked)));
    ui->writebackView->setItem(0,0,new QTableWidgetItem(QString::number(wb_stage.noop)));

    //update statistics
    ui->label_16->setText(QString::number(main_cache.num_cache_misses));
    ui->label_18->setText(QString::number(PROGRAM_COUNTER));
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->instructionsView->horizontalHeader()->setStretchLastSection(true);
    refreshViews(ui);
}



MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{

    if (wb_stage.exit) {
        std::cout << "program end" << std::endl; // in gui code, just return
        //update label
        ui->runningStatus->setText("halt");
        return;
    }
    wb_stage.tick();
    ui->runningStatus->setText("running");
    if (wb_stage.exit || wb_stage.squashed) {
        std::cout << "!! squashing previous stages" << std::endl;
        mem_stage.reset();
        execute_stage.reset();
        decode_stage.reset();
        fetch_stage.reset();
    }
    else {
        mem_stage.tick();
        execute_stage.tick();
        decode_stage.tick();
        fetch_stage.tick();
    }
    clock_cycle +=1;
    ui->clockCycles->setText(QString::number(clock_cycle));
    refreshViews(ui);
    return;
}


void MainWindow::on_loadIntructionFile_clicked()
{
// todo rework loading files into the gui. use assemble instead of build_instruction

    QString asmFileName = QFileDialog::getOpenFileName(this,tr("Open .ily file"),"/home/$USER",tr("Image Files (*.ily)"));
    std::cout << asmFileName.toStdString() << std::endl;
    if (asmFileName.isEmpty()){
        return;
    }
    QFile asmFile(asmFileName);
    if (!asmFile.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    // This creates the binary file with a .r3k extension
    QProcess *proc = new QProcess();

    //This is OS specific/ user specific right now // needs to be changed for other systems
    QString program = "/home/nandu/Documents/i-love-you-r3000/src/asm/a.out";

    proc->start(program,QStringList() << asmFileName);
    proc->waitForFinished();
    QString result=proc->readAllStandardOutput();
    std::cout << QString(result).toStdString() << std::endl;

    // This is the binary file or .r3k file opening
    QFileInfo asmFileInfo(asmFileName);
    //Do binFileName manipulation here
    QString binFileName = asmFileInfo.path() +"/" + asmFileInfo.baseName()+ ".r3k";
    std::cout << binFileName.toStdString() << std::endl;

    QFile binFile(binFileName);
    if (!binFile.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

// assuming asmFile and binFile have the same number of the files
    QTextStream inAsm(&asmFile);
    QTextStream inBin(&binFile);
    int i = 0;
    while (!inAsm.atEnd()) {
        QString asmLine = inAsm.readLine();
        QString binLine = inBin.readLine();
        ui->instructionsView->insertRow(ui->instructionsView->rowCount());
        ui->instructionsView->setItem(ui->instructionsView->rowCount()-1,0,new QTableWidgetItem(asmLine));
        QString binary_instruction = binLine;
        ui->instructionsView->setItem(ui->instructionsView->rowCount()-1,1,new QTableWidgetItem(QString("%1").arg(binLine.toUInt(),0,2)));
        main_mem.memory[(i/WORDS_PER_LINE) % (WORDS_PER_LINE * NUM_LINES)][i% WORDS_PER_LINE] = binary_instruction.toUInt();
        i++;
    }
    clock_cycle = 0;
    refreshViews(ui);
    return;
}



void MainWindow::on_jumpToMemLoc_clicked()
{
    int addr_row = (ui->inputForJumpTo->item(0,0)->data(0).toInt() /WORDS_PER_LINE) % (WORDS_PER_LINE * NUM_LINES);
    int addr_col= (ui->inputForJumpTo->item(0,0)->data(0).toInt() % (WORDS_PER_LINE));
    ui->memoryView->scrollToItem(ui->memoryView->item(addr_row, addr_col));
    ui->memoryView->item(addr_row, addr_col)->setBackground(Qt::blue);

}


void MainWindow::on_runProgram_clicked()
{
    while(!wb_stage.exit){
        ui->runningStatus->setText("running");
        on_pushButton_clicked();
    }
    std::cout << "program end" << std::endl; // in gui code, just return
    //update label
    ui->runningStatus->setText("halt");
    return;

}


void MainWindow::on_pipeLineEnableCheckBox_stateChanged(int arg1)
{
    if (arg1 > 0){
        fetch_stage.enable_pipeline();
        return;
    }
    else{
        fetch_stage.disable_pipeline();
    }
    return;
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if (arg1 > 0){
        enable_cache(fetch_stage, mem_stage, &main_cache); // enable cache
        return;
    }
    else{
        disable_cache(fetch_stage, mem_stage, &main_mem); // disable cache

    }
    return;
}
