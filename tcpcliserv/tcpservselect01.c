int main(int argc,char **argv)
{
	int client[100],nready;
	int i,maxi,maxfd,listenfd,connfd,sockfd;
	ssize_t n;
	fd_set allset,rset;
	char buf[100];
	socklen_t clilen;
	struct sockaddr_in cliaddr,servaddr;

	listenfd = socket(AF_INET,SOCK_STREAM,0);
	maxfd = listenfd;

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9877);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
}
