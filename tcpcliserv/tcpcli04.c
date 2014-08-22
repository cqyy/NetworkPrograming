#include "../header.h"
#include "strcli.h"
/*
 * Create 5 connection to server at the same time,
 * and use the first to echo.
 * This is for server testing at clear zoobie child.
 */

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
