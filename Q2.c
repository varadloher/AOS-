/* display all the files from current dirctory which are created in particular month*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

// Array of month names
const char *month_names[] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <month_number>\n", argv[0]);
        return 1;
    }

    int target_month = atoi(argv[1]);
   
    if (target_month < 1 || target_month > 12) {
        fprintf(stderr, "Invalid month number. Please provide a number between 1 and 12.\n");
        return 2;
    }

    struct tm current_time;
    time_t now;
    time(&now);
    localtime_r(&now, &current_time);

    DIR *dir = opendir(".");
   
    if (dir == NULL) {
        perror("opendir");
        return 3;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        struct stat fileStat;

        if (stat(entry->d_name, &fileStat) == -1) {
            perror("stat");
            continue;
        }

        struct tm file_time;
        localtime_r(&fileStat.st_mtime, &file_time);

        if (file_time.tm_mon + 1 == target_month) {
            char formatted_time[100];
            strftime(formatted_time, sizeof(formatted_time), "%b %Y", &file_time);

            printf("%s (%s)\n", entry->d_name, formatted_time);
        }
    }

    closedir(dir);

    return 0;
}

