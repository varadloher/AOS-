/* print the type of file where  file name accepted through command line */
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return  
 1;
    }

    struct stat st;
    if (stat(argv[1], &st)  
 == -1) {
        perror("stat");
        return 1;
    }

    if (S_ISREG(st.st_mode)) {
        printf("%s is a regular file\n", argv[1]);
    } else if (S_ISDIR(st.st_mode)) {
        printf("%s is a directory\n", argv[1]);
    } else if (S_ISCHR(st.st_mode)) {
        printf("%s is a character device\n", argv[1]);
    } else if (S_ISBLK(st.st_mode)) {
        printf("%s is a block device\n", argv[1]);
    } else if (S_ISFIFO(st.st_mode)) {
        printf("%s is a FIFO (named pipe)\n", argv[1]);
    } else if (S_ISLNK(st.st_mode)) {
        printf("%s is a symbolic link\n", argv[1]);
    } else if (S_ISSOCK(st.st_mode)) {
        printf("%s is a socket\n", argv[1]);
    } else {
        printf("%s is an unknown file type\n", argv[1]);
    }

    return 0;
}
