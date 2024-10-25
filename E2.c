#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void block_signals() {
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGQUIT);
    sigprocmask(SIG_BLOCK, &mask, NULL);
}

int main() {
    int pipefd[2];

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Block SIGINT and SIGQUIT signals
    block_signals();

    // Create first child process to execute `ls -l`
    pid_t pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // Child process 1: Execute `ls -l`
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe
        close(pipefd[0]); // Close unused read end
        close(pipefd[1]); // Close write end after duplicating
        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls");
        exit(EXIT_FAILURE);
    }

    // Create second child process to execute `wc -l`
    pid_t pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        // Child process 2: Execute `wc -l`
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to pipe
        close(pipefd[1]); // Close unused write end
        close(pipefd[0]); // Close read end after duplicating
        execlp("wc", "wc", "-l", NULL);
        perror("execlp wc");
        exit(EXIT_FAILURE);
    }

    // Parent process
    close(pipefd[0]); // Close read end of the pipe
    close(pipefd[1]); // Close write end of the pipe

    // Wait for both child processes to complete
    wait(NULL);
    wait(NULL);

    return 0;
}

