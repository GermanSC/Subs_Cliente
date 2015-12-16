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
		write(sockfd, "Estoy vivo...", 13);
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	/*	Variables de Control	*/

	pthread_t hilo_tout;
	int ctrl	=	0;
	char buff[512] = "";

	fd_set readfd;

	/*	Variables de Conexión	*/
	int		port		=	15002;
	char	ip[INET_ADDRSTRLEN] = "127.0.0.1";
	struct sockaddr_in	server_info;

	/*	Verificación de argumentos	*/

	if(argc != 3)
	{
		printf("usage: %s [direccion IP] [Puerto] \n"
				"Se utililzaran valores por defecto: \n"
				"IP: 127.0.0.1 \n"
				"port: 15002 \n",argv[0]);
	}else
	{
		strcpy(ip, argv[1]);
		sscanf(argv[2], "%d", &port);
	}


	printf("Inicializando...");

	/*	Seteo del Hilo	*/

	pthread_create(&hilo_tout, NULL, (void *)&timeOut_check,NULL);

	/*	Configuración del socket	*/

	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)	/*	Error de creación de socket	*/
	{
		printf("  Error en la creacion del socket.\n\n");
		return -1;
	}

	inet_pton(AF_INET, ip, &server_info.sin_addr);
	server_info.sin_family	=	AF_INET;
	server_info.sin_port	=	htons(port);

	printf(" Listo.\n");

	printf("Intentando conectar con servidor en %s:%d...", ip, port);

	ctrl = connect(sockfd, (struct sockaddr *)&server_info,sizeof (struct sockaddr_in));
	if(ctrl == -1)
	{
		printf("ERROR\nNo se pudo conectar con servidor.\n\n");
		close(sockfd);
		return -1;
	}

	printf(" Listo.\n");

	/*	Conectado... Espero los subtitulos nomás	*/
	FD_ZERO(&readfd);

	while(1)
	{
		FD_SET(sockfd, &readfd);
		select(sockfd+1, &readfd, NULL, NULL, NULL);
		if(FD_ISSET(sockfd, &readfd))
		{
			ctrl = read(sockfd, buff, sizeof(buff));
			if(ctrl == 0)	/*	Conexión terminada	*/
			{
				printf(">Conexión terminada.\n");
				break;
			}
			else
			{
				if(strcmp(buff, "RDY_CMD") == 0)
				{
					printf("Recibiendo Stream: \n\n\n");
				}
//				else if (strncmp(buff, "SSCMD_ENDOFFILE", 15) == 0)
				else if ( strstr(buff, "SSCMD_ENDOFFILE") !=  NULL)
				{
					printf(">Fin de Transmisión.\n");
					break;
				}
				else
				{
					printf("%.*s\n", ctrl, buff);
				}
			}
		}
	}
	close(sockfd);
	return 0;
}
