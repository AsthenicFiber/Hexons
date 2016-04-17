#ifndef NNBASE_H
#define NNBASE_H

#include "matrix.h"

class NNBase
{
public:
    NNBase(int n_in, int n_out, int n_n);
    Matrix feedforward();
    NNBase breed(NNBase B, int mode, int mutation);

private:
    void init_weights();

    Matrix w1, w2, inp, n1, outp;
    int inputs, outputs, nodes;

};

#endif // NNBASE_H
