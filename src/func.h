//Tecnologico de Monterrey
//Programacion Avanzada - Proyecto 2
//Diego Guerrero - A01625199
//Ricardo Montemayor - A01194869

#ifndef FUNC_H
#define FUNC_H

#define TCOUNT 5

struct arguments {
    int size;
    int tnum;
};

void linearRegression(int n, char formula[50]);

void piValue(int n, char piValue[12]);

void *sumScalar(void *args);

void sumMatrix(int n, char sum[50]);

void sendHTML(char html[150]);

int isPrime(int n);

void nearestPrime(int n, char nearPrime[4]);

void currentDateTime(char timeString[20]);

#endif
