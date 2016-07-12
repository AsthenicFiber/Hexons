#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "hexitem.h"

class Obstacle : public HexItem
{
public:
    Obstacle();
    Obstacle(cube h);

    cube tstep() override;
    int interact(HexItem *hitem) override;
    char h_type() override;

private:
    //cube hex;
};

#endif // OBSTACLE_H
