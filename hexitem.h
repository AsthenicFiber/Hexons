#ifndef HEXITEM_H
#define HEXITEM_H


#include <QGraphicsItem>
#include "hex.h"

struct hsv
{
    // range 0-359
    int hue;
    // range 0-255
    //int sat;
    int val;
};

struct rgb
{
    int red;
    int green;
    int blue;
};


QColor rgb2color(int rgbHex);
QColor hsv2color(hsv cHSV);
hsv color2hsv(QColor C);
rgb color2rgb(QColor C);

class HexItem : public QGraphicsItem
{
public:
    HexItem();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    //void copy_hexon(Hexon A);
    virtual int get_color() = 0;
    virtual cube get_pos() = 0;

protected:
    QColor color;

private:

};

#endif // HEXITEM_H
