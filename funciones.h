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
#include <sys/mman.h>
int buscar (char* palabm, char* buff);
int abrir();
//void buff(int arch, char* buffer);
char* palabrares(int connfd);
