
#include "funciones.h"
//archivo de texto proc/cpuinfo
// localhost:8000/procesador/model


int main(int argc, char **argv){



	int fd, connfd, pid;
	int puerto=5000; //por defecto


	//printf("%d",arch);

	struct sockaddr_in procrem={};

	fd=socket(AF_INET, SOCK_STREAM, 0);
	if(fd<0){return fd;}


	procrem.sin_family = AF_INET;   //Familia TCP/IP
	procrem.sin_port = htons(puerto);  




	procrem.sin_addr.s_addr = htonl(INADDR_ANY);
	//inet_pton(AF_INET,"0.0.0.0", &procrem.sin_addr);
	int a=1;

	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,&a, sizeof a);

	if (bind(fd,(struct sockaddr *)&procrem, sizeof procrem) < 0 ) {
		perror ("bind");
		return -1;
	}

	listen(fd, 5);


	while ( (connfd = accept(fd,NULL, 0)) > 0 ){
		pid = fork();
		//hijo
		if ( pid == 0 ) {
			char palabra[15]="";
			char i;
			int archivo = abrir();
			char buffer[30000]="";
			read(archivo,buffer,sizeof buffer);
			strcpy(palabra,palabrares(connfd)); // palabra que busco
			//write(1,buffer,30000);
			int cantidad = buscar(palabra,buffer); // cantidad de veces
			char cantidad2[10]="";
			sprintf(cantidad2,"%d",cantidad);
			/*-----------------------*/
			char resp[500]="";
			int length = (int)strlen(cantidad2)+25+(int)strlen(palabra);
			sprintf(resp,"HTTP/1.1 200 OK\nContent-Length: %d\nContent-Type: text/plain\n\n",length);

			write(connfd,resp,strlen(resp));
			sprintf(resp,"se encontraron %s palabras %s",cantidad2,palabra);
			write(connfd,resp,strlen(resp));
			/*----------------------*/
			close(connfd);
			close(archivo);
			return 0;


		}
	}



	close(connfd);

	return 0;
} 
