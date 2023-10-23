#include "Matrix.h"

Matrix X(2,1); 
Matrix Y(2,2);
Matrix A(2,2);

void setup() {
  Serial.begin(9600);
  X.set(0,0,1); X.set(1,0,1); //X.set(1,0,1); X.set(1,1,1);
  Y.set(0,0,1); Y.set(0,1,1); Y.set(1,0,1); Y.set(1,1,1);
  Serial.println("Iniciado");
}

void loop() {
  A = X * Y;
  Serial.println(A.row()+A.col());
}