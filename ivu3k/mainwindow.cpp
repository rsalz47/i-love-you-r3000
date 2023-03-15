#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include "asm/assembler.h"
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

   QFile file(filename);

   if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
       return;

   ui->codePanel->setRowCount(0);
   QTextStream in(&file);

   while (!in.atEnd()) {
       QString line = in.readLine();
       std::string line_string = line.toStdString();
       std::cout << line_string << std::endl;
       unsigned long binary = build_instruction(line_string);
       QTableWidgetItem *assemInstruction = new QTableWidgetItem(line);
       QTableWidgetItem *binaryInstruction = new QTableWidgetItem(QString("0x%1").arg(binary,8,16,QLatin1Char('0')));
       ui->codePanel->setRowCount(ui->codePanel->rowCount() + 1);
       ui->codePanel->setItem(ui->codePanel->rowCount() - 1, 1, assemInstruction);
       ui->codePanel->setItem(ui->codePanel->rowCount() - 1, 2, binaryInstruction);
   }
   file.close();
}

