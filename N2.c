/*Write a C program to find file properties such as inode number, number of hard link, File permissions, File size, File access and modification time and so on of a given file using stat() system call.*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

void printFilePermissions(mode_t mode) {
    printf("File Permissions: ");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}

int main(int argc, char *argv[]) {
    // Check if the file name is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct stat fileStat;

    // Get file information
    if (stat(argv[1], &fileStat) == -1) {
        perror("Error retrieving file information");
        return 1;
    }

    // Print file properties
    printf("File: %s\n", argv[1]);
    printf("Inode Number: %lu\n", (unsigned long)fileStat.st_ino);
    printf("Number of Hard Links: %lu\n", (unsigned long)fileStat.st_nlink);
    printFilePermissions(fileStat.st_mode);
    printf("File Size: %lld bytes\n", (long long)fileStat.st_size);
    printf("Last Access Time: %s", ctime(&fileStat.st_atime));
    printf("Last Modification Time: %s", ctime(&fileStat.st_mtime));
    printf("Last Status Change Time: %s", ctime(&fileStat.st_ctime));

    return 0;
}

