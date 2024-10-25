/* write a C Program that demonstrates redirection of standard output to a file. */
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

    // Redirect standard output (stdout) to the file
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    // Close the original file descriptor since we no longer need it
    close(fd);

    // Now any printf statements will go to output.txt
    printf("This will be written to the file output.txt\n");
    printf("Hello, World!\n");

    // Close standard output
    fflush(stdout);  // Flush the output buffer
    return EXIT_SUCCESS;
}

	

