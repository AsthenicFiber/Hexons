#include "nnbase.h"
#include <random>

NNBase::NNBase()
{
    w1 = Matrix(10,10);
    w2 = Matrix(10,10);
    inp = Matrix(10,1);
    outp = Matrix(10,1);
    n1 = Matrix(10,1);
    init_weights();
}

Matrix NNBase::feedforward()
{
    n1 = inp*w1++;
    outp = n1*w2;
    return outp;
}

void NNBase::init_weights()
{
    std::default_random_engine generator;
    std::uniform_real_distribution<mel> distribution(-1.0,1.0);

    for (int i = 0; i < w1.rows(); i++)
    {
        for (int j = 0; j < w1.cols(); j++)
        {
            w1[i][j] = distribution(generator);
        }
    }

    for (int i = 0; i < w2.rows(); i++)
    {
        for (int j = 0; j < w2.cols(); j++)
        {
            w2[i][j] = distribution(generator);
        }
    }

    for (int i = 0; i < inp.rows(); i++)
    {
        for (int j = 0; j < inp.cols(); j++)
        {
            inp[i][j] = distribution(generator);
        }
    }
}
