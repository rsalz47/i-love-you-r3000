#include "codewidget.h"
#include <QHeaderView>

CodeWidget::CodeWidget(QWidget *parent) :
    QTableWidget(parent)
{
    setColumnCount(3);
    QStringList headers;
    headers << "address" << "assembly" << "hexadecimal";
    setHorizontalHeaderLabels(headers);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
