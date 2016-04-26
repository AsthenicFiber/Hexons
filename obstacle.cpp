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

/*
hsv Obstacle::get_color()
{
    return color2hsv(color);
    //return 0x703d0b;
}

cube Obstacle::get_pos()
{
    return hex;
}
*/

void Obstacle::advance(int step)
{
    if (!step)
    {
        return;
    }
    //cube origin = {0,0,0};

    //hex = cube_rotate(hex, global_origin, true);

    //hex.H = h;

    pix p = cube2pix(hex);
    setPos(p.x,p.y);
    return;
}
