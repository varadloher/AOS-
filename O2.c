/*Write a C program which display the information of a given file similar to given by the unix /linux command on current directory (l.e File Access permission, file name, file type, User id, group id, file size, file access and modified time and so on)ls –l <filename> DO NOT simply exec ls -l <filename> or system command from the program.*/      
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void display_file_info(const char *filename) {
    struct stat fileStat;

    // Get file status
    if (stat(filename, &fileStat) != 0) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    // Determine file type
    char fileType;
    if (S_ISREG(fileStat.st_mode)) fileType = '-';
    else if (S_ISDIR(fileStat.st_mode)) fileType = 'd';
    else if (S_ISCHR(fileStat.st_mode)) fileType = 'c';
    else if (S_ISBLK(fileStat.st_mode)) fileType = 'b';
    else if (S_ISFIFO(fileStat.st_mode)) fileType = 'p';
    else if (S_ISLNK(fileStat.st_mode)) fileType = 'l';
    else if (S_ISSOCK(fileStat.st_mode)) fileType = 's';
    else fileType = '?';

    // File permissions
    char permissions[10];
    permissions[0] = fileType;
    permissions[1] = (fileStat.st_mode & S_IRUSR) ? 'r' : '-';
    permissions[2] = (fileStat.st_mode & S_IWUSR) ? 'w' : '-';
    permissions[3] = (fileStat.st_mode & S_IXUSR) ? 'x' : '-';
    permissions[4] = (fileStat.st_mode & S_IRGRP) ? 'r' : '-';
    permissions[5] = (fileStat.st_mode & S_IWGRP) ? 'w' : '-';
    permissions[6] = (fileStat.st_mode & S_IXGRP) ? 'x' : '-';
    permissions[7] = (fileStat.st_mode & S_IROTH) ? 'r' : '-';
    permissions[8] = (fileStat.st_mode & S_IWOTH) ? 'w' : '-';
    permissions[9] = (fileStat.st_mode & S_IXOTH) ? 'x' : '-';
    permissions[10] = '\0';

    // Get user and group names
    struct passwd *pw = getpwuid(fileStat.st_uid);
    struct group *gr = getgrgid(fileStat.st_gid);

    // Convert times to human-readable format
    char accessTime[100];
    char modifyTime[100];
    struct tm *tm_info;

    tm_info = localtime(&fileStat.st_atime);
    strftime(accessTime, sizeof(accessTime), "%Y-%m-%d %H:%M:%S", tm_info);

    tm_info = localtime(&fileStat.st_mtime);
    strftime(modifyTime, sizeof(modifyTime), "%Y-%m-%d %H:%M:%S", tm_info);

    // Display file information
    printf("File: %s\n", filename);
    printf("Permissions: %s\n", permissions);
    printf("User ID: %d (%s)\n", fileStat.st_uid, pw ? pw->pw_name : "Unknown");
    printf("Group ID: %d (%s)\n", fileStat.st_gid, gr ? gr->gr_name : "Unknown");
    printf("Size: %lld bytes\n", (long long)fileStat.st_size);
    printf("Last Access Time: %s\n", accessTime);
    printf("Last Modified Time: %s\n", modifyTime);
}

int main(int argc, char *argv[]) {
    // Check if the filename is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    display_file_info(argv[1]);

    return EXIT_SUCCESS;
}

