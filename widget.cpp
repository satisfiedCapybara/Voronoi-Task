#include <QPainter>
#include <QPen>
#include <memory>

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
}

void Widget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 6));
    for(auto&& elem: myVectorOfPnt)
    {
        painter.drawPoint(QPointF(elem.getX(),elem.getY()));
    }

    painter.setRenderHint(QPainter::Antialiasing,true);

    for(auto&& polygon: mySolution)
    {
        std::vector<prGeom2D::segment> theVecSegment= polygon.getSegment();
        QPointF* a = new QPointF[theVecSegment.size()+1];
        a[0] = {theVecSegment[0].getBegin().getX(), theVecSegment[0].getBegin().getY()};
        for(std::size_t i = 0; i < theVecSegment.size(); ++i)
        {
            a[i+1] = {theVecSegment[i].getEnd().getX(), theVecSegment[i].getEnd().getY()};
        }
        painter.drawPolyline(a, theVecSegment.size()+1);
        delete [] a;
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::DrawVoronoiTask(const QPointF& aPoint)
{
    for(auto&& elem: myVectorOfPnt)
    {
        if (!(elem.getX() != aPoint.x() || elem.getY()!= aPoint.y()))
            return;
    }
     myVectorOfPnt.push_back({aPoint.x(), aPoint.y()});
     mySolution = VoronoiTask(myVectorOfPnt);
     this->update();
}

 void Widget::mousePressEvent(QMouseEvent * event)
 {
     DrawVoronoiTask({static_cast<double>(event->x()), static_cast<double>(event->y())});
 }

