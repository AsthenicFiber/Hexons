

#ifndef HEXON_H
#define HEXON_H

#include "hexitem.h"

// Global Variable Access Functions
int get_visibility();
void set_visibility(int val);

void combat(Stats *S1, Stats *S2);

class Hexon : public HexItem
{
public:
    Hexon(int a, int b);
    Hexon(cube h);
    Hexon(cube h, NNBase NN);
    void copy_hexon(const Hexon &A);
    void set_vis(Matrix vision) override;
    //void advance(int step) Q_DECL_OVERRIDE;
    cube tstep() override;
    int interact(HexItem *hitem) override;
    char h_type() override;

private:
};

bool breed_hexon_check(Stats *S1, Stats *S2);
Hexon * breed_hexon(HexItem *A, HexItem *B, cube h);

#endif // HEXON_H
