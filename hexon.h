

#ifndef HEXON_H
#define HEXON_H

#include "hexitem.h"
#include "nnbase.h"

void combat(Stats *S1, Stats *S2);

class Hexon : public HexItem
{
public:
    Hexon(int a, int b);
    Hexon(cube h);
    void copy_hexon(const Hexon &A);
    void set_vis(Matrix vision) override;
    void advance(int step) Q_DECL_OVERRIDE;
    cube tstep() override;
    int interact(HexItem *hitem) override;

private:
    NNBase brain;
};

#endif // HEXON_H
