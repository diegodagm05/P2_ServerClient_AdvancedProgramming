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

#define PORT 1025
#define BUFFSIZE 100

int main() {    
    
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
    char *buffer = malloc(BUFFSIZE*sizeof(char));

    // Aceptar nueva conexion
    socklen_t cli_addr_len = sizeof(cli_addr);        
    connfd = accept(fd, NULL, NULL);

    if (connfd == -1){
        perror("Unable to connect\n");        
    }

    // Leer buffer de cliente
    read(connfd, buffer, BUFFSIZE);




    // Responder a cliente
    write(connfd, buffer, strlen(buffer));

    free(buffer);

    // Cerrar conexiones
    close(connfd);
    close(fd);
    return 0;
}