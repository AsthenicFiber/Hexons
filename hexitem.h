#ifndef HEXITEM_H
#define HEXITEM_H


#include <QGraphicsItem>
#include "hex.h"
#include "matrix.h"
#include "nnbase.h"

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

struct Stats
{
    int attack;
    int defense;
    int speed;
    int energy;
    int health;
    int charisma;
    Stats(int A, int D, int S, int E, int H, int C) : attack(A), defense(D), speed(S), energy(E), health(H), charisma(C)
    {
    }
    Stats() : attack(0), defense(0), speed(0), energy(1), health(1), charisma(0)
    {
    }
};


QColor rgb2color(int rgbHex);
QColor rgb2color(rgb cRGB);
QColor hsv2color(hsv cHSV);
hsv color2hsv(QColor C);
rgb color2rgb(QColor C);

class HexItem : public QGraphicsItem
{
public:
    HexItem();
    ~HexItem();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    //void copy_hexon(Hexon A);
    //virtual hsv get_color() = 0;
    rgb get_color();
    rgb get_border();
    //virtual cube get_pos() = 0;
    cube get_pos();
    cube get_move();
    void set_pos(cube h);
    bool has_vis();

    virtual char h_type() = 0;

    cube update_pos();

    virtual void set_vis(Matrix vision);
    void advance(int step);

    virtual cube tstep() = 0;
    virtual int interact(HexItem *hitem) = 0;

    Stats stats;
    char stance = 'n';
    NNBase brain;

protected:
    //QColor color;
    cube hex;
    bool vis;
    cube dh;
    QColor color;
    QColor border;

private:

};

#endif // HEXITEM_H
