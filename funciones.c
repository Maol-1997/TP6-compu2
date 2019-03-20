#include "funciones.h"
int buscar(char* palab, char* buffer){
	int a = 0;
	char * p;
	//write(1,palab,strlen (palab));
	while ( (p = strstr(buffer,palab)) != NULL )  {
		buffer=p;
		buffer++;
		a++;
		//write(1,buffer,strlen(buffer));
	}
	return a;
}
int abrir(){
	return open("services",O_RDONLY);
}

void buff(int arch, char* buffer){ // devuelve todo el buffer
	read(arch,buffer,sizeof buffer);
}

char* palabrares(int connfd){
	char buff[1000]="";
	read(connfd,buff,sizeof buff);
	char * linea;
	strtok(buff,"/");
	linea = strtok(NULL,"/");
	char linea2[1000];
	strcpy(linea2,linea);
	char * lin;
	lin = strtok(linea2," ");
	return lin;

}

