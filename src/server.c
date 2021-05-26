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

#define PORT 1025
#define BUFFSIZE 100



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
        struct sockaddr_in cli_addr;
        char *buffer = calloc(BUFFSIZE, sizeof(char));
        // printf("buff 50 %c\n", buffer[50]);

    #pragma omp parallel
    {
        // Aceptar nueva conexion
        socklen_t cli_addr_len = sizeof(cli_addr);        
        connfd = accept(fd, NULL, NULL);

        if (connfd == -1){
            perror("Unable to connect\n");      
        }

        // Leer buffer de cliente
        read(connfd, buffer, 2);

        int number = atoi(buffer);

        if( number % 9 == 0 ){
            //funcion 1
            printf("divisible entre 9: %s\n", buffer);
        }
        else if( number % 7 == 0 ){
            //funcion 2
            printf("divisible entre 7: %s\n", buffer);
        }
        else if( number % 5 == 0 ){
            //funcion 3
            printf("divisible entre 5: %s\n", buffer);
        }
        else if( number % 3 == 0 ){
            //funcion 4
            printf("divisible entre 3: %s\n", buffer);
        }
        else if( number % 2 == 0 ){
            //funcion 5
            printf("divisible entre 2: %s\n", buffer);
        }

        // Responder a cliente
        write(connfd, buffer, strlen(buffer));
        free(buffer);

        // Cerrar conexiones
        close(connfd);
        close(fd);
    }
    return 0;
}
