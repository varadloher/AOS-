/* handle the two-way communication between parent and child process using pipe. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
    {
    int parent_to_child_pipe[2];
    int child_to_parent_pipe[2];
    pid_t child_pid;

    if (pipe(parent_to_child_pipe) == -1 || pipe(child_to_parent_pipe) == -1){
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
   }

    child_pid = fork();

    if (child_pid < 0){
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0){
        // This is the child process

        // Close unused ends of the pipes
        close(parent_to_child_pipe[1]);
        close(child_to_parent_pipe[0]);

        char message[] = "Hello from the child process!\n\n";
        char received_message[100];

        // Read from the parent and write to the parent
        read(parent_to_child_pipe[0], received_message, sizeof(received_message));
        printf("Child received: %s\n\n", received_message);
        write(child_to_parent_pipe[1], "Message from child to parent", 28);

        // Close the ends of the pipes in the child
        close(parent_to_child_pipe[0]);
        close(child_to_parent_pipe[1]);

        exit(EXIT_SUCCESS);
    }

   else{
        // This is the parent process

        // Close unused ends of the pipes
        close(parent_to_child_pipe[0]);
        close(child_to_parent_pipe[1]);

        char message[] = "Hello from the parent process!";
        char received_message[100];

        // Write to the child and read from the child
        write(parent_to_child_pipe[1], message, sizeof(message));
        read(child_to_parent_pipe[0], received_message, sizeof(received_message));
        printf("Parent received: %s\n", received_message);

        // Close the ends of the pipes in the parent
        close(parent_to_child_pipe[1]);
        close(child_to_parent_pipe[0]);
   }

    return 0;
}

