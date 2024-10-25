/* write a program to read the contents of current dirctory.display the name of the all files and subdirectories and number of all subdirectories in current directory*/
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
    DIR *directory;
    struct dirent *entry;
    int subDirCount = 0;

    // Open the current directory
    directory = opendir(".");
    if (directory == NULL) {
        perror("opendir");
        return EXIT_FAILURE;
    }

    // Read the contents of the directory
    printf("subdirectories of the current directory:\n");
    while ((entry = readdir(directory)) != NULL) {
        // Skip the "." and ".." entries
        if (entry->d_name[0] != '.') {
            printf("%s\n", entry->d_name);
            subDirCount++;
        }
    }

    // Close the directory
    closedir(directory);

    // Display the total count
    printf("\nTotal number subdirectories: %d\n", subDirCount);

    return EXIT_SUCCESS;
}


