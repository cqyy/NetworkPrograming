#include<stdlib.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>

ssize_t readn(int fd,char *vptr,size_t len);

ssize_t writen(int fd,char *vptr,size_t len);

void Listen(int fd,int backlog);

void Bind(int fd, sockaddr *addr,socklen_t len);
