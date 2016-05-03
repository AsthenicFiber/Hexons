#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "hexitem.h"

class Obstacle : public HexItem
{
public:
    Obstacle();
    Obstacle(cube h);
    //hsv get_color() override;
    //cube get_pos() override;
    void advance(int step) Q_DECL_OVERRIDE;

    cube tstep() override;
    int interact(HexItem *hitem) override;

private:
    //cube hex;
};

#endif // OBSTACLE_H
