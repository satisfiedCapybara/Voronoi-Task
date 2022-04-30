#ifndef WIDGET_H
#define WIDGET_H
#include <QMouseEvent>
#include <QWidget>
#include <QPointF>
#include <vector>
#include "headers/PrimitiveGeometry.h"
#include "headers/VoronoiTask.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr) ;
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent * event) override;
    ~Widget();

public slots:
    void DrawVoronoiTask(const QPointF&);
private:
    std::vector<prGeom2D::point> myVectorOfPnt;
    std::vector<topoG::convexPolygon> mySolution;

    Ui::Widget *ui;
};
#endif // WIDGET_H
