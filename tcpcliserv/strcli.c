#include "../header.h"

void str_cli(FILE *fp,int fd)
{
	char sendline[100],recvline[100];

	while( fgets(sendline,sizeof(sendline),fp) != NULL){
		writen(fd,sendline,strlen(sendline));
		if ( readline(fd,recvline,sizeof(recvline)) == 0){
			fputs("str_cli:server terminated prematurely\n",stderr);
			exit(1);
		}
		fputs(recvline,stdout);
	}
}
