

#ifndef HEXON_H
#define HEXON_H

//#include <QGraphicsItem>
//#include "hex.h"
#include "hexitem.h"

//class Hexon : public QGraphicsItem
class Hexon : public HexItem
//class Hexon
{
public:
    Hexon(int a, int b);
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    //void paintEvent(QPaintEvent *event);

    //QRectF boundingRect() const Q_DECL_OVERRIDE;
    void copy_hexon(const Hexon &A);
    int get_color() override;
    cube get_pos() override;

    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    void advance(int step) Q_DECL_OVERRIDE;
    //void advance();

private:
    //Hex hex;
    cube hex;
};

#endif // HEXON_H
