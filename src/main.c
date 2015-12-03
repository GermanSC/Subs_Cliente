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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

void* timeOut_check(void)
{
	for(;;)
	{
		sleep(2);
		printf("Aca estoy!\n");
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	/*	Variables de Conexión	*/
	int		port		=	15002;
	int		sock_srv, nuevofd;
	struct sockaddr_in	server_sock;
	struct sockaddr_in	client_info;

	/*	Seteo del Hilo	*/

	pthread_t hilo_tout;
	pthread_create(&hilo_tout, NULL, &timeOut_check,NULL);

	while(1);

	return 0;
}
