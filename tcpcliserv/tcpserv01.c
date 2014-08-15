#include "../header.h"
#include "../readn.c"
#include "../writen.c"

int main(int argc,char **argv)
{
	sockaddr_t addr,cliaddr;
	int serfd,clifd;
	int clilen;
	int chipid;

	bzero(&addr,sizeof(addr));
	serfd = sock(AF_INET,SOCK_STREAM,0);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = 9002;
	Bind(serfd,(struct sockaddr*)&addr,sizeof(addr));
	Listen(serfd,10);

	for(;;){
		clilen = sizeof(cliaddr);
		clifd = accept(serfd,(struct sockaddr*)&cliaddr,&clilen);
		if( (chipid = fork()) == 0){
			close(serfd);
			str_echo(clifd);
			close(clifd);
		}
		close(clifd);
	}
}

void str_echo(int fd)
{
	char buff[100];
	size_t len;
	
	len = readn(fd,buff,sizeof(buff));
	writen(fd,buff,len);
}
