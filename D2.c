/*.Write a C program that illustrates suspending and resuming processes using signals.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void handler(int signum) {
    // Signal handler for SIGUSR1
    if (signum == SIGUSR1) {
        printf("Child process: Received SIGUSR1. Resuming...\n");
    }
}

int main() {
    pid_t pid;
    struct sigaction sa;

    // Setting up the signal handler for SIGUSR1
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        while (1) {
            printf("Child process: Running...\n");
            sleep(2);
        }
    } else { // Parent process
        sleep(5); // Allow the child to run for a bit
        printf("Parent process: Sending SIGSTOP to child...\n");
        kill(pid, SIGSTOP); // Suspend the child process

        sleep(5); // Suspend for a while

        printf("Parent process: Sending SIGCONT to child...\n");
        kill(pid, SIGCONT); // Resume the child process

        // Wait for the child process to finish
        wait(NULL);
        printf("Parent process: Child has terminated.\n");
    }

    return 0;
}

