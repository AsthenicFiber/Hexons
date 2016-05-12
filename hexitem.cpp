#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <iostream>

#include <math.h>

#include "hexitem.h"

HexItem::HexItem()
{
    color = QColor(Qt::blue);
    border = QColor(Qt::white);
    hex = global_origin;
    vis = false;
}

HexItem::~HexItem()
{
    scene()->removeItem(this);
}

void HexItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPolygon poly;

    poly << QPoint(-10,-17) << QPoint(10,-17) << QPoint(20,0) << QPoint(10,17) << QPoint(-10,17) << QPoint(-20,0);

    //QPen pen(Qt::transparent, 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
    //QPen pen(Qt::white, 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
    QPen pen(border, 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
    QBrush brush(Qt::SolidPattern);

    //color = hsv2color(get_color());

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

rgb HexItem::get_color()
{
    return color2rgb(color);
    //return 0x703d0b;
}

rgb HexItem::get_border()
{
    return color2rgb(border);
}

cube HexItem::get_pos()
{
    return hex;
}

bool HexItem::has_vis()
{
    return vis;
}

cube HexItem::update_pos()
{
    hex = hex + dh;
    return hex;
}

void HexItem::set_vis(Matrix vision)
{
    int N = vision.length();
    vision[N-6][1] = stats.attack;
    vision[N-5][1] = stats.defense;
    vision[N-4][1] = stats.speed;
    vision[N-3][1] = stats.energy;
    vision[N-2][1] = stats.health;
    vision[N-1][1] = stats.charisma;
    return;
}

QColor rgb2color(int rgbHex)
{
    int red = (rgbHex >> 16) & 0xff;
    int green = (rgbHex >> 8) & 0xff;
    int blue = (rgbHex >> 0) & 0xff;
    return QColor(red, green, blue, 255);
}

QColor rgb2color(rgb C)
{
    return QColor().fromRgb(C.red, C.green, C.blue, 255);
}

QColor hsv2color(hsv C)
{
    return QColor().fromHsv(C.hue, 255, C.val, 255);
}

hsv color2hsv(QColor C)
{
    return hsv{C.hue(),C.value()};
}

rgb color2rgb(QColor C)
{
    return rgb{C.red(),C.green(),C.blue()};
}
