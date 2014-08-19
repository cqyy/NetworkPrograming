#include "../header.h"

void str_echo(int fd)
{
        char buff[100];
        size_t len;

	memset(buff, 0, sizeof(buff));
        len = read(fd,buff,sizeof(buff));
	if(len <= 0)
	{
		printf("read error\n");
		return;
	}
	buff[len] = '\0';
	printf("%s\n", buff);
        write(fd,buff,len);
}

int main(int argc,char **argv)
{
	struct sockaddr_in addr,cliaddr;
	int serfd,clifd;
	socklen_t clilen;
	int chipid;
	
	fputs("starting server\n",stdout);
	bzero(&addr,sizeof(addr));
	serfd = socket(AF_INET,SOCK_STREAM,0);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(9004);
	Bind(serfd,(struct sockaddr*)&addr,sizeof(addr));
	Listen(serfd,10);
	
	fputs("server start on port 9002\n",stdout);
	
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
