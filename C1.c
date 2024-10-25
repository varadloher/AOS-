/*take a multiple file as command line argumentsand print their inode number*/
#include<stdio.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<sys/sysmacros.h>
#include<fcntl.h>

int main(int argc, char *argv[])
{
        int i=0;
	struct stat s;

	for(i=0;i<argc;i++)
	{
		printf("%s \n",argv[i]);
		stat(argv[i],&s);
		printf("I-node number : %ld\n",(long)s.st_ino);
	}
}

