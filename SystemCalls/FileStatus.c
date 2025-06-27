#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
//#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void display_file_info(const char *filename, const struct stat *stat_info);

int main() {
    DIR *dir;
    struct dirent *entry;
   
    // Open current directory
    dir = opendir("/home/pjthomas/OSLAB/SystemCalls/new");
    if (dir == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    // Read files in the directory
    while ((entry = readdir(dir)) != NULL) {
        char filename[258];
        sprintf(filename, "./%s", entry->d_name);

        struct stat stat_info;
       
        // Use stat to get information about the file
        if (stat(filename, &stat_info) == -1) {
            perror("Error getting file information");
            continue;
        }

        // Display information about the file
        display_file_info(entry->d_name, &stat_info);
    }

    // Close the directory
    closedir(dir);

    return 0;
}

void display_file_info(const char *filename, const struct stat *stat_info) {
    printf("File: %s\n", filename);
    printf("Size: %lld bytes\n", (long long)stat_info->st_size);

    // Display permissions
    printf("Permissions: ");
    printf((S_ISDIR(stat_info->st_mode)) ? "d" : "-");
    printf((stat_info->st_mode & S_IRUSR) ? "r" : "-");
    printf((stat_info->st_mode & S_IWUSR) ? "w" : "-");
    printf((stat_info->st_mode & S_IXUSR) ? "x" : "-");
    printf((stat_info->st_mode & S_IRGRP) ? "r" : "-");
    printf((stat_info->st_mode & S_IWGRP) ? "w" : "-");
    printf((stat_info->st_mode & S_IXGRP) ? "x" : "-");
    printf((stat_info->st_mode & S_IROTH) ? "r" : "-");
    printf((stat_info->st_mode & S_IWOTH) ? "w" : "-");
    printf((stat_info->st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");

    // Display owner and group
    struct passwd *owner_info = getpwuid(stat_info->st_uid);
    struct group *group_info = getgrgid(stat_info->st_gid);
    printf("Owner: %s\n", (owner_info != NULL) ? owner_info->pw_name : "Unknown");
    printf("Group: %s\n", (group_info != NULL) ? group_info->gr_name : "Unknown");

    // Display time of last modification
    char time_buffer[26];
    printf("Last modified: %s", ctime_r(&(stat_info->st_mtime), time_buffer));

    printf("\n");
}


