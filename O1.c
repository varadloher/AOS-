/*  Write a C program to create an unnamed pipe. The child process will write
following three messages to pipe and parent process display it.
Message1 = “Hello World”
Message2 = “Hello SPPU”
Message3 = “Linux is Funny”  */


#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#define MSGSIZE 16

char *msg1 = "Hello World";
char *msg2 = "Hello SPPU";
char *msg3 = "Linux is funny";
int main()

{
int fd[2],i;
char buff[MSGSIZE];
if(pipe(fd)<0)
exit(1);

write(fd[1],msg1,MSGSIZE);
write(fd[1],msg2,MSGSIZE);
write(fd[1],msg3,MSGSIZE);
for(i=0;i<3;i++)

{
read(fd[0],buff,MSGSIZE);
printf("\n%s",buff);
}

return 0;
}

