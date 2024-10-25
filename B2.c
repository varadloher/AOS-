/*.Write a C program which creates a child process to run linux/ unix command or any user defined program. The parent process set the signal handler for death of child signal and Alarm signal. If a child process does not complete its execution in 5 second then parent process kills child process.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t child_pid;

void handle_child_death(int signum) {
    int status;
    pid_t dead_child = wait(&status);
    if (dead_child == -1) {
        perror("wait");
    } else {
        printf("Child process (PID: %d) has terminated.\n", dead_child);
        if (WIFEXITED(status)) {
            printf("Child exited with status: %d\n", WEXITSTATUS(status));
        }
    }
}

void handle_alarm(int signum) {
    printf("Alarm went off! Killing the child process (PID: %d)!\n", child_pid);
    kill(child_pid, SIGKILL);
}

int main() {
    // Set up signal handlers
    signal(SIGCHLD, handle_child_death);
    signal(SIGALRM, handle_alarm);

    child_pid = fork();

    if (child_pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) { // Child process
        // Simulate a long-running process
        printf("Child process (PID: %d): Running...\n", getpid());
        while (1) {
            // Simulating work
            printf("Child process is working...\n");
            sleep(1); // Sleep to avoid busy waiting
        }
    } else { // Parent process
        // Set an alarm for 5 seconds
        alarm(5);

        // Wait for the child to complete or be killed
        while (1) {
            pause(); // Wait for signals
        }
    }

    return 0;
}

