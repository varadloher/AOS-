/* Write a C program that redirects standard output to a file output.txt. (use of dup and open system call).*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd;

    // Open the file output.txt for writing, create it if it doesn't exist
    fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Duplicate the file descriptor to standard output (stdout)
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Close the original file descriptor since it's no longer needed
    close(fd);

    // Now any printf statements will go to output.txt
    printf("This output will be redirected to the file output.txt\n");
    printf("Hello, World!\n");

    // Flush the output to ensure everything is written
    fflush(stdout);

    return EXIT_SUCCESS;
}
