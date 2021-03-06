//Tecnologico de Monterrey
//Programacion Avanzada - Proyecto 2
//Diego Guerrero - A01625199
//Ricardo Montemayor - A01194869

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <omp.h>
#include <pthread.h>
#include <time.h>

#include "func.h"

#define TCOUNT 5

int MAT[2000][2000];
int SUM = 0;

void linearRegression(int n, char formula[50]){
    // Array of numbers
    int x[n], y[n], xy[n], x2[n], y2[n];
    // Sum values
    float ex, ey, exy, ex2, ey2;
    // Linear regression components
    float a, b;

    srand(time(0));

    // Fill arrays
    for (int i = 0; i < n; i++) {
        // Determine x and y values
        x[i] = i;
        y[i] = (rand() % (50)) + 1;

        // Fill other arrays
        xy[i] = x[i] * y[i];
        x2[i] = x[i] * x[i];
        y2[i] = y[i] * y[i];
    }

    // Find sum values
    for (int i = 0; i < n; i++) {
        ex += x[i];
        ey += y[i];
        exy += xy[i];
        ex2 += x2[i];
        ey2 += y2[i];
    }

    // Find a and b values
    a = (ey * ex2 - ex * exy) / (n * ex2 - ex * ex);
    b = (n * exy - ex * ey) / (n * ex2 - ex * ex);

    // Store linear regression formula in variable
    sprintf(formula,"y = %.4fx + %.4f", b, a);
}

void piValue(int n, char piValue[12]){
    static long total_steps = 100000;
    double step;
    int i;
    double pi, sum = 0.0;
    step = 1.0/(double)total_steps;
    #pragma omp parallel
    {
        double x;
        #pragma omp for reduction (+:sum)
            for(i=0; i<total_steps; i++){
                x = (i+0.5)*step;
                sum = sum + 4.0/(1.0+x*x);
            }
    }
    pi = step * sum;
    sprintf(piValue,"PI = %.10f",pi);
}

void *sumScalar(void *args) {
    int size = ((struct arguments *)args)->size;
    int tnum = ((struct arguments *)args)->tnum;

    for(int i = (size / TCOUNT) * tnum; i < (size / TCOUNT) * (tnum+1); i++) {
        for (int j = 0; j < size; j++) {
            SUM += MAT[i][j];
        }
    }
    return NULL;
}

void sumMatrix(int n, char sum[50]){
    srand(time(0));

    // Fill matrix with random values
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            MAT[i][j] = (rand() % (50)) + 1;
        }
    }

    // Display random matrix
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         printf("%d\t", MAT[i][j]);
    //     }
    //     printf("\n");
    // }

    // Initialize pthreads
    pthread_t tids[TCOUNT];

    // Assign each pthread task
    for (int i = 0; i < TCOUNT; i++) {
        struct arguments *args = (struct arguments *)malloc(sizeof(struct arguments));
        args->size = n;
        args->tnum  = i;
        pthread_create(&tids[i], NULL, sumScalar, (void *)args);
    }

    for (int i = 0; i < TCOUNT; i++) {
        pthread_join(tids[i], NULL);
    }
    
    sprintf(sum, "Matrix Sum = %d", SUM);
}

void sendHTML(char html[150]){
    sprintf(html,"\n<!DOCTYPE html>\n<html>\n\t<body>\n\t\t<h1>Hello Luis</h1>\n\t\t<p>Programming is my passion.</p>\n\t</body>\n</html>");
}

int isPrime(int n){ //Function to check if a number is Prime.
    int x=0;
    for(int i=2;i<=n/2;i++){
        if(n%i==0)
            x++;
    }
    if(x==0)//Prime no. has 2 factors-1 and number itself.
        return 1;
    else
        return 0;
}

void nearestPrime(int n, char nearPrime[4]){
    int bwdCount=0, fwdCount=0, bwdPrime, fwdPrime; //backward and forward variables

    for(int i=n; ; i++){ //forward loop and break when prime found
        fwdCount++;
        if(isPrime(i)){
            fwdPrime = i;
            break;
        }
    }

    for(int i=n; ;i--){ //backwards loop and break when prime found
        bwdCount++;
        if(isPrime(i)){
            bwdPrime = i;
            break;
        }
    }

    if(fwdCount <= bwdCount)
        sprintf(nearPrime, "Nearest prime to %d is: %d", n, fwdPrime);
    else
        sprintf(nearPrime, "Nearest prime to %d is: %d", n, bwdPrime);
}

void currentDateTime(char timeString[20]){ // space for "YYYY-MM-DD HH:MM:SS\0"
    
    time_t current_time;
    struct tm * time_info;

    time(&current_time);
    time_info = localtime(&current_time);

    strftime(timeString, 20, "%F %H:%M:%S", time_info); //%F represents YYYY-MM-DD
}