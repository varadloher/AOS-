/* Write a C program to display the last access and modified time of a given file  */
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

void display_file_times(const char *filename) {
    struct stat fileStat;

    // Get file status
    if (stat(filename, &fileStat) != 0) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    // Convert time from seconds to human-readable format
    char accessTime[100];
    char modifyTime[100];
    struct tm *tm_info;

    // Last access time
    tm_info = localtime(&fileStat.st_atime);
    strftime(accessTime, sizeof(accessTime), "%Y-%m-%d %H:%M:%S", tm_info);

    // Last modified time
    tm_info = localtime(&fileStat.st_mtime);
    strftime(modifyTime, sizeof(modifyTime), "%Y-%m-%d %H:%M:%S", tm_info);

    // Display the times
    printf("File: %s\n", filename);
    printf("Last Access Time: %s\n", accessTime);
    printf("Last Modified Time: %s\n", modifyTime);
}

int main(int argc, char *argv[]) {
    // Check if the filename is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    display_file_times(argv[1]);

    return EXIT_SUCCESS;
}


