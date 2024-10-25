  /*Generate child process to create unnamed pipe and parent process will read from it */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 100

int main() {
    int pipefd[2]; // Array to hold the file descriptors for the pipe
    pid_t pid;
    char buffer[BUFFER_SIZE];

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Create a child process
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process: close the read end of the pipe
        close(pipefd[0]);

        // Write a message to the pipe
        const char *message = "Hello from the child process!";
        write(pipefd[1], message, strlen(message) + 1); // +1 to include the null terminator

        // Close the write end
        close(pipefd[1]);
        exit(EXIT_SUCCESS);
    } else {
        // Parent process: close the write end of the pipe
        close(pipefd[1]);

        // Read the message from the pipe
        read(pipefd[0], buffer, BUFFER_SIZE);

        // Print the message received from the child
        printf("Parent received: %s\n", buffer);

        // Close the read end
        close(pipefd[0]);

        // Wait for the child process to finish
        wait(NULL);
    }

    return EXIT_SUCCESS;
}
