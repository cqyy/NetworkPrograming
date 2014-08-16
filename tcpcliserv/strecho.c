void str_echo(int fd)
{
	char buff[100];
	size_t len;
	
	len = readn(fd,buff,sizeof(buff));
	writen(fd,buff,len);
}
