//#include <QGraphicsScene>
//#include <QPainter>
//#include <QStyleOption>
//#include <iostream>

#include <cmath>

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
    brain.set_inputs(vision);
}

void Hexon::advance(int step)
{
    if (!step)
    {
        return;
    }

    // update position
    //hex = hex+dh;
    pix p = cube2pix(hex);

    setPos(p.x,p.y);
    //std::cout << "\n" << p.x << "\t" << p.y;
    return;
}

cube Hexon::tstep()
{
    Matrix A = brain.feedforward();

    dh = hex_dir1[(int)((std::round(A[0][0]) * 4) + (std::round(A[1][0]) * 2) + std::round(A[2][0]))];
    color = hsv2color({std::round(359*A[3][0]),std::round(255*A[4][0])});

    //pix p = cube2pix(hex);

    //setPos(p.x,p.y);
    //std::cout << "\n" << p.x << "\t" << p.y;
    return dh;
}

int Hexon::interact(HexItem *hitem)
{
    if (hitem->has_vis())
    {
        rgb Crgb = color2rgb(hitem->color);
        hsv Chsv = color2hsv(hitem->color);
    }
    else
    {
        dh = global_origin;
        return 0;
        // don't move
    }

    return 1;
}
