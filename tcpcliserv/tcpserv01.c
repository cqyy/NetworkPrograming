#include "../header.h"

/**
 * basic echo server,int wait-stop model.
 */

void str_echo(int fd)
{
        char buff[100];
        size_t len;
again:
	while( (len = read(fd,buff,sizeof(buff))) > 0 ){
		writen(fd,buff,len);
	}
	if (len < 0)
		if (errno == EINTR)
			goto again;
		else
			return;
}

int main(int argc,char **argv)
{
	struct sockaddr_in addr,cliaddr;
	int listenfd,clifd;
	socklen_t clilen;
	int chipid;
	
	fputs("starting server\n",stdout);
	bzero(&addr,sizeof(addr));
	listenfd = socket(AF_INET,SOCK_STREAM,0);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(9002);
	Bind(listenfd,(struct sockaddr*)&addr,sizeof(addr));
	Listen(listenfd,10);
	
	fputs("server start on port 9002\n",stdout);
	
	for(;;){
		clilen = sizeof(cliaddr);
		clifd = accept(listenfd,(struct sockaddr*)&cliaddr,&clilen);
		if( (chipid = fork()) == 0){
			close(listenfd);
			str_echo(clifd);
			close(clifd);
			exit(0);
		}
		close(clifd);
	}
}
