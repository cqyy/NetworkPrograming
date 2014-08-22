#include "../header.h"
/* select demo.
 */

void str_cli(FILE *fp,int sockfd)
{	
	int maxfdp1,stdeof;
	int sel,fn,n;
	fd_set rset;
	char buff[100];
	
	fn = fileno(fp);
	stdeof = 0;
	FD_ZERO(&rset);

	for(;;){
		if(stdeof == 0)
			FD_SET(fn,&rset);
		FD_SET(sockfd,&rset);
		maxfdp1 = ((fn > sockfd )?fn:sockfd) + 1;

		if ( (sel = select(maxfdp1,&rset,NULL,NULL,NULL)) <= 0){
			if( (sel < 0 && errno == EINTR) || sel == 0)
				continue;
		}

		if(FD_ISSET(sockfd,&rset)){                        //data avaliable from network
			if( ( n = readline(sockfd,buff,sizeof(buff))) == 0){
				if (stdeof == 1)
					return;       ///normal termination
				fputs("error:server terminated prematurally\n",stderr);
				exit(1);
			}
			writen(fileno(stdout),buff,n);
		}

		if(FD_ISSET(fn,&rset)){
			if ( (n = read(fn,buff,sizeof(buff))) == 0){
				stdeof = 1;
				shutdown(sockfd,SHUT_WR);	//send FIN
				FD_CLR(fn,&rset);
				continue;
			}	
			writen(sockfd,buff,n);
		}
	}
}
