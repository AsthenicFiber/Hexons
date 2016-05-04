#include "obstacle.h"

Obstacle::Obstacle()
{
    hex.x = (rand() % 40) - 20;
    hex.y = (rand() % 40) - 20;
    hex.z = -hex.y - hex.x;
    pix p = cube2pix(hex);
    setPos(p.x,p.y);
    color = rgb2color(0x703d0b);
    vis = false;
}

Obstacle::Obstacle(cube h)
{
    hex = h;
    pix p = cube2pix(hex);
    setPos(p.x,p.y);
    color = rgb2color(0x703d0b);
    vis = false;
}

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
}

cube Obstacle::tstep()
{
    //pix p = cube2pix(hex);
    //setPos(p.x,p.y);
    dh = global_origin;
    return dh;
}

int Obstacle::interact(HexItem *hitem)
{
    return 0;
}
