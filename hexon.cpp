//#include <QGraphicsScene>
//#include <QPainter>
//#include <QStyleOption>
//#include <iostream>

//#include <math.h>

#include "hexon.h"

Hexon::Hexon(int a, int b)
{
    /*cube h;
    h.x = a;
    h.y = -a-b;
    h.z = b;
    hex.set_cube(h);

    pix p = hex.loc();*/

    hex.x = a;
    hex.y = -a-b;
    hex.z = b;

    pix p = cube2pix(hex);

    //setPos(mapToParent(x, y));
    setPos(p.x,p.y);
}


//void hexon::paintEvent(QPaintEvent *event)
/*void Hexon::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //QPainter painter(this);
    QPolygon poly;

    poly << QPoint(-10,-17) << QPoint(10,-17) << QPoint(20,0) << QPoint(10,17) << QPoint(-10,17) << QPoint(-20,0);

    //painter.setPen(QPen(Qt::black, 12, Qt::DashDotLine, Qt::RoundCap));
    //painter.drawLine(0, 0, 200, 200);

    // QPen: style(), width(), brush(), capStyle() and joinStyle().
    //QPen pen(Qt::transparent, 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
    QPen pen(Qt::white, 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
    QBrush brush(Qt::SolidPattern);

    cube B = {0,1,-1};
    cube h = {0,0,0};
    if (hex.LineofSight(h,B))
    {
        brush.setColor(Qt::blue);
    }
    else
    {
        brush.setColor(Qt::red);
    }

    painter->setPen(pen);
    painter->setBrush(brush);

    painter->drawPolygon(poly);
    //painter->end();
}

QRectF Hexon::boundingRect() const
{
    return QRectF(-20,-17,40,34);
}*/

void Hexon::copy_hexon(const Hexon &A)
{
    hex = A.hex;
    return;
}

void Hexon::advance(int step)
{
    if (!step)
    {
        return;
    }
    //cube origin = {0,0,0};

    //cube h = cube_rotate(hex.H, origin, false);
    //hex.H = h;

    hex = cube_rotate(hex,global_origin,false);

    //pix p = hex.loc();
    pix p = cube2pix(hex);

    setPos(p.x,p.y);
    //std::cout << "\n" << p.x << "\t" << p.y;
    //setPos(mapToParent(x, y));
    return;
}

int Hexon::get_color()
{
    return 0x0000ff;
}

cube Hexon::get_pos()
{
    return hex;
}
