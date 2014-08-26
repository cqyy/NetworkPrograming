#include<stdlib.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#include<sys/select.h>
#include<sys/time.h>
#include<pool.h>


typedef void Sigfunc(int);

ssize_t readn(int fd,void *vptr,size_t len);

ssize_t readline(int fd, void *vptr,size_t maxlen);

ssize_t writen(int fd,void *vptr,size_t len);

void Listen(int fd,int backlog);

void Bind(int fd,const struct sockaddr *addr,socklen_t len);

void Connect(int fd,const struct sockaddr *addr,socklen_t len);

Sigfunc * singnal(int signo,Sigfunc *func);
