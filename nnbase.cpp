#include "nnbase.h"
#include <chrono>

//typedef std::chrono::high_resolution_clock myclock;

std::default_random_engine NNBase::generator(0); // std::chrono::system_clock::now().time_since_epoch().count())

NNBase::NNBase()
    : NNBase(1,1,1)
{ }

NNBase::NNBase(int n_in, int n_out, int n_n)
{
    inputs = n_in;
    outputs = n_out;
    nodes = n_n;
    w1 = Matrix(n_n,n_in);
    w2 = Matrix(n_out,n_n);
    inp = Matrix(n_in,1);
    outp = Matrix(n_out,1);
    n1 = Matrix(n_n,1);
    init_weights();
}

void NNBase::set_size(int n_in, int n_out, int n_n)
{
    inputs = n_in;
    outputs = n_out;
    nodes = n_n;
    w1 = Matrix(n_n,n_in);
    w2 = Matrix(n_out,n_n);
    inp = Matrix(n_in,1);
    outp = Matrix(n_out,1);
    n1 = Matrix(n_n,1);
    init_weights();
}

void NNBase::set_inputs(Matrix input)
{
    if (inputs == input.rows())
    {
        inp = input;
    }
    return;
}

Matrix NNBase::feedforward()
{
    inp.activation();
    n1 = w1*inp;
    n1.activation();
    outp = w2*n1;
    outp.activation();
    return outp;
}

NNBase NNBase::breed(NNBase B, int mode, int mutation)
{
    NNBase C(inputs, outputs, nodes);
    if (mode == 0)
    {
        // unweighted average
        C.w1 = (w1 + B.w1)*0.5;
        C.w2 = (w2 + B.w2)*0.5;
    }
    else if (mode == 1)
    {
        // random weighted average
        std::uniform_real_distribution<mel> distribution(0,1.0);
        mel x = distribution(generator);

        C.w1 = (w1 + B.w1)*x;
        C.w2 = (w2 + B.w2)*(1-x);
    }
    else if (mode == 2)
    {
        // random selection from parents
        for (int i = 0; i < C.w1.rows(); i++)
        {
            for (int j = 0; j < C.w1.cols(); j++)
            {
                if (std::rand() % 2)
                {
                    C.w1[i][j] = w1[i][j];
                }
                else
                {
                    C.w1[i][j] = B.w1[i][j];
                }
            }
        }
        for (int i = 0; i < C.w2.rows(); i++)
        {
            for (int j = 0; j < C.w2.cols(); j++)
            {
                if (std::rand() % 2)
                {
                    C.w2[i][j] = w2[i][j];
                }
                else
                {
                    C.w2[i][j] = B.w2[i][j];
                }
            }
        }
    }

    if (!(rand() % mutation))
    {
        std::uniform_real_distribution<mel> distribution(-1.0,1.0);

        if (rand() % 2)
        {
            C.w1[rand() % C.w1.rows()][rand() % C.w1.cols()] = distribution(generator);
        }
        else
        {
            C.w1[rand() % C.w1.rows()][rand() % C.w1.cols()] = distribution(generator);
        }
    }
    return C;
}

void NNBase::copy_nn(NNBase B)
{
    w1 = B.w1;
    w2 = B.w2;
    return;
}

void NNBase::init_weights()
{
    //myclock::time_point begin_clock = myclock::now();
    //myclock::duration d = myclock::now() - begin_clock;
    //unsigned int seed1 = d.count();
    //unsigned seed1 = 102264135;
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
