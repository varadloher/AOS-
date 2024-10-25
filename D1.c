/*write  a c prog to take multiple file as a command line arg and print their sizes*/
#include<stdio.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<sys/sysmacros.h>
#include<fcntl.h>

int main(int argc, char *argv[])
{
        int i=0;
	struct stat fileStat;

	for(i=0;i<argc;i++)
	{
		printf("%s \n",argv[i]);
		stat(argv[i],&fileStat);
		printf("Size of the file '%s': %lld bytes\n",argv[i],(long long)fileStat.st_size);
	}
	return 0;
}

