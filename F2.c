/*. Write a C program which creates a child process and child process catches a signal SIGHUP, SIGINT and SIGQUIT. The Parent process send a SIGHUP or SIGINT signal after every 3 seconds, at the end of 15 second parent send SIGQUIT signal to child and child terminates by displaying message "My Papa has Killed me!!!”.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void handle_sighup(int sig) {
    printf("Child: Caught SIGHUP (signal %d)\n", sig);
}

void handle_sigint(int sig) {
    printf("Child: Caught SIGINT (signal %d)\n", sig);
}

void handle_sigquit(int sig) {
    printf("My Papa has Killed me!!!\n");
    exit(0);  // Terminate the child process
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        signal(SIGHUP, handle_sighup);
        signal(SIGINT, handle_sigint);
        signal(SIGQUIT, handle_sigquit);

        // Keep the child process running to catch signals
        while (1) {
            pause();  // Wait for signals
        }
    } else {
        // Parent process
        for (int i = 0; i < 5; i++) {
            sleep(3);  // Wait for 3 seconds
            if (i < 4) {
                // Send SIGHUP or SIGINT
                if (i % 2 == 0) {
                    kill(pid, SIGHUP);  // Send SIGHUP on even iterations
                } else {
                    kill(pid, SIGINT);  // Send SIGINT on odd iterations
                }
            }
        }
        sleep(3);  // Wait for another 3 seconds before sending SIGQUIT
        kill(pid, SIGQUIT);  // Send SIGQUIT signal

        // Wait for child to terminate
        wait(NULL);
    }

    return 0;
}

