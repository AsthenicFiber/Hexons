#include "matrix.h"
#include <iostream>

Matrix::Matrix(int rows, int cols)
{
    m = rows;
    n = cols;

    if (m < 0 || n < 0)
    {
        std::cout << "\nMatrix dimensions must be positive.\n";
        m = 1;
        n = 1;
    }
    if (m > 1000 || n > 1000)
    {
        std::cout << "\nMatrix dimensions exceed 1000.\n";
        m = 1;
        n = 1;
    }

    p = new mel[m*n];
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            p[i*n+j] = 0;
        }
    }
}

Matrix::~Matrix()
{
    delete [] p;
    std::cout << "shutting down\n";
}

mel& Matrix::get(int row, int col)
{
    return p[row*n+col];
}

mel Matrix::get(int row, int col) const
{
    return p[row*n+col];
}

/*
void Matrix::set(int row, int col, mel val)
{
    p[row*n+col] = val;
}
*/

void Matrix::operator = (const Matrix &B)
{

    if (m != B.m || n != B.n)
    {
        std::cout << "Matrices dimensions do not match for = operation." << std::endl;
        throw std::exception();
    }

    m = B.m;
    n = B.n;

    //p = new mel[m*n];

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            get(i,j) = B.get(i,j);
            //set(i,j,B.get(i,j));
        }
    }
    return;
}

Matrix Matrix::operator + (const Matrix &B)
{
    if (m != B.m || n != B.n)
    {
        std::cout << "Matrices dimensions do not match for + operation." << std::endl;
        throw std::exception();
    }

    Matrix C(m,n);

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C.get(i,j) = get(i,j) + B.get(i,j);
            //C[i][j] = get(i,j) + B[i][j];
            //C(i,j) = get(i,j) + B(i,j);
            //C.set(i,j,get(i,j) + B.get(i,j));
        }
    }
    return C;
}

Matrix Matrix::operator += (const Matrix &B)
{
    if (m != B.m || n != B.n)
    {
        std::cout << "Matrices dimensions do not match for + operation." << std::endl;
        throw std::exception();
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            get(i,j) = get(i,j) + B.get(i,j);
            //set(i,j,get(i,j) + B.get(i,j));
        }
    }
    return B;
}

Matrix Matrix::operator * (const mel &s)
{
    Matrix C(m,n);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C.get(i,j) = get(i,j)*s;
            //C.set(i,j,get(i,j)*s);
        }
    }
    return C;
}

mel Matrix::operator *=(const mel &s)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            get(i,j) = get(i,j)*s;
            //set(i,j,get(i,j)*s);
        }
    }
    return s;
}

Matrix Matrix::operator * (const Matrix &B)
{
    if (n != B.m)
    {
        std::cout << "Matrices dimensions do not match for * operation." << std::endl;
        throw std::exception();
    }

    Matrix C(m,B.n);
    for (int i = 0; i < C.m; i++)
    {
        for (int j = 0; j < C.n; j++)
        {
            mel sum = 0;
            for (int k = 0; k < n; k++)
            {
                sum += get(i,k) * B.get(k,j);
            }
            C.get(i,j) = sum;
            //C.set(i,j,sum);
        }
    }
    return C;
}

Matrix Matrix::operator ~ ()
{
    // Transpose Operator
    Matrix C(n,m);

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C.get(j,i) = get(i,j);
            //C.set(j,i,get(i,j));
        }
    }
    return C;
}

mel * Matrix::operator [] (const int &row)
{
    //return row * n + &p;
    return row*n + p;
}

mel &Matrix::operator ()(const int &row, const int &col)
{
    return get(row,col);
}

mel Matrix::operator ()(const int &row, const int &col) const
{
    return get(row,col);
}

void Matrix::print_matrix()
{
    std::cout << "\n" << m << " x " << n << std::endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << "\t" << get(i,j);
        }
        std::cout << std::endl;
    }
    return;
}
