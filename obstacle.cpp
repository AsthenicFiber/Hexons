#include "obstacle.h"

Obstacle::Obstacle()
  : Obstacle(cube((rand() % 40) - 20,(rand() % 40) - 20))
{
}

Obstacle::Obstacle(cube h)
{
    hex = h;
    pix p = cube2pix(hex);
    setPos(p.x,p.y);
    color = rgb2color(0x703d0b);
    border = rgb2color(0x703d0b);
    vis = false;
    stats = Stats(0,15,0,0,(rand()%100)+101,0);
}
/*
void Obstacle::advance(int step)
{
    if (!step)
    {
        return;
    }
    //hex = cube_rotate(hex, global_origin, true);

    //hex = hex + dh;
    pix p = cube2pix(hex);
    setPos(p.x,p.y);
    return;
}*/

cube Obstacle::tstep()
{
    //pix p = cube2pix(hex);
    //setPos(p.x,p.y);
    dh = global_origin;
    return dh;
}

int Obstacle::interact(HexItem *hitem)
{
    hitem;
    return 0;
}

char Obstacle::h_type()
{
    return 'o';
}
