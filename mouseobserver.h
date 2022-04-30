#ifndef MOUSEOBSERVER_H
#define MOUSEOBSERVER_H

#include<QtWidgets>

class mouseobserver: public QLabel
{
public:
    mouseobserver(QWidget* pwgt = 0);

protected:
    virtual void mousePressEvent (QMouseEvent*)
};

#endif // MOUSEOBSERVER_H
