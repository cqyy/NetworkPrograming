#include "header.h"

size_t readn(int fd,void *vptr,size_t n)
{
        ssize_t nread;
        size_t nleft;
        char *ptr;

        ptr = (char*)vptr;
        nleft = n;
        while(nleft >0){
                if( (nread = read(fd,ptr,nleft)) <= 0 ){
                        if( nread < 0 && errno == EINTR){
                                nread = 0;
                                break;
                        }else
                                return (-1);
                }
                nleft -= nread;
                ptr   += nread;
        }
        return (n - nleft);
}

size_t writen(int fd,void *vptr,size_t n)
{
        ssize_t nwrite,nleft;
        char   *ptr;

        ptr = vptr;
        nleft = n;

        while(nleft > 0){
                if( (nwrite = write(fd,ptr,nleft)) <= 0){
                        if(nwrite <0 && errno == EINTR){
                                nwrite = 0;
                                break;
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
                fputs("listen error",stderr);
        }

}

void Bind(int fd,const struct sockaddr *addr,socklen_t len)
{
	if( bind(fd,addr,len) != 0){
		fputs("bind error);
	}
}
