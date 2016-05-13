//#include <QGraphicsScene>
//#include <QPainter>
//#include <QStyleOption>
//#include <iostream>

#include <cmath>

#include "hexon.h"

Hexon::Hexon(int a, int b)
{

    //hex.x = a;
    //hex.y = -a-b;
    //hex.z = b;
    hex = cube(a,b);

    pix p = cube2pix(hex);

    //setPos(mapToParent(x, y));
    setPos(p.x,p.y);
    color = rgb2color(0x0000ff);
    border = rgb2color(0x000000);
    brain.set_size(6*(3*(6-1)*6+1) + 6,3+2+3,30); // make size universal
    vis = true;
    stats = Stats((rand()%10)+1,rand()%5,(rand()%10)+1,(rand()%20)+21,(rand()%50)+51,(rand()%10)+1);
}

Hexon::Hexon(cube h)
{
    hex = h;
    pix p = cube2pix(hex);
    setPos(p.x,p.y);
    color = rgb2color(0x0000ff);
    border = rgb2color(0x000000);
    brain.set_size(6*(3*(6-1)*6+1) + 6,3+2+3,30);
    vis = true;
    stats = Stats((rand()%10)+1,rand()%5,(rand()%10)+1,(rand()%20)+21,(rand()%50)+51,(rand()%10)+1);
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
    //color = hsv2color({std::round(359*A[3][0]),std::round(255*A[4][0])});

    int st = (std::round(A[3][0]) * 2) + std::round(A[4][0]);
    if (st == 0)
    {
        stance = 'a';
    }
    else if (st == 1)
    {
        stance = 'b';
    }
    else
    {
        stance = 'n';
    }

    rgb C;
    C.red = 255-(int)(255*exp(-mel(stats.attack+stats.speed)/10));
    C.green = 255-(int)(255*exp(-mel(stats.defense+stats.health)/50));
    C.blue = 255-(int)(255*exp(-mel(stats.energy+stats.charisma)/25));
    //std::cout << C.red << "\t" << C.green << "\t" << C.blue << std::endl;

    color = rgb2color(C);

    C.red = 255*A[5][0];
    C.green = 255*A[6][0];
    C.blue = 255*A[7][0];
    border = rgb2color(C);

    //C = color2rgb(color);
    //std::cout << C.red << "\t" << C.green << "\t" << C.blue << std::endl;
    //color = rgb2color(rgb{stats.attack+stats.speed, stats.defense+stats.health, stats.energy+stats.charisma});

    //pix p = cube2pix(hex);

    //setPos(p.x,p.y);
    //std::cout << "\n" << p.x << "\t" << p.y;
    return dh;
}

int Hexon::interact(HexItem *hitem)
{
    if (hitem->has_vis())
    {
        if (stance == 'n')
        {
            dh = global_origin;
            return 0;
        }
        else if (stance == 'a')
        {
            //attack sequence

            //initiative
            if (hitem->stats.speed > stats.speed)
            {
                // other attacks first
                combat(&hitem->stats,&stats);
                if (stats.health <= 0)
                {
                    return 2;
                }
                combat(&stats,&hitem->stats);
                if (hitem->stats.health <= 0)
                {
                    return 3;
                }
            }
            else
            {
                // initiative won
                combat(&stats,&hitem->stats);
                if (hitem->stats.health <= 0)
                {
                    return 3;
                }
                combat(&hitem->stats,&stats);
                if (stats.health <= 0)
                {
                    return 2;
                }
            }

            return 0;
        }
        else if (stance == 'b')
        {
            //breed sequence
            dh = global_origin;
            return 0;
        }
    }
    else
    {
        dh = global_origin;
        return 0;
        // don't move
    }

    return 0;
}

void combat(Stats *S1, Stats *S2)
{
    if (S1->energy <= 0)
    {
        return;
    }
    S1->energy--;

    if (S1->attack <= S2->defense)
    {
        return;
    }

    //Roll to Hit
    if ((rand() % (S1->speed + S2->speed)) < S1->speed)
    {
        S2->health -= S1->attack - S2->defense;
        S1->attack++;
        S2->defense++;
    }
    else
    {
        S1->speed++;
        S2->speed++;
    }
    return;
}
