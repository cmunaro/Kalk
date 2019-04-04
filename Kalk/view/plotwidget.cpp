#include "plotwidget.h"
#include <QPainter>

PlotWidget::PlotWidget(QWidget *parent, const std::vector<std::pair<double, double>>* points, const QSize& size, const QPoint& pos) : QWidget(parent)
{
    setFixedHeight(size.height());
    setFixedWidth(size.height());
    move(pos.x() + size.width(), pos.y());
    setAttribute(Qt::WA_QuitOnClose, false); //Si chiude al chiudersi del padre

    for (std::vector<std::pair<double, double>>::const_iterator i = points->begin(); i != points->end(); ++i)
        this->points.push_back(QPointF(i->first, -i->second));
    repaint();
}

void PlotWidget::paintEvent(QPaintEvent* )
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(-this->width()/4, -this->height()/4);
    painter.scale(1.5, 1.5);

    painter.drawLine(QPoint(this->width()/2, 0), QPoint(this->width()/2, this->height()));
    painter.drawLine(QPoint(0, this->height()/2), QPoint(this->width(), this->height()/2));

    QPen pen(QColor(50,50,250), 1, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin);
    painter.setPen(pen);

    QPoint gap(this->width()/2,this->height()/2);
    std::vector<QPointF> translatedPoints;
    for (std::vector<QPointF>::iterator i = points.begin(); i != points.end(); ++i)
        translatedPoints.push_back(*i + gap);

    painter.drawPolyline(translatedPoints.data(), static_cast<int>(translatedPoints.size()));
}

