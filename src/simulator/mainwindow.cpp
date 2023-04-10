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


#include <QString>
#include <QFileDialog>
#include <QDebug>
#include <QFile>
 #include <QProcess>


uint32_t CLK = 0;
uint32_t PROGRAM_COUNTER = 0;
Memory main_mem(2);
Cache main_cache(&main_mem, 1);
uint32_t registers[32];
volatile int clock_cycle = 0;

WritebackStage wb_stage(registers,&PROGRAM_COUNTER);
MemoryStage mem_stage(wb_stage, &main_cache);
ExecuteStage execute_stage(mem_stage);
DecodeStage decode_stage(execute_stage, registers);
FetchStage fetch_stage(&PROGRAM_COUNTER, &main_cache, decode_stage);




void resetViews(Ui::MainWindow *ui){
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

}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->instructionsView->horizontalHeader()->setStretchLastSection(true);
    resetViews(ui);
}



MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{

    wb_stage.tick();
    mem_stage.tick();
    execute_stage.tick();
    decode_stage.tick();
    fetch_stage.tick();
    clock_cycle +=1;
    ui->clockCycles->setText(QString::number(clock_cycle));
    resetViews(ui);

    return;
}


void MainWindow::on_loadIntructionFile_clicked()
{


    QString asmFile = QFileDialog::getOpenFileName(this,tr("Open .ily file"),"/home/$USER",tr("Image Files (*.ily)"));
    if (asmFile.isEmpty()){
        return;
    }
    QFile file(asmFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QTextStream in(&file);
    int i = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();
        ui->instructionsView->insertRow(ui->instructionsView->rowCount());
        ui->instructionsView->setItem(ui->instructionsView->rowCount()-1,0,new QTableWidgetItem(line));
        unsigned long built_instruction = build_instruction(line.toStdString());
        QString binary_instruction;
        binary_instruction = QString("%1").arg(built_instruction, 0, 2);
        ui->instructionsView->setItem(ui->instructionsView->rowCount()-1,1,new QTableWidgetItem(binary_instruction));
        main_mem.memory[(i/WORDS_PER_LINE) % (WORDS_PER_LINE * NUM_LINES)][i% WORDS_PER_LINE] = built_instruction;
        i++;
    }
    clock_cycle = 0;
    resetViews(ui);
    return;
}

