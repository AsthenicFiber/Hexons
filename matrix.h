#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

typedef float mel;

class Matrix
{
public:
    Matrix(int rows, int cols);
    Matrix(const Matrix&) = default;
    //Matrix(Matrix&&) = default;
    Matrix(Matrix&& other);
    ~Matrix();
    mel& get(int row, int col);
    mel get(int row, int col) const;
    //void set(int row, int col, mel val);

    //Matrix& operator = (const Matrix &B) = default;
    void operator = (const Matrix &B);
    Matrix operator + (const Matrix &B);
    Matrix operator += (const Matrix &B);
    Matrix operator * (const mel &s);
    mel operator *= (const mel &s);
    Matrix operator * (const Matrix &B);
    Matrix operator ++ ();
    mel* operator [](const int &row);
    mel& operator ()(const int &row, const int &col);
    mel operator ()(const int &row, const int &col) const;
    void print_matrix();

private:
    int m,n;
    mel *p;
    //std::vector<mel> p;
};

#endif // MATRIX_H
