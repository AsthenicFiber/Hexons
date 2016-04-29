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
    //cube origin = {0,0,0};

    //cube h = cube_rotate(hex.H, origin, false);
    //hex.H = h;

    Matrix A = brain.feedforward();

    cube dh = {std::round(A[0][0]),std::round(A[1][0]),-std::round(A[0][0])-std::round(A[1][0])};
    //cube dh = {A[0][0],A[1][0],-A[0][0]-A[1][0]};
    //cube dh = cube(A[0][0],A[1][0]);
    hex = hex+dh;

    color = hsv2color({std::round(359*A[2][0]),std::round(255*A[3][0])});

    //hex = cube_rotate(hex,global_origin,false);

    //pix p = hex.loc();
    pix p = cube2pix(hex);

    setPos(p.x,p.y);
    //std::cout << "\n" << p.x << "\t" << p.y;
    //setPos(mapToParent(x, y));
    return;
}
