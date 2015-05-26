#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;



int main(void){
	
	struct hostent *hostinfo;
	SOCKADDR_IN sin = { 0 };
	char var[50];
	printf("Entrez le nom du site\n");
	scanf("%s",var);
	char hostname[100];
	strcpy(hostname,var);
	char request[10000];
	SOCKET sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock == INVALID_SOCKET){
		perror("socket()");
		exit(errno);
	}
	
	hostinfo = gethostbyname(hostname);
	
	if(hostinfo ==NULL){
		printf("UNKNOW host %s\n",hostname);
		exit(EXIT_FAILURE);
	}
	sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
	sin.sin_port = htons(80);
	sin.sin_family =  AF_INET;

	if(connect(sock,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
    perror("connect()");
    exit(errno);
	}else{
		printf("connect success\n");
	}
	bzero(var,50);
	printf("Entrez la requete\n");
	scanf("%s",var);
	printf("%s\n",var);
	bzero(request, 10000);
	sprintf(request,"Get /%s\r\nHost: %s\r\n\r\n",var,hostname);
	printf("%s\n",request);
	if(send(sock,request,strlen(request),0)<0){
		perror("send()");
		exit(errno);
	} else {
		printf("send succes\n");

	}
	bzero(request,10000);
	read(sock,request,10000);
	printf("%s\n",request);
	
	close(sock);



}
