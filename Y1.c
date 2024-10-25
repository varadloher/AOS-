/*write a C program to get and set the resource limits such as files,memory associated with a process*/
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <stdlib.h>

void print_limit(const char *limit_name, int resource) {
    struct rlimit limit;

    // Get the current limit
    if (getrlimit(resource, &limit) == 0) {
        printf("%s: \n", limit_name);
        printf("  Soft limit: %ld\n", (long)limit.rlim_cur);
        printf("  Hard limit: %ld\n\n", (long)limit.rlim_max);
    } else {
        perror("getrlimit");
    }
}

void set_limit(int resource, rlim_t soft, rlim_t hard) {
    struct rlimit new_limit;

    new_limit.rlim_cur = soft; // Soft limit
    new_limit.rlim_max = hard; // Hard limit

    // Set the new limit
    if (setrlimit(resource, &new_limit) == -1) {
        perror("setrlimit");
    }
}

int main() {
    // Display current limits
    printf("Current resource limits:\n");
    print_limit("Max number of open files (RLIMIT_NOFILE)", RLIMIT_NOFILE);
    print_limit("Max virtual memory size (RLIMIT_AS)", RLIMIT_AS);
    print_limit("Max CPU time (RLIMIT_CPU)", RLIMIT_CPU);

    // Set new limits
    printf("Setting new limits...\n");

    // Increase the max number of open files
    set_limit(RLIMIT_NOFILE, 1024, 2048); // Soft limit: 1024, Hard limit: 2048

    // Decrease the max virtual memory size
    set_limit(RLIMIT_AS, 1024L * 1024L * 1024L, 2L * 1024L * 1024L * 1024L); // Soft: 1 GB, Hard: 2 GB

    // Set the max CPU time to 1 minute (60 seconds)
    set_limit(RLIMIT_CPU, 60, 120); // Soft limit: 60 seconds, Hard limit: 120 seconds

    // Display updated limits
    printf("Updated resource limits:\n");
    print_limit("Max number of open files (RLIMIT_NOFILE)", RLIMIT_NOFILE);
    print_limit("Max virtual memory size (RLIMIT_AS)", RLIMIT_AS);
    print_limit("Max CPU time (RLIMIT_CPU)", RLIMIT_CPU);

    return 0;
}

