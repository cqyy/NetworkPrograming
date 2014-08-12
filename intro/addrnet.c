#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>

//practice function inet_aton and inet_ntoa
//int inet_aton(const char *strptr,struct in_addr *addrptr)   address to net
//char *inet_ntoa(struct in_addr inaddr)   net to address

int main(int argc,char ** argv)
{
	char *strptr;
	struct in_addr addrptr;
	if (argc != 2){
                fputs("usage: <ip addr>\n",stderr);
		exit(1);
        }
	if(!(inet_aton(argv[1],&addrptr))){
		printf("invalid address\n");
		exit(1);
	}else {
		printf("net address : %d\n",addrptr.s_addr);	
	}
	strptr = inet_ntoa(addrptr);
	printf("original address : %s\n",strptr);
	exit(0);	
}
