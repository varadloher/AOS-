/* Write a C program to get and set the resource limits such as files, memory associated with a process.  */
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>

void print_limits(const char *resource_name, struct rlimit *rl) {
    printf("%s:\n", resource_name);
    printf("  Soft Limit: %lu\n", (unsigned long)rl->rlim_cur);
    printf("  Hard Limit: %lu\n", (unsigned long)rl->rlim_max);
}

int main() {
    struct rlimit rl;

    // Get and display the maximum number of open files
    if (getrlimit(RLIMIT_NOFILE, &rl) == 0) {
        print_limits("Maximum number of open files", &rl);
    } else {
        perror("getrlimit");
    }

    // Get and display the maximum size of virtual memory
    if (getrlimit(RLIMIT_AS, &rl) == 0) {
        print_limits("Maximum size of virtual memory", &rl);
    } else {
        perror("getrlimit");
    }

    // Modify the limits
    printf("\nSetting new limits...\n");

    // Set new limit for maximum number of open files
    rl.rlim_cur = 1024;  // New soft limit
    rl.rlim_max = 2048;  // New hard limit
    if (setrlimit(RLIMIT_NOFILE, &rl) != 0) {
        perror("setrlimit (RLIMIT_NOFILE)");
    } else {
        printf("Successfully set new limits for maximum open files.\n");
    }

    // Set new limit for maximum size of virtual memory
    rl.rlim_cur = 1024 * 1024 * 1024;  // 1 GB
    rl.rlim_max = 2 * 1024 * 1024 * 1024;  // 2 GB
    if (setrlimit(RLIMIT_AS, &rl) != 0) {
        perror("setrlimit (RLIMIT_AS)");
    } else {
        printf("Successfully set new limits for maximum virtual memory size.\n");
    }

    // Get and display the updated limits
    printf("\nUpdated Limits:\n");
    if (getrlimit(RLIMIT_NOFILE, &rl) == 0) {
        print_limits("Maximum number of open files", &rl);
    } else {
        perror("getrlimit");
    }

    if (getrlimit(RLIMIT_AS, &rl) == 0) {
        print_limits("Maximum size of virtual memory", &rl);
    } else {
        perror("getrlimit");
    }

    return EXIT_SUCCESS;
}
