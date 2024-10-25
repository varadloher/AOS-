/*.Write a C program that a string as an argument and return all the files that begins with that name in the current directory. For example > /a.out foo will return all file name that begins with foo.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <prefix>\n", argv[0]);
        return 1;
    }

    char *prefix = argv[1];

    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }

    printf("Files starting with '%s' in the current directory:\n", prefix);

    while ((entry = readdir(dir)) != NULL) {
        if (strncmp(prefix, entry->d_name, strlen(prefix)) == 0) {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);

    return 0;
}

