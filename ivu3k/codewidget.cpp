#include "codewidget.h"
#include <QHeaderView>

CodeWidget::CodeWidget(QWidget *parent) :
    QTableWidget(parent)
{
    setColumnCount(3);
    QStringList headers;
    headers << "address" << "assembly" << "binary";
    setHorizontalHeaderLabels(headers);
    //horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    horizontalHeader()->setStretchLastSection(true);

    auto header = horizontalHeader();
    // toggle between binary and hex when clicking header
    connect(header, &QHeaderView::sectionClicked, [this](int logicalIndex){
        if (logicalIndex != 2) {
            return;
        }
        QString text = horizontalHeaderItem(logicalIndex)->text();
        bool binary = true;
        if (QString::compare(text, "binary", Qt::CaseInsensitive)) {
            //header is "hex"
            binary = false;
            horizontalHeaderItem(2)->setText("binary");
        } else {
            horizontalHeaderItem(2)->setText("hexadecimal");
        }
        for (int i = 0; i < rowCount(); i++) {
            QString current = item(i, 2)->text();
            QString newValue;
            if (binary) {
                newValue = convertQString(current, 2, 16).rightJustified(8,'0');
            } else {
                newValue = convertQString(current, 16, 2).rightJustified(32, '0');
            }
            QTableWidgetItem *newItem = new QTableWidgetItem(newValue);
            // set non-editable and non-selectable
            newItem -> setFlags(newItem ->flags() & ~Qt::ItemIsSelectable & ~Qt::ItemIsEditable);
            setItem(i, 2, newItem);
        }
    });
}

QString CodeWidget::convertQString(QString s, int sourceBase, int targetBase) {
    bool fOK;
    long long value = s.toLongLong(&fOK, sourceBase);
    return QString::number(value, targetBase);
}
