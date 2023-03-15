#include "dramwidget.h"
#include <QHeaderView>

DRAMWidget::DRAMWidget(QWidget *parent):
    QTableWidget(parent)
{
    setColumnCount(2);
    QStringList headers;
    headers << "address" << "data";
    setHorizontalHeaderLabels(headers);
    horizontalHeader()->setStretchLastSection(true);
}
