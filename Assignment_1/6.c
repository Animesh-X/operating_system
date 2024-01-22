#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <setjmp.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
jmp_buf env;

void handle(){
    longjmp(env, 1);
    exit(1);
}

void chandler(){
    fprintf(stderr, "Process killed");
    exit(1);
}

int main(int argc,char*argv[]){

    int n=0; //false
    if(argc>=2){
        if(argv[1][0]=='-')
            n=1;
    }

    if ((argc>=2 && !n)|| (argc>=3 && n)){
        int index=(n) ?2 :1;
        int f1=open(argv[index], O_RDONLY);
        if(f1==-1){
            perror("error");
            exit(1);
        }
        close(0);
        if (dup(f1)== -1){
            perror("error");
            exit(1);
        }
    }

    if ((argc>=3 && !n) || (argc>=4 && n)){
        int index=(n) ?3 :2;
        int f2=open(argv[index], O_RDONLY);
        if (f2==-1){
            perror("error");
            exit(1);
        }
        close(1);
        if(dup(f2)==-1){
            perror("error");
            exit(1);
        }
    }
    int pip[2];
    if (pipe(pip) == -1){
        perror("error");
        exit(1);
    }
    pid_t p1 = fork();
    if (p1 > 0)    {
        pid_t p2 = fork();
        if (p2 > 0){
            close(pip[1]);
            int pid=-1;
            int status=-1;
            if (setjmp(env) !=0)
            {
                kill(p1,SIGTERM);
                kill(p2,SIGTERM);
                fprintf(stderr, "read timeout in second child, killing both children");
                while ((pid = wait(&status))>0){
                    fprintf(stderr, "child pid=%d reaped\n", pid);
                }
                exit(1);
            }
            signal(SIGALRM, handle);
            alarm(15);
            while ((pid = wait(&status))> 0){
                fprintf(stderr, "child pid=%d reaped with exit status=%d\n",pid, WEXITSTATUS(status));
                if (pid == p1 && WEXITSTATUS(status)==2){
                    fprintf(stderr,"process exited with status %d",WEXITSTATUS(status));
                    if (kill(p2, SIGTERM) ==-1)
                        fprintf(stderr, "process already dead");
                    wait(&status);
                    exit(1);
                }
            }
            alarm(0);
            fprintf(stderr, "normal children exit");
            exit(0);
        }
        else if (p2 == 0){
            fprintf(stderr, "process id= %d\n", getpid());
            close(1);
            dup(pip[1]);
            signal(SIGTERM, chandler);
            execl("/path/convert", "convertqE", (char *)NULL);
            close(pip[1]);
        }
        else
        {
            perror("fork failed");
            exit(1);
        }
    }
    else if (p1 == 0){
        fprintf(stderr, "process id = %d\n", getpid());
        close(0);
        dup(pip[0]);
        signal(SIGTERM, chandler);
        if (n)
            execl("/Users/apple/Desktop/Code/Operating_System/Assignment_1/count6", "count6",argv[1], (char *)NULL);
        else
            execl("/Users/apple/Desktop/Code/Operating_System/Assignment_1/convert6", "convert6",(char *)NULL);
        close(pip[0]);
    }
    else{
        perror("fork failed");
        exit(1);
    }
    return 0;
}