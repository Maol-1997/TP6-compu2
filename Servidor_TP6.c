#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <netdb.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

#include <stdlib.h>
#include <string.h>
//#include <pthread.h>
#include <sys/mman.h>

//archivo de texto proc/cpuinfo
// localhost:8000/procesador/model


int tamano_ar(int fd){
	char buffer[50];
	int tamano = 0;
	int leido;
	while((leido = read(fd, buffer, 50)) > 0)
	{
		tamano = tamano + leido;
	}
	lseek(fd, 0, SEEK_SET);
	return tamano;
}

int main(){

	
  
	int fd, fdcliente, leido, conectado, connfd, pid;
	char buff[5000];
    //char buff2[2000];
    char c;
    int puerto=80; //por defecto
    
    
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
		  
		  
		  int arch=open("usuario.txt",O_RDONLY);
		  
		  int leido;
		char dir[256];
		char buff[1000];
		char buff2[tamano_ar(arch)];
		char rta[1000]="";
		char prot[1000];
		char dd[10];
        int arg;
        char * linea;
		leido = read(connfd,buff ,sizeof buff);
		 char * lin=strtok(buff,"/");
		 lin=strtok(NULL,"/");
        if(strcmp(lin,"user")==0){ //verificamos que el LINK este correcto // Añadir caso para archivo diferente a usuario.txt
		 lin=strtok(NULL,"/");
         char * numeroarg=lin;
        printf("%s\n",numeroarg);
         char * auxx;
         char * auxx2 = lin;
        lin=strtok(NULL,"/");
        auxx = strtok(lin,"");
        //printf("%s",auxx);
		 linea=strtok(auxx," ");
        if(strcmp(linea,"email")==0 || strcmp(linea,"nombre")==0 || strcmp(linea,"tel")==0 || strcmp(linea,"ciudad")==0 || strcmp(linea,"cp")==0){
        //printf("%s",linea);
        arg=1;
}
        else{
        linea=auxx2;
        strtok(linea," ");
        //printf("%s",linea);
        arg=0;
        }
		 char palabra[50];
        if(arg==1)
		 strcpy(palabra,numeroarg);
        else
        strcpy(palabra,linea);
		 strcat(palabra," ");
		 read(arch, buff2, sizeof buff2);
        
		 
		 char * puntero=strstr(buff2,palabra);
        //printf("%s",puntero);
	    if(puntero!=NULL){
        
        char* puntero_aux=puntero;
        int argumento=0;
        if(arg==1){
        if(strcmp(linea,"nombre")){
        while(*puntero!=' '){puntero++;}
        puntero++;
}
        if(strcmp(linea,"email"))
        argumento=1;
        if(strcmp(linea,"tel"))
        argumento=2;
        if(strcmp(linea,"ciudad"))
        argumento=3;
        if(strcmp(linea,"cp"))
        argumento=4;
}
/*while(*puntero!=' '){puntero++; }
        puntero++;*/
        //printf("%d",argumento); // SIEMPRE ME DA 4
        for(int x=0;x<argumento;x++) // pasar entre los terminos separados por :
{
        while(*puntero!=':'){puntero++; }
        puntero++;      
}
        while(*puntero_aux!='\n'){puntero_aux++;} // leer desde lo encontrado hasta el final de linea
        strncat(rta,puntero,(puntero_aux-puntero));
	strcpy(prot,"HTTP/1.1 200 OK\nContent-Length: ");
	int tam=strlen(rta);
	char tamm[50];
	sprintf(tamm,"%d",tam);
	strcat(prot,tamm);
	 strncat(prot,"\nContent-type: ",15);
	 strcat(prot,"text/html\n\n");
	 strcpy(dd,"\n\n");
			  write(connfd,prot, strlen(prot));
			  write(connfd,rta,strlen(rta));
			  write(connfd,dd,strlen(dd) );
			  
			  
        
	    
      }else{
	strcpy(prot,"HTTP/1.0 404 Not Found\nContent-Length: 26\nContent-Type: text/html\n\n<h1>404 Not Found :'(</h1>\n\n");
	write(connfd,prot, strlen(prot));
	
      }
      
}else{ // si el link esta incorrecto:
strcpy(prot,"HTTP/1.0 404 Not Found\nContent-Length: 26\nContent-Type: text/html\n\n<h1>404 Not Found :'(</h1>\n\n");
	write(connfd,prot, strlen(prot));
}
		  close(connfd);
		  close(arch);
		  return 0;
		  
		  
		  }
		  }
		  
		  
    
    close(connfd);
   
	return 0;
} 
