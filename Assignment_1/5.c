#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc,char *argv[]){
    if(argc<3){
        fprintf(stderr,"Insufficient arguments");
        exit(1);
    }
    int fileDes=open(argv[1],O_RDONLY);
    if (fileDes<0) {
        printf("File1 does not exist!!");
        return 0;
    }
    int fileDes2=open(argv[2],O_WRONLY | O_CREAT, 0644);
    if (fileDes2<0) {
        printf("Error opening/creating File2!!");
        return 0;
    }

    // duplicate the first file to stdin
    close(0);   // close the stdin
    if(dup(fileDes)==-1){
        perror("Error duplicating file");
        exit(1);
    }

    // duplicate the second file to stdout
    close(1);   // close the stdout
    if(dup(fileDes2)==-1){
        perror("Error duplicating file");
        exit(1);
    }
    
    char buffer[BUFFER_SIZE];
    char inbuf[BUFFER_SIZE];
    int fd[2];
    int p=pipe(fd);
    if(p<0){
        printf("Error creating pipe");
        exit(1);
    }
    pid_t pid1=fork();
    if(pid1==0){
        printf("First Child\t");
        // int sz;
        // while((sz=read(fileDes,buffer,BUFFER_SIZE))>0){    //read from the file and write it into the pipe
        //     write(fd[1],buffer,sz);
        // }
        close(fd[1]);   //close the write end of pipe
        // dup2(fd[0],0);  //duplicate standard input to the read end of pipe
        close(fd[0]);
        execl("/Users/apple/Desktop/Code/Operating_System/Assignment_1/count","count",(char*)NULL);
        perror("Error executing count");
        exit(1);
    }
    pid_t pid2=fork();
    if(pid2==0){
        printf("Second Child\t");
        close(fd[1]);
        close(fd[0]);
        execl("/Users/apple/Desktop/Code/Operating_System/Assignment_1/convert","convert",(char*)NULL);
        perror("Error executing count");
        exit(1);
    }

}