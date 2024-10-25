/*Write a C program to send SIGALRM signal by child process to parent process and parent process make a provision to catch the signal and display alarm is fired.(Use Kill, fork, signal and sleep system call)	*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/resource.h>

int main()
{
    int n;
    printf("Enter the number of child processes to create: ");
    scanf("%d", &n);

    pid_t pid;
    struct rusage usage;
    long total_user_time_sec = 0;
    long total_user_time_usec = 0;
    long total_sys_time_sec = 0;
    long total_sys_time_usec = 0;

    // Create 'n' child processes
    for (int i = 0; i < n; i++)
{
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            // Child process: Perform some task and exit
            printf("Child process %d (PID: %d) is running.\n", i + 1, getpid());
            // Simulate work with a sleep call (can be replaced by actual work)
            sleep(1 + (i % 3));  // Children take varying time to finish
            exit(0);
        }
}

    // Parent process: Wait for all child processes and accumulate time
    for (int i = 0; i < n; i++)
{
        int status;
        if (wait3(&status, 0, &usage) == -1)
        {
            perror("wait3");
            exit(EXIT_FAILURE);
        }

        // Accumulate user and system time from each child process
        total_user_time_sec += usage.ru_utime.tv_sec;
        total_user_time_usec += usage.ru_utime.tv_usec;
        total_sys_time_sec += usage.ru_stime.tv_sec;
        total_sys_time_usec += usage.ru_stime.tv_usec;
}

    // Adjust time in microseconds to seconds if necessary
    total_user_time_sec += total_user_time_usec / 1000000;
    total_user_time_usec = total_user_time_usec % 1000000;

    total_sys_time_sec += total_sys_time_usec / 1000000;
    total_sys_time_usec = total_sys_time_usec % 1000000;

    // Display cumulative time spent by children in user and kernel mode
    printf("\nTotal cumulative time spent by children:\n");
    printf("User time: %ld seconds, %ld microseconds\n", total_user_time_sec, total_user_time_usec);
    printf("Kernel (system) time: %ld seconds, %ld microseconds\n", total_sys_time_sec, total_sys_time_usec);

    return 0;
}

