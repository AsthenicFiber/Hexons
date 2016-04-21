//#include <QGraphicsScene>
//#include <QPainter>
//#include <QStyleOption>
//#include <iostream>

//#include <math.h>

#include "hexon.h"

Hexon::Hexon(int a, int b)
{

    hex.x = a;
    hex.y = -a-b;
    hex.z = b;

    pix p = cube2pix(hex);

    //setPos(mapToParent(x, y));
    setPos(p.x,p.y);
    color = rgb2color(0x0000ff);
    brain.set_size(3*(4-1)*4+1,3+2,10);
    vis = true;
}

Hexon::Hexon(cube h)
{
    hex = h;
    pix p = cube2pix(hex);
    setPos(p.x,p.y);
    color = rgb2color(0x0000ff);
    brain.set_size(3*(4-1)*4+1,3+2,10);
    vis = true;
}

void Hexon::copy_hexon(const Hexon &A)
{
    hex = A.hex;
    return;
}

void Hexon::set_vis(Matrix vision)
{

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
