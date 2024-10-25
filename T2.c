/*Write a C program to display all the files from current directory and its subdirectory whose size is greater than ’n’ Bytes Where n is accepted from user through command line
 */
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void list_files(const char *path, size_t n) {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    // Open the directory
    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    // Read entries from the directory
    while ((entry = readdir(dir)) != NULL) {
        // Ignore "." and ".."
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            char fullPath[1024];
            snprintf(fullPath, sizeof(fullPath), "%s/%s", path, entry->d_name);

            // Get file status
            if (stat(fullPath, &fileStat) == 0) {
                // Check if it's a regular file
                if (S_ISREG(fileStat.st_mode) && fileStat.st_size > n) {
                    printf("%s (Size: %lld bytes)\n", fullPath, (long long)fileStat.st_size);
                }
                // If it's a directory, recurse into it
                else if (S_ISDIR(fileStat.st_mode)) {
                    list_files(fullPath, n);
                }
            } else {
                perror("stat");
            }
        }
    }

    // Close the directory
    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <size_in_bytes>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t n = atoi(argv[1]);
    if (n == 0) {
        fprintf(stderr, "Please enter a valid size greater than 0.\n");
        return EXIT_FAILURE;
    }

    // Start listing files from the current directory
    list_files(".", n);

    return EXIT_SUCCESS;
}


