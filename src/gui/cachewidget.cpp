#include "cachewidget.h"
#include <QHeaderView>

CacheWidget::CacheWidget(QWidget *parent) :
    QTableWidget(parent)
{
    setColumnCount(5); //for now put the data of a line in on column, may separate them by adding offset columns
    QStringList headers;
    headers << "Tag" << "Index" << "Dirty" << "Valid" << "Data";
    setHorizontalHeaderLabels(headers);
    horizontalHeader()->setStretchLastSection(true);

}
