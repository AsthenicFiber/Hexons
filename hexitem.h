#ifndef HEXITEM_H
#define HEXITEM_H


#include <QGraphicsItem>
#include "hex.h"
#include "matrix.h"

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
    //virtual hsv get_color() = 0;
    hsv get_color();
    //virtual cube get_pos() = 0;
    cube get_pos();
    bool has_vis();
    virtual void set_vis(Matrix vision);
    virtual void advance(int step) = 0;

protected:
    QColor color;
    cube hex;
    bool vis;
private:

};

#endif // HEXITEM_H
