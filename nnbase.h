#ifndef NNBASE_H
#define NNBASE_H

#include "matrix.h"


class NNBase
{
public:
    NNBase();
    Matrix feedforward();

private:
    void init_weights();

    Matrix w1, w2, inp, n1, outp;

};

#endif // NNBASE_H
