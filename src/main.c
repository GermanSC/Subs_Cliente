/*
 ============================================================================
 Name        : main.c
 Project	 : Subs_Cliente
 Author      : German Sc.
 Version     : 0.0
 Copyright   : Completamente copyrighteado 2015
 Description : Nada.
 ============================================================================
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

int		sockfd;

void* timeOut_check(void)
{
	for(;;)
	{
		sleep(2);
		write(sockfd, "Estoy viendo...",15);
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	/*	Variables de Control	*/

	int ctrl	=	0;

	/*	Variables de Conexión	*/
	int		port		=	15002;
	char	ip[INET_ADDRSTRLEN] = "127.0.0.1";
	struct sockaddr_in	server_info;

	printf("Inicializando...");

	/*	Seteo del Hilo	*/

	pthread_t hilo_tout;
	pthread_create(&hilo_tout, NULL, (void *)&timeOut_check,NULL);

	/*	Configuración del socket	*/

	sockfd = socket(PF_INET,SOCK_STREAM,0);
	if(sockfd == -1)	/*	Error de creación de socket	*/
	{
		printf("  Error en la creacion del socket.\n\n");
		return -1;
	}

	inet_pton(AF_INET, ip, &server_info.sin_addr);
	server_info.sin_family	=	AF_INET;
	server_info.sin_port	=	htons(port);

	printf(" Listo.\n");

	printf("Intentando conectar con servidor en %s:%d...",ip,port);

	ctrl = connect(sockfd,(struct sockaddr *)&server_info,sizeof (struct sockaddr_in));
	if(ctrl == -1)
	{
		printf("ERROR: No se pudo conectar con servidor.\n\n");
		close(sockfd);
		return -1;
	}

	printf(" Listo.\n");

	/*	Conectado... Espero los subtitulos nomás	*/

	char buff[512]="";
	fd_set readfd;
	FD_ZERO(&readfd);

	while(1)
	{
		FD_SET(sockfd,&readfd);
		select(sockfd+1,&readfd,NULL,NULL,NULL);
		if(FD_ISSET(sockfd,&readfd))
		{
			ctrl = read(sockfd,buff,sizeof buff);
			if(ctrl == 0)	/*	Conexión terminada	*/
			{
				printf(">Conexión terminada.\n\n");
				break;
			}
			else
			{
				if(strcmp(buff,"RDY_CMD") == 0)
				{
					printf("Recibiendo Stream: \n");

				}
				else
				{
					printf("%.*s",ctrl,buff);
				}
			}
		}
	}
	close(sockfd);
	return 0;
}
