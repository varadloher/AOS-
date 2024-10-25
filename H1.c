/*Write a C program to read the contents of current directory. Display the name of all regular files and no of files in current Directory.  */ 
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

int main() {
    DIR *directory;
    struct dirent *entry;
    struct stat fileStat;
    int fileCount = 0;

    // Open the current directory
    directory = opendir(".");
    if (directory == NULL) {
        perror("opendir");
        return EXIT_FAILURE;
    }

    // Read the contents of the directory
    printf("Regular files in the current directory:\n");
    while ((entry = readdir(directory)) != NULL) {
        // Construct the full path
        if (stat(entry->d_name, &fileStat) == 0) {
            // Check if it is a regular file
            if (S_ISREG(fileStat.st_mode)) {
                printf("%s\n", entry->d_name);
                fileCount++;
            }
        }
    }

    // Close the directory
    closedir(directory);

    // Display the total count of regular files
    printf("\nTotal number of regular files: %d\n", fileCount);

    return EXIT_SUCCESS;
}

