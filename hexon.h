

#ifndef HEXON_H
#define HEXON_H

#include "hexitem.h"
#include "nnbase.h"

class Hexon : public HexItem
{
public:
    Hexon(int a, int b);
    Hexon(cube h);
    void copy_hexon(const Hexon &A);
    void set_vis(Matrix vision) override;
    void advance(int step) Q_DECL_OVERRIDE;

private:
    NNBase brain;
};

#endif // HEXON_H
