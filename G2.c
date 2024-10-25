/* Write a C program which blocks SIGOUIT signal for 5 seconds. After 5 second process checks any occurrence of quit signal during this period, if so, it unblock the signal. Now another occurrence of quit signal terminates the program. (Use sigprocmask() and sigpending() )  */ 
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main() {
    sigset_t blockSet, oldSet, pendingSet;

    // Initialize the signal set to block SIGQUIT
    sigemptyset(&blockSet);
    sigaddset(&blockSet, SIGQUIT);

    // Block SIGQUIT and save the old signal mask
    sigprocmask(SIG_BLOCK, &blockSet, &oldSet);

    printf("SIGQUIT is blocked for 5 seconds. Try sending SIGQUIT (Ctrl+\\)\n");

    // Sleep for 5 seconds
    sleep(5);

    // Check if SIGQUIT was pending during the block period
    sigpending(&pendingSet);
    if (sigismember(&pendingSet, SIGQUIT)) {
        printf("SIGQUIT was received during the block period. Unblocking now.\n");
    } else {
        printf("No SIGQUIT was received during the block period.\n");
    }

    // Unblock SIGQUIT
    sigprocmask(SIG_UNBLOCK, &blockSet, NULL);

    // Wait for another occurrence of SIGQUIT
    printf("SIGQUIT is now unblocked. Send SIGQUIT (Ctrl+\\) to terminate the program.\n");

    // Infinite loop to keep the program running until SIGQUIT is received
    while (1) {
        pause(); // Wait for signals
    }

    return 0;
}


