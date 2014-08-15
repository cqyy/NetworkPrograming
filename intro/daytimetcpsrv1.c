#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<time.h>

/**
 * A simple server,receive connection from client,print the ip address of 
 * the client and the time it arrives,and then close the connection.
 */

int main(int argc,char **argv)
{
	int 	              listenfd,confd;
	socklen_t	      len;
	char		      buff[100];
	struct sockaddr_in    servaddr,cliaddr;
	time_t		      ticks;
	
	listenfd = socket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(8089);

	if(bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr))==-1){
		fputs("error when bind port\n",stderr);
		exit(1);
	};
	
	if(listen(listenfd,5)==-1){
		 fputs("error when listen\n",stderr);
		 exit(1);
	};

	for(;;){
		len = sizeof(cliaddr);
		confd = accept(listenfd,(struct sockaddr*)&cliaddr,&len);
		printf("New connection from %s,port %d\n",
			inet_ntop(AF_INET,&cliaddr.sin_addr,buff,sizeof(buff)),
			ntohs(cliaddr.sin_port));
		ticks = time(NULL);
		snprintf(buff,sizeof(buff),"%s\r\n",ctime(&ticks));
		write(confd,buff,strlen(buff));
		close(confd);
	}

}
