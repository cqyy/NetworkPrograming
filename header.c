#include "header.h"

ssize_t readn(int fd,void *vptr,size_t n)
{
        ssize_t nread;
        size_t nleft;
        char *ptr;

        ptr = (char*)vptr;
        nleft = n;
        while(nleft > 0){
                if( (nread = read(fd,ptr,nleft)) < 0 ){
                        if( errno == EINTR){
                                nread = 0;
                        }else
                                return (-1);
                }else if(nread == 0)
			break;           //EOF
		
                nleft -= nread;
                ptr   += nread;
        }
        return (n - nleft);
}

ssize_t readline(int fd,void *vptr,size_t n)
{
	
	size_t nleft;
	int nread;
	char c,*ptr;

	ptr = (char *)vptr;
	nleft = n;
	while( nleft > 0){
again:
		if ( (nread = read(fd,&c,1))==1){
			*ptr++ = c;
			nleft--;
			if ( c == '\n')
				break;
		}else if ( nread < 0 && errno == EINTR)	
			goto again;
		else if ( nread == 0){              //EOF
			*ptr = 0;
			return (n -nleft);
		}
		else 
			return (-1);	             //ERROR
	}
	*ptr = 0;
	return (n - nleft);
}

ssize_t writen(int fd,void *vptr,size_t n)
{
        ssize_t nwrite,nleft;
        char   *ptr;

        ptr = (char *)vptr;
        nleft = n;

        while(nleft > 0){
                if( (nwrite = write(fd,ptr,nleft)) <= 0){
                        if(nwrite < 0 && errno == EINTR){
                                nwrite = 0;
                        }else
                                return (-1);
                }
                nleft -= nwrite;
                ptr   += nwrite;
        }
        return n;
}

void Listen(int fd,int backlog)
{
        char *ptr;

        if( (ptr = getenv("LISTENQ")) != NULL){
                backlog = atoi(ptr);
        }

        if(listen(fd,backlog) < 0){
                fputs("listen error\n",stderr);
		exit(1);
        }

}

void Bind(int fd,const struct sockaddr *addr,socklen_t len)
{
	if( bind(fd,addr,len) != 0){
		fputs("bind error\n",stderr);
		exit(1);
	}
}

void Connect(int fd,const struct sockaddr *addr,socklen_t len)
{
	if(connect(fd,addr,len) !=0 ){
		fputs("connect error\n",stderr);
		exit(1);
	}
}

Sigfunc * singnal(int signo,Sigfunc *func)
{
	struct sigaction act,oact;

	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if( signo == SIGALRM){
#ifdef SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;    /* SunOS */
#endif
	}else {
#ifdef SA_RESTART
		act.sa_flags |= SA_RESTART;      /* SVR4*/
#endif
	}
	if(sigaction(signo,&act,&oact) < 0){
		return (SIG_ERR);
	}
	return (oact.sa_handler);
}
