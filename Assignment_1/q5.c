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
        perror("Error opening the file");
        exit(1);
    }

    int fileDes2=open(argv[2],O_WRONLY | O_CREAT, 0644);
    if (fileDes2<0) {
        perror("Error creating File2!!");
        exit(1);
    }
    // https://stackoverflow.com/questions/7861611/can-someone-explain-what-dup-in-c-does
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

    // create a pipe
    int fd[2];
    if(pipe(fd)<0){
        perror("Error creating the pipe");
        exit(1);
    }

    pid_t pid1=fork(); // fork the first child
    if(pid1>0){ // parent 

        // Second Forked Child
        pid_t pid2=fork();  // create the second child
        if(pid2>0){ // parent of 2nd child
            // close the read and write end of pipe in parent
            close(fd[0]);
            close(fd[1]);
            wait(NULL);
        }
        else if(pid2==0){   // second child, it will write to the pipe
            // close(1);   // close the standard output
            // dup(fd[1]); // duplicate the standard out to write end of pipe
            dup2(fd[1],1);   //alternate to dup and close
            close(fd[0]);   // close the read end of pipe
            execl("/Users/apple/Desktop/Code/Operating_System/Assignment_1/convert","convert",(char*)NULL);
            perror("Error executing count");
            exit(1);
        }
        else{
            perror("Error creating second child");
            exit(1);
        }
    }
    // First Forked Child, it will read from the pipe
    else if(pid1==0){
        close(0);
        dup(fd[0]);
        close(fd[1]);
        execl("/Users/apple/Desktop/Code/Operating_System/Assignment_1/count","count",(char*)NULL);
        perror("Error executing count");
        exit(1);
    }
    return 0;
}