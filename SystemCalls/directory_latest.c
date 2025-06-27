#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/stat.h>
#include<time.h>
#include<pwd.h>
#include<grp.h>

void display_info(char filename[],struct stat* stat_buf){
    char time_buffer[600];
    struct passwd* user_info;
    struct group* group_info;

    printf("Filename: %s\n",filename);
    printf("File size=%ld bytes\n",stat_buf->st_size);
    
    printf("Permissions: ");
    printf(S_ISDIR(stat_buf->st_mode)?"d":"_");
    printf((S_IRUSR & stat_buf->st_mode)?"r":"_");
    printf((S_IWUSR & stat_buf->st_mode)?"w":"_");
    printf((S_IXUSR & stat_buf->st_mode)?"x":"_");
    printf((S_IRGRP & stat_buf->st_mode)?"r":"_");
    printf((S_IWGRP & stat_buf->st_mode)?"w":"_");
    printf((S_IXGRP & stat_buf->st_mode)?"x":"_");
    printf((S_IROTH & stat_buf->st_mode)?"r":"_");
    printf((S_IWOTH & stat_buf->st_mode)?"w":"_");
    printf((S_IXOTH & stat_buf->st_mode)?"x":"_");
    printf("\n");

    ctime_r(&(stat_buf->st_mtime),time_buffer);
    printf("Last modification time: %s",time_buffer);

    ctime_r(&(stat_buf->st_atime),time_buffer);
    printf("Last access time: %s",time_buffer);

    ctime_r(&(stat_buf->st_ctime),time_buffer);
    printf("Last change time: %s",time_buffer);

    user_info=getpwuid(stat_buf->st_uid);
    group_info=getgrgid(stat_buf->st_gid);
    printf("User info: %s\n",user_info->pw_name);
    printf("Group info: %s\n\n",group_info->gr_name);
}

void main(){
    char dname[40];
    DIR* dir;
    struct dirent* entry;

    printf("Enter the pathname of the directory to be opened: ");
    scanf(" %[^\n]",dname);

    dir=opendir(dname);
    if(dir==NULL){
        printf("error\n");
        exit(1);
    }

    while((entry=readdir(dir))!=NULL){
        char filename[260];
        struct stat stat_buf;

        sprintf(filename,"./%s",entry->d_name);
        stat(filename,&stat_buf);

        display_info(filename,&stat_buf);
    }

    closedir(dir);
}
