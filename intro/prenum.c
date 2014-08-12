#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>

/*
 * practice inet_pton adn inet_ntop
 * p -- presentation    n -- numeric
 * int inet_pton(int family,cont char *strptr,void *addrptr)
 * const char *inet_ntop(int family,const void *addrptr,char *strptr,size_t len)
 */

int main(int argc,char ** argv)
{
	struct sockaddr_in addr;
	char pre[INET_ADDRSTRLEN];
	
	if( argc != 2 ){
		fputs("error,usage: <ip addr>\n",stderr);
		exit(1);
	}
	if( (inet_pton(AF_INET,argv[1],&addr.sin_addr)) <= 0){
		fputs("error in inet_pton\n",stderr);
		exit(1);
	}else{
		printf("numeric value of ip address:%d\n",addr.sin_addr);
	}

	if( inet_ntop(AF_INET,&addr.sin_addr,pre,INET_ADDRSTRLEN) ){
		printf("original ip address : %s\n",&pre);
	}else{
		fputs("error in inet_ntop\n",stderr);
	}
	exit(0);
}
