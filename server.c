#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>

#define PORT 8080
#define BACKLOG 3
#define BUFFER_SIZE 256


int main (){
	int fd;
	char *buffer[BUFFER_SIZE];
	struct sockaddr_in address;
	char *message = "VOCE ME CHAMOU?";
	int connfd;

	if((fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) <0) {
		printf("A porta nao foi criada\n");
		return 1;
	}

	address.sin_family=AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = PORT;

	int fromlen = sizeof(address);

	if(bind(fd, (struct sockaddr*) &address, sizeof(address))< 0) {
		printf("Interface de rede indisponivel\n");
		return 1;
	}

	recvfrom(fd, (void*)buffer, sizeof buffer,0, (struct sockaddr*)&address, &fromlen);
	printf("%s\n", buffer);

	close(fd);
	return 0;

}
