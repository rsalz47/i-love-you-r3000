#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include "../asm/assembler.h"
#include <string>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loadAssembButton_clicked()
{
   QString filename= QFileDialog::getOpenFileName(this, "Choose File");

   if(filename.isEmpty())
       return;

   loadAssembly(filename);
}

// cunrrently load src/asm/in/bar.ily
void MainWindow::on_quicLoadButton_clicked()
{
    QString filename = "../src/asm/in/bar.ily";
    loadAssembly(filename);
}

void MainWindow::loadAssembly(QString filename) {
    ui->codePanel->setRowCount(0);
    QFile file(filename);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        return;
    QTextStream in(&file);
    unsigned long address = 0;

    // load the assembly file and convert it to binary by default
    while (!in.atEnd()) {
        QString line = in.readLine();
        std::string line_string = line.toStdString();
        std::cout << line_string << std::endl;
        unsigned long binary = build_instruction(line_string);
        QTableWidgetItem *assemInstruction = new QTableWidgetItem(line);
        QTableWidgetItem *binaryInstruction = new QTableWidgetItem(QString("%1").arg(binary,32,2,QLatin1Char('0')));
        QTableWidgetItem *addressItem = new QTableWidgetItem(QString("%1").arg(address,3,16,QLatin1Char('0')));
        //make items nonselectable
        binaryInstruction -> setFlags(binaryInstruction->flags() & ~Qt::ItemIsSelectable & ~Qt::ItemIsEditable);
        ui->codePanel->setRowCount(ui->codePanel->rowCount() + 1);
        ui->codePanel->setItem(ui->codePanel->rowCount() - 1, 1, assemInstruction);
        ui->codePanel->setItem(ui->codePanel->rowCount() - 1, 2, binaryInstruction);
        ui->codePanel->setItem(ui->codePanel->rowCount() - 1, 0, addressItem);
        address += 4;
    }
    file.close();
}
