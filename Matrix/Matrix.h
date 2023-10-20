/***
 * Refeito por Leo
 * Basicamente cópia do da USP com duas funções a mais
 ***/

#ifndef Matrix_h
#define Matrix_h

#include <assert.h>
#include <Arduino.h>

class Matrix{
private:
    unsigned int row_;
    unsigned int col_;

    float **matrix_;

    void allocate();
    void deallocate();
    void initialize();
public:
    Matrix(unsigned rows=0, unsigned cols=0);
    Matrix(const Matrix &M);
    ~Matrix();

    void setSize(unsigned lines, unsigned columns);
    unsigned row() const { return row_; }
    unsigned col() const { return col_; }
    float get(unsigned i, unsigned j) const;
    void set(int i, int j, float value);

    Matrix tran() const;
    Matrix inv() const;

    static Matrix identity(unsigned size);
    static Matrix diag(unsigned size, float diagValue);

    void copyFrom(const Matrix &M);
    void print();

    void operator=(const Matrix &M);
    Matrix operator+(const Matrix &M) const;
    Matrix operator+(float k) const;
    Matrix operator-(const Matrix &M) const;
    Matrix operator-(float k) const;
    Matrix operator*(const Matrix &M) const;
    Matrix operator*(float k) const;
    void operator+=(const Matrix &M);
    void operator+=(float k);
    void operator-=(const Matrix &M);
    void operator-=(float k);
    void operator*=(const Matrix &M);
    void operator*=(float k);
};
#endif