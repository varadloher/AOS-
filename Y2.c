/*Write a C program which creates two files. The first file should have read and write permission to owner, group of owner and other users whereas second file has read and write permission to owner(use umask() function). Now turn on group-id and turn off group execute permission of first file. Set the read permission to all user for second file (use chmod() function).*/      
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    // Set umask to restrict permissions
    umask(0);

    // Create the first file with read and write permissions for owner, group, and others
    int fd1 = open("file1.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (fd1 == -1) {
        perror("Error creating file1.txt");
        return EXIT_FAILURE;
    }

    // Create the second file with read and write permissions for owner only
    int fd2 = open("file2.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd2 == -1) {
        perror("Error creating file2.txt");
        close(fd1);
        return EXIT_FAILURE;
    }

    // Change permissions of the first file:
    // Turn on group-id and turn off group execute permission
    if (chmod("file1.txt", (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH | S_ISGID) & ~S_IXGRP) == -1) {
        perror("Error setting permissions on file1.txt");
        close(fd1);
        close(fd2);
        return EXIT_FAILURE;
    }

    // Set read permission for all users on the second file
    if (chmod("file2.txt", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) == -1) {
        perror("Error setting permissions on file2.txt");
        close(fd1);
        close(fd2);
        return EXIT_FAILURE;
    }

    // Close the file descriptors
    close(fd1);
    close(fd2);

    printf("Files created and permissions set successfully.\n");
    return EXIT_SUCCESS;
}


