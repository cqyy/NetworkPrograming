#include "../header.h"

/*
 * Create 5 connection to server at the same time,
 * and use the first to echo.
 * This is for server testing at clear zoobie child.
 */

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

int main(int argc,char **argv)
{
	int i ,sockfd[5];
	struct sockaddr_in servaddr;

	if(argc != 2){
		fputs("usage: <sockaddr>\n",stdout);
	}

	for(int i = 0;i < 5; i++){
		sockfd[i] = socket(AF_INET,SOCK_STREAM,0);
		bzero(&servaddr,sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(9877);
		inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
		Connect(sockfd[i],(struct sockaddr*)&servaddr,sizeof(servaddr));
	}
	str_cli(stdin,sockfd[0]);
	exit(0);

}
