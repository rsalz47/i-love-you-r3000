#include "dramwidget.h"
#include <QHeaderView>

DRAMWidget::DRAMWidget(QWidget *parent):
    QTableWidget(parent)
{
    setColumnCount(2);
    QStringList headers;
    headers << "Address" << "Data";
    setHorizontalHeaderLabels(headers);
    horizontalHeader()->setStretchLastSection(true);
}
