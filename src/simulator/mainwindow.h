#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_loadIntructionFile_clicked();

    void on_jumpToMemLoc_clicked();

    void on_runProgram_clicked();

    void on_pipeLineEnableCheckBox_stateChanged(int arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_resetSimulatorButton_clicked();

    void on_data_cacheCheckbox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
