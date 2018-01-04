#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>

#define MAXLEN 100
#define DEV_PATH "/dev/scull0"
int main(void)
{
	int fd,len;
	char inbuf[MAXLEN];
	char outbuf[MAXLEN]="scull dev test";
	char tmp_buf[MAXLEN];
	int i;
	for(i=0;i<10;i++)
	{
		fd=open(DEV_PATH,O_WRONLY);

		if(fd < 0)
		{
			perror("open device");
			exit(EXIT_FAILURE);
		}
		memset(tmp_buf,0,MAXLEN);
		sprintf(tmp_buf,"%d",i);
		strcat(outbuf, tmp_buf);

		len = write(fd,outbuf,strlen(outbuf)+1);

		if(len < 0)
		{
			perror("write device");
			close(fd);
			exit(EXIT_FAILURE);  
		}

		printf("write device %d bytes ok\n",len);

		close(fd);
		sleep(1);

		fd=open(DEV_PATH,O_RDONLY);

		if(fd < 0)
		{
			perror("open device");
			exit(EXIT_FAILURE);
		} 
		memset(inbuf,0,MAXLEN);
		len = read(fd,inbuf,len);

		if(len < 0)
		{
			perror("read device");
			close(fd);
			exit(EXIT_FAILURE);  
		} 

		printf("read device ok\n");
		printf("%s\n",inbuf);
	} 
}
