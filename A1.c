/*Create a file with hole in it.*/
#include <stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<fcntl.h>


int main()
{
	int fd;
	char msg1[] = "abcdefghij";
	char msg2[] = "ABCDEFGHIJ";

		fd = open("test.txt",O_CREAT | O_WRONLY);
	if(fd<0)

{
	printf("\n failed to create file\n");
	exit(1);
}

	write(fd,msg1,10);
	lseek(fd,1024L,SEEK_CUR);
	write(fd,msg2,10);
	close(fd);
return 0;
}

