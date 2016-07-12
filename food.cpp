#include "food.h"
#include <iostream>

Food::Food()
  : Food(cube((rand() % 40) - 20,(rand() % 40) - 20))
{
}

Food::Food(cube h)
{
    hex = h;
    pix p = cube2pix(hex);
    setPos(p.x,p.y);
    color = rgb2color(0x228B22);
    border = rgb2color(0x228B22);
    vis = false;
    stats = Stats(0,0,0,20,1,0,10);
}

Food::Food(cube h, int energy)
  : Food(h)
{
    stats.energy = energy;
}

cube Food::tstep()
{
    if ((rand() % 10) < 1)
    {
        dh = hex_dir[rand() % 6 + 1];
    }
    else
    {
        dh = global_origin;
        if (rand() % 10 < 1)
        {
            stats.energy++;
        }
    }
    return dh;
}

int Food::interact(HexItem *hitem)
{
    hitem;
    dh = global_origin;
    return 0;
}

char Food::h_type()
{
    return 'f';
}


int grow_food_check(Stats *S)
{
    if (S->energy <= 1)
    {
        return 0;
    }
    else
    {
        int E = (S->energy + (S->energy % 2))/2;
        S->energy -= E;
        return E;
    }
}

Food * grow_food(cube h, int energy)
{
    return new Food(h,energy);
}
