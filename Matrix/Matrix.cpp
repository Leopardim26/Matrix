/***
 * Refeito por Leo
 * Basicamente cópia do da USP com duas funções a mais
 ***/

#include "Matrix.h"

Matrix::Matrix(unsigned lines, unsigned columns) {
    row_ = lines;
    col_ = columns;

    // Create matrix
    matrix_ = NULL;
    allocate();
    initialize();
}

Matrix::Matrix(const Matrix &M) {
    row_ = M.row();
    col_ = M.col();

    // Create matrix by copy
    matrix_ = NULL;
    allocate();
    copyFrom(M);
}

Matrix::~Matrix() {
    deallocate();
}

void Matrix::allocate() {
    if(row_!=0 && col_!=0) {
        matrix_ = new float*[row_];
        for(unsigned i=0; i<row_; i++)
            matrix_[i] = new float[col_];
    }
}

void Matrix::deallocate() {
    if(matrix_!=NULL) {
        for(unsigned i=0; i<row_; i++)
            delete[] matrix_[i];
        delete[] matrix_;
        matrix_ = NULL;
    }
}

void Matrix::initialize() {
    for(unsigned i=0; i<row_; i++)
        for(unsigned j=0; j<col_; j++)
            matrix_[i][j] = 0;
}

void Matrix::setSize(unsigned lines, unsigned columns) {
    deallocate();

    row_ = lines;
    col_ = columns;
    allocate();

    initialize();
}

float Matrix::get(unsigned i, unsigned j) const {
    assert(i<row_ && j<col_);

    return matrix_[i][j];
}

void Matrix::set(int i, int j, float value){
    assert(i<row_ && j<col_);

    matrix_[i][j] = value;
}

void Matrix::copyFrom(const Matrix &M) {
    assert(row_==M.row() && col_==M.col());

    for(unsigned i=0; i<row_; i++)
        for(unsigned j=0; j<col_; j++)
            matrix_[i][j] = M.get(i, j);
}

void Matrix::print() {
    for(unsigned i=0; i<row_; i++) {
        for(unsigned j=0; j<col_; j++)
            Serial.print(matrix_[i][j]);Serial.print(" ");
        Serial.println();
    }
    Serial.println("--------");
}

Matrix Matrix::identity(unsigned size) {
    return diag(size, 1);
}

Matrix Matrix::diag(unsigned size, float diagValue) {
    Matrix M(size, size);
    for(unsigned i=0; i<size; i++)
        M.set(i, i, diagValue);
    return M;
}

Matrix Matrix::tran()const{
    Matrix N(col_, row_);
    for(unsigned i=0; i<row_; i++)
        for(unsigned e=0; e<col_; e++)
            N.set(e, i, matrix_[i][e]);
    return N;
}

Matrix Matrix::inv()const{
    Matrix N(col_, row_);
    if(row_ == 1 && col_ == 1){
        N.set(0,0, 1/get(0,0));
    }else if(row_ == 2 && col_ == 2){
        float det = get(0,0) * get(1,1) - get(1,0) * get(0,1);
        N.set(0,0, get(0,0)/det);
        N.set(0,1, -get(0,1)/det);
        N.set(1,1, get(1,1)/det);
        N.set(1,0, -get(1,0)/det);
    }
    return N;
}

void Matrix::operator=(const Matrix &M) {
    deallocate();

    row_ = M.row_;
    col_ = M.col_;
    allocate();

    copyFrom(M);
}

Matrix Matrix::operator+(const Matrix &M) const {
    assert(row_==M.row() && col_==M.col());

    Matrix temp(row_, col_);
    for(unsigned i=0; i<row_; i++)
        for(unsigned j=0; j<col_; j++)
            temp.set(i, j, matrix_[i][j]+M.get(i,j));

    return temp;
}

Matrix Matrix::operator-(const Matrix &M) const {
    assert(row_==M.row() && col_==M.col());

    Matrix temp(row_, col_);
    for(unsigned i=0; i<row_; i++)
        for(unsigned j=0; j<col_; j++)
            temp.set(i, j, matrix_[i][j]-M.get(i,j));

    return temp;
}

Matrix Matrix::operator+(float k) const {
    Matrix temp(row_, col_);
    for(unsigned i=0; i<row_; i++)
        for(unsigned j=0; j<col_; j++)
            temp.set(i, j, matrix_[i][j]+k);

    return temp;
}

Matrix Matrix::operator-(float k) const {
    return (*this)+(-k);
}

Matrix Matrix::operator*(const Matrix &M) const {
    assert(col_==M.row());
    Matrix temp(row_, M.col());
    for(unsigned i=0; i<row_; i++) {
        for(unsigned j=0; j<M.col();j++) {
            temp.set(i, j, 0);
            for(unsigned k=0;k<M.row();k++)
                temp.set(i, j, temp.get(i,j)+matrix_[i][k]*M.get(k,j));
        }
    }
    return temp;
}

Matrix Matrix::operator*(float k) const {
    Matrix temp(row_, col_);
    for(unsigned i=0; i<row_; i++)
        for(unsigned j=0; j<col_; j++)
            temp.set(i, j, matrix_[i][j]*k);
    return temp;
}

void Matrix::operator+=(const Matrix &M) {
    for(unsigned i=0; i<row_; i++)
        for(unsigned j=0; j<col_; j++)
            matrix_[i][j] += M.get(i,j);
}

void Matrix::operator+=(float k) {
    for(unsigned i=0; i<row_; i++)
        for(unsigned j=0; j<col_; j++)
            matrix_[i][j] += k;
}

void Matrix::operator-=(const Matrix &M) {
    for(unsigned i=0; i<row_; i++)
        for(unsigned j=0; j<col_; j++)
            matrix_[i][j] -= M.get(i,j);
}

void Matrix::operator-=(float k) {
    for(unsigned i=0; i<row_; i++)
        for(unsigned j=0; j<col_; j++)
            matrix_[i][j] -= k;
}

void Matrix::operator*=(float k) {
    for(unsigned i=0; i<row_; i++)
        for(unsigned j=0; j<col_; j++)
            matrix_[i][j] *= k;
}