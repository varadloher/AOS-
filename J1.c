/* write a c program to identify the type(dirctory,character device,block device,regular file,FIFO or pipe,symbolic link or socket)of given file using stat() system call. */

#include<stdio.h>
#include<sys/stat.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s <file_path>\n",argv[0]);
		return 1;
	}

	struct stat fileStat;

	if (stat(argv[1], &fileStat) < 0)
	{
		perror("stat");
		return 1;
	}

	printf("File type: ");

	if (S_ISDIR(fileStat.st_mode))
	{
		printf("Directory\n");
	}
	else if (S_ISCHR(fileStat.st_mode))
	{
		printf("Character Device\n");
	}
	else if (S_ISBLK(fileStat.st_mode))
	{
		printf("Block Device\n");
	}
	else if (S_ISREG(fileStat.st_mode))
	{
		printf("Regular File\n");
	}
	else if (S_ISFIFO(fileStat.st_mode))
	{
		printf("FIFO or pipe\n");
	}
	else if (S_ISLNK(fileStat.st_mode))
	{
		printf("Symbolic Link\n");
	}
	else if (S_ISSOCK(fileStat.st_mode))
	{
		printf("Socket\n");
	}
	else
	{
		printf("Unknown\n");
	}
	return 0;
}

