#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QtGui>
#include <vector>

class TableWidget : public QWidget
{
    Q_OBJECT
private:
    std::vector<std::vector<char>> matrix;

    QStandardItemModel *createModel();

public:
    TableWidget(QWidget *parent = nullptr, const std::vector<std::vector<char>> *table = nullptr, const QSize& size = QSize(0, 0), const QPoint& pos = QPoint(1024, 1024));
    ~TableWidget();
};

#endif // TABLEWIDGET_H
