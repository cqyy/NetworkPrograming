#include "../header.h"

int main(int argc,char **argv)
{
	int i,maxi,listenfd,connfd,sockfd,nready;
	ssize_t n;
	char buf[100];
	socklen_t clilen;
	struct sockaddr_in cliaddr,servaddr;
	struct poolfd client[100];          	
	listenfd = socket(AF_INET,SOCK_STREAM,0);
	maxfd = listenfd;

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9877);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	client[0].fd = listenfd;
	client[0].events = POOLRDNORM;	
	for(i = 1; i < 100; i++){
		client[i].fd = -1;
	}
	maxi = 0;
	Bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	Listen(listenfd,100);
	printf("server start at post %d\n",9877);

	for(;;){
		nready = pool(&client,maxi+1,INFTIM);
		/*receive new connection*/	
		if( client[0].revents & POOLRDNORM)
			clilen = sizeof(cliaddr);
			connfd = accept(listenfd,(struct sockaddr*)&cliaddr,&clilen);
			for(i = 0; i < 100; i++){
				if(client[i].fd < 0){
					client[i].fd = connfd;
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
			client[i].events = POOLRDNORM;
			if ( --nready == 0){
				continue;
			}
		}
		/*read and write back*/
		for( i = 1; i <= maxi; i++){
			if( (sockfd = client[i].fd) < 0)
				continue;
			if( client[i].revents & (POOLRDNORM | POOLERR)){
				if( (n = read(sockfd,buf,sizeof(buf)) < 0){
					if(errno == ECONNRESET){
						/**connection reset by client*/
						close(sockfd);
						client[i].fd = -1;
					}else
						fputs("read error\n",stderr);	
				}else if ( n == 0){
					close(sockfd);
					client[i].fd = -1;
				}else
					writen(sockfd,buf,n);
				if( --nready == 0)
					break;
			}
		}
	}
}
