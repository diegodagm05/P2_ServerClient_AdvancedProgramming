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

#define PORT 1025
#define BUFFSIZE 200

int main(int argc, char *argv[]) {

    if(argc >= 2)
        omp_set_num_threads(atoi(argv[1]));
    else{
        omp_set_num_threads(50);
    }
        // Crear socket TCP
        int fd = socket(AF_INET, SOCK_STREAM, 0);
        
        // Asignar puerto a socket
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;    
        addr.sin_port = htons(PORT);    
        addr.sin_addr.s_addr = INADDR_ANY;  
        
        // Poner socket en modo escucha (bind)    
        if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {        
            perror("Unable to bind\n");        
            close(fd);        
            exit(1);    
        }    
        if (listen(fd, 1) == -1){        
            perror("Unable to listen\n");    
        }    
        
        // Repetir
        int connfd;

    while(1){
        #pragma omp parallel
        {
            char *buffer = calloc(BUFFSIZE, sizeof(char));

            // Aceptar nueva conexion
            connfd = accept(fd, NULL, NULL);

            if (connfd == -1){
                perror("Unable to connect\n");      
            }

            // Leer buffer de cliente
            read(connfd, buffer, BUFFSIZE);

            int number = atoi(buffer); //store the number read from client
            char threadAnswer[BUFFSIZE];

            printf("Server received %s from client\n", buffer);

            if( number % 9 == 0 ){ //funcion 1
                linearRegression(atoi(buffer), threadAnswer);
            }
            else if( number % 7 == 0 ){ //funcion 2
                piValue(number, threadAnswer);
            }
            else if( number % 5 == 0 ){ //funcion 3
                sumMatrix(number, threadAnswer);
            }
            else if( number % 3 == 0 ){ //funcion 4
                sendHTML(threadAnswer);
            }
            else if( number % 2 == 0 ){ //funcion 5
                nearestPrime(number, threadAnswer);
            }
            else{
                printf("Number %d does not have a function\n", number);
            }

            // Responder a cliente
            char timeToReturn[20]; //variable where the current time is stored
            currentDateTime(timeToReturn); //get current time
            strcpy(buffer, "DATE & TIME: ");
            strcat(buffer, timeToReturn); //add the time to the buffer
            strcat(buffer, " | ");
            strcat(buffer, threadAnswer); //concatenate the answer to the buffer
            #pragma omp critical
            {
                write(connfd, buffer, strlen(buffer));
                // sleep(1);
            }
                free(buffer);

            // Cerrar conexion
            close(connfd);
        }
    }
    close(fd);
    return 0;
}