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
#define IP "127.0.0.1"
#define BUFFSIZE 100

int main(int argc, char *argv[]){
    
    // Crear socket TCP
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    // Establecer conexion
    struct sockaddr_in addr;    
    addr.sin_family = AF_INET;    
    addr.sin_port = htons(PORT);    
    inet_pton(AF_INET, IP, &addr.sin_addr);    
    if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {        
        perror("Unable to connect\n");       
        close(fd);
        exit(1);  
    }
    
    // printf("%s\n", argv[1]);
    
    // Write to server
    write(fd, argv[1], strlen(argv[1])); //argumento al ejecutar
    
    // Read from server
    char *buffer = malloc(BUFFSIZE*sizeof(char));
    read(fd, buffer, BUFFSIZE);
    printf("%s\n", buffer);
    free(buffer);

    // Cerrar conexion
    close(fd);    
    return 0;
}