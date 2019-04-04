#include "tablewidget.h"
#include <QTableView>
#include <QHeaderView>
#include <QGridLayout>
#include <QMessageBox>

TableWidget::TableWidget(QWidget *parent, const std::vector<std::vector<char>> *matrix, const QSize& size, const QPoint& pos) : QWidget(parent)
{
    if(!matrix) {
        QMessageBox::critical(
            this,
            tr("Error"),
            tr("Richiesta di stampa di un oggetto nullo")
            );
        exit(0);
    }

    QStyleOptionTitleBar so;
    setAttribute(Qt::WA_QuitOnClose, false); //Si chiude al chiudersi del padre

    QGridLayout *gl = new QGridLayout(this);
    QTableView* table = new QTableView(this);

    this->matrix = *matrix;
    table->setModel(createModel());
    table->verticalHeader()->hide();
    table->horizontalHeader()->hide();
    table->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);

    gl->addWidget(table);
    gl->setMargin(0);
    if(table->verticalScrollBar())
        setFixedWidth(sizeHint().width() + style()->pixelMetric(QStyle::PM_ScrollBarExtent));
    else setFixedWidth(sizeHint().width());
    move(pos.x() + size.width(), pos.y());
}

QStandardItemModel * TableWidget::createModel()
{
    size_t numRows = matrix.size();
    size_t numColumns = matrix[1].size();
    matrix[0].push_back('R');

    QStandardItemModel* model = new QStandardItemModel(static_cast<int>(numRows), static_cast<int>(numColumns));
    for (size_t row = 0; row < numRows; ++row)
        for (size_t column = 0; column < numColumns; ++column)
        {
            QString text(matrix[row][column]);
            QStandardItem* item = new QStandardItem(text);
            item->setEditable(false);
            item->setTextAlignment(Qt::AlignCenter);
            model->setItem(static_cast<int>(row), static_cast<int>(column), item);
        }
    return model;
}

TableWidget::~TableWidget()
{
}
