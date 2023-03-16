#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class RegistersWidget;
class CodeWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadAssembButton_clicked();

    void on_quicLoadButton_clicked();

private:
    Ui::MainWindow *ui;

    void loadAssembly(QString filename);
};
#endif // MAINWINDOW_H
