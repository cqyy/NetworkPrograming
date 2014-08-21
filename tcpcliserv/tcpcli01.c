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

int main(int argc, char **argv)
{
	struct sockaddr_in seraddr;
	int fd;
	
	if(argc != 2){
		fputs("usage:<inetaddress>\n",stderr);
	}
	
	fd = socket(AF_INET,SOCK_STREAM,0);
	
	bzero(&seraddr,sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(9877);
	inet_pton(AF_INET,argv[1],&seraddr.sin_addr);	
	Connect(fd,(struct sockaddr *)&seraddr,sizeof(seraddr));
	printf("connected to server at %s\n",argv[1]);
	str_cli(stdin,fd);
	exit(0);
}
