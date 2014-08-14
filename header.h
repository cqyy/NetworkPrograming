#include<stdlib.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<netinet/in.h>

/*
 * read n bytes from descriptor
 */

ssize_t readn(int fd,void *vptr,size_t n)
{
	ssize_t nread;
	size_t nleft;
	char *ptr;

	ptr = vprt;
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

ssize_t writen(int fd,void *vptr,size_t n)
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

void Bind(int fd,sockaddr *addr,socklen_t addrlen)
{
	if( bind(fd,addr,addr_len) !=0){
		fputs("bind error",stderr);
	}
}
