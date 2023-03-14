#include "registerswidget.h"
#include <QHeaderView>
RegistersWidget::RegistersWidget(QWidget *parent):
    QTableWidget(parent)
{
    setColumnCount(2);
    QStringList headers;
    headers << "register" << "value";
    setHorizontalHeaderLabels(headers);
    setRowCount(32);
    verticalHeader()->setVisible(false);
    for (int i = 0; i < 32; i++) {
        QTableWidgetItem *registerName =
            new QTableWidgetItem(QString("r%1").arg(i));
        setItem(i, 0, registerName);
    }
}
