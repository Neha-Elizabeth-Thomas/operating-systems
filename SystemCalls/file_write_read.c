#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

void main(){
    char str[20],new[20];
    char filename[10];
    int fd;

    printf("Enter the filename: ");
    scanf(" %[^\n]",filename);
    printf("Enter the data to be written to file %s\n",filename);
    scanf(" %[^\n]",str);

    fd=open(filename,O_CREAT|O_RDWR,S_IRUSR|S_IWUSR|S_IXUSR);
    if(fd==-1){
        printf("error\n");
        exit(1);
    }

    ssize_t n=write(fd,str,strlen(str));
    if(n==-1){
        printf("error\n");
        exit(1);
    }

    printf("Data successfully written\n");

    lseek(fd,0,0);

    n=read(fd,new,sizeof(new));
    if(n==-1){
        printf("error\n");
        exit(1);
    }
    new[n]='\0';

    printf("Data read from %s is %s\n",filename,new);

    close(fd);
}
