#ifndef FOOD_H
#define FOOD_H

#include "hexitem.h"

class Food : public HexItem
{
public:
    Food();
    Food(cube h);
    Food(cube h, int eneregy);

    cube tstep() override;
    int interact(HexItem *hitem) override;
    char h_type() override;
};

int grow_food_check(Stats *S);
Food * grow_food(cube h, int energy);

#endif // FOOD_H
