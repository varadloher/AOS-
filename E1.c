/* Write a C program to find whether a given file is present in current directory or not */
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    char filename[256];  // Buffer to hold the filename
    struct stat fileStat;

    // Prompt the user to enter the filename
    printf("Enter the filename to check: ");
    scanf("%255s", filename);  // Read filename safely

    // Check the file status using stat
    if (stat(filename, &fileStat) == 0) {
        // File exists
        printf("The file '%s' is present in the current directory.\n", filename);
    } else {
        // File does not exist
        printf("The file '%s' is not present in the current directory.\n", filename);
    }

    return 0;
}


