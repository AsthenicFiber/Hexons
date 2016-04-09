#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "hexitem.h"

class Obstacle : public HexItem
{
public:
    Obstacle();
    Obstacle(cube h);
    int get_color();
    cube get_pos();
    void advance(int step) Q_DECL_OVERRIDE;

private:
    cube hex;
};

#endif // OBSTACLE_H