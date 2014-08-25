#include "../header.h"

int main(int argc,char **argv)
{
	int client[100],nready;
	int i,maxi,maxfd,listenfd,connfd,sockfd;
	ssize_t n;
	fd_set allset,rset;
	char buf[100];
	socklen_t clilen;
	struct sockaddr_in cliaddr,servaddr;
	
	maxi = -1;
	listenfd = socket(AF_INET,SOCK_STREAM,0);
	maxfd = listenfd;

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9877);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	for(i = 0; i < 100; i++){
		client[i] = -1;
	}
	Bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	Listen(listenfd,100);
	FD_ZERO(&allset);
	FD_SET(listenfd,&allset);
	printf("server start at post %d\n",9877);

	for(;;){
		rset = allset;
		nready = select(maxfd+1,&rset,NULL,NULL,NULL);
		/*receive new connection*/	
		if(FD_ISSET(listenfd,&rset)){
			clilen = sizeof(cliaddr);
			connfd = accept(listenfd,(struct sockaddr*)&cliaddr,&clilen);
			for(i = 0; i < 100; i++){
				if(client[i] < 0){
					client[i] = connfd;
					if(connfd > maxfd)
						maxfd = connfd;
					if(i > maxi)
						maxi = i;
					break;
					}
			}
			if( i == 100){
				fputs("too much connection\n",stderr);
				exit(1);
			}
			FD_SET(connfd,&allset);
			printf("maxfd %d,maxi %d\n",maxfd,maxi);
			if ( --nready == 0){
				continue;
			}
		}
		/*read and write back*/
		for( i = 0; i <= maxi; i++){
			if( (sockfd = client[i]) < 0)
				continue;
			if( FD_ISSET(sockfd,&rset)){
				if ( (n = read(sockfd,buf,sizeof(buf))) == 0){
					close(sockfd);
					client[i] = -1;
					FD_CLR(sockfd,&allset);
				}else
					writen(sockfd,buf,n);
				if( --nready == 0)
					continue;
			}
		}
	}
}
