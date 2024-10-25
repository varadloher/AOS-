/*.Write a C program to send SIGALRM signal by child process to parent process and parent process make a provision to catch the signal and display alarm is fired.(Use Kill, fork, signal and sleep system call).*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function to handle SIGALRM signal in the parent process
void handle_alarm(int signum) {
    printf("Parent process: Alarm is fired!\n");
}

int main() {
    pid_t child_pid;

    // Set up the signal handler for SIGALRM
    signal(SIGALRM, handle_alarm);

    child_pid = fork();

    if (child_pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) { // Child process
        // Sleep for 3 seconds before sending the alarm
        sleep(3);
        printf("Child process (PID: %d): Sending SIGALRM to parent (PID: %d)...\n", getpid(), getppid());
        kill(getppid(), SIGALRM); // Send SIGALRM to the parent
        exit(0); // Terminate the child process
    } else { // Parent process
        // Wait for the child to finish
        wait(NULL);
        printf("Parent process (PID: %d): Child has terminated.\n", getpid());
    }

    return 0;
}

