#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>
#include <iostream>
#include <vector>

#include <QPoint>
#include <QPainter>

class PlotWidget : public QWidget
{
    Q_OBJECT
private:
    std::vector<QPointF> points;

public:
    PlotWidget(QWidget *parent = nullptr, const std::vector<std::pair<double, double>>* points = nullptr,const QSize& size = QSize(0, 0), const QPoint& pos = QPoint(1024,1024));

protected:
    void paintEvent(QPaintEvent* ); //Q_DECL_OVERRIDE;
};

#endif // PLOTWIDGET_H
