#ifndef CODEWIDGET_H
#define CODEWIDGET_H

#include <QTableWidget>

class CodeWidget : public QTableWidget
{
public:
    CodeWidget(QWidget *parent = 0);

private:
    // convert the string containing number with base soucceBase to targetBase
    QString convertQString(QString s, int sourceBase, int targetBase);
};

#endif // CODEWIDGET_H
