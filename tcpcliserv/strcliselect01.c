#include "../header.h"
/* select demo.
 */

void str_cli(FILE *fp,int sockfd)
{	
	int maxfdp1;
	int sel,fn;
	fd_set rset;
	char recvline[100],sendline[100];
	
	fn = fileno(fp);
	FD_ZERO(&rset);
	for(;;){
		FD_SET(fn,&rset);
		FD_SET(sockfd,&rset);
		maxfdp1 = ((fn > sockfd )?fn:sockfd) + 1;

		if ( (sel = select(maxfdp1,&rset,NULL,NULL,NULL)) <= 0){
			if( (sel < 0 && errno == EINTR) || sel == 0)
				continue;
		}

		if(FD_ISSET(sockfd,&rset)){                        //data avaliable from network
			if( readline(sockfd,recvline,sizeof(recvline)) == 0){
				fputs("error:server terminated prematurally\n",stderr);
				exit(1);
			}
			fputs(recvline,stdout);
		}

		if(FD_ISSET(fn,&rset)){
			if ( readline(fn,sendline,sizeof(sendline)) == 0)
				return;
			writen(sockfd,sendline,strlen(sendline));
		}
	}
}
