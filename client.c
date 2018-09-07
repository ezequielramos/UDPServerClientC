#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 256

int main (int argc, char **argv){
	int fd;
	char *buffer[BUFFER_SIZE];
	char *message = "Olá servidor!";
	struct sockaddr_in address;

	if((fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		printf("O socket não foi criado\n");
		return 1;
  	}

	address.sin_family = AF_INET;
	address.sin_port = PORT;

	inet_pton(AF_INET, argv[1], &address.sin_addr);

	if((connect(fd, (struct sockaddr *) &address, sizeof(address))) < 0) {
		printf("Não foi possivel se conectar ao servidor:/\n");
		return 1;
	}


	send(fd, message, strlen(message), 0);
	printf("Mensagem enviada: %s\n", message);

	close(fd);

	return 0;
}
