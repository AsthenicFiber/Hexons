#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <iostream>

#include <math.h>

#include "hexitem.h"

HexItem::HexItem()
{
    color = QColor(Qt::blue);
}

void HexItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPolygon poly;

    poly << QPoint(-10,-17) << QPoint(10,-17) << QPoint(20,0) << QPoint(10,17) << QPoint(-10,17) << QPoint(-20,0);

    //QPen pen(Qt::transparent, 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
    QPen pen(Qt::white, 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
    QBrush brush(Qt::SolidPattern);

    color = rgb2color(get_color());

    brush.setColor(color);

    painter->setPen(pen);
    painter->setBrush(brush);

    painter->drawPolygon(poly);
    //painter->end();
}

QRectF HexItem::boundingRect() const
{
    return QRectF(-20,-17,40,34);
}

QColor rgb2color(int rgbHex)
{
    int red = (rgbHex >> 16) & 0xff;
    int green = (rgbHex >> 8) & 0xff;
    int blue = (rgbHex >> 0) & 0xff;
    return QColor(red, green, blue, 255);
}

