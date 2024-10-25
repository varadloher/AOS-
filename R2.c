/*write C program that will only list all regular files in alphabetical order from current directory */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

#define MAX_FILES 1024

// Structure to hold file names for sorting
typedef struct {
    char *name;
} FileEntry;

// Comparison function for qsort
int compare(const void *a, const void *b) {
    FileEntry *fileA = (FileEntry *)a;
    FileEntry *fileB = (FileEntry *)b;
    return strcmp(fileA->name, fileB->name);
}

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;
    FileEntry files[MAX_FILES];
    int count = 0;

    // Open the current directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return EXIT_FAILURE;
    }

    // Read entries from the directory
    while ((entry = readdir(dir)) != NULL) {
        // Ignore "." and ".."
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            // Get file status
            if (stat(entry->d_name, &fileStat) == 0) {
                // Check if it's a regular file
                if (S_ISREG(fileStat.st_mode)) {
                    // Add to the list of files
                    files[count].name = strdup(entry->d_name); // Duplicate the name
                    count++;
                }
            }
        }
    }

    // Close the directory
    closedir(dir);

    // Sort the file names alphabetically
    qsort(files, count, sizeof(FileEntry), compare);

    // Print the sorted list of regular files
    printf("Regular files in alphabetical order:\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", files[i].name);
        free(files[i].name); // Free the duplicated name
    }

    return EXIT_SUCCESS;
}
