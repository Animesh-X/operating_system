#include <stdio.h>

int main(int argc, char *argv[]){
    if(argc < 2) {
        printf("Insuffiecent parameters");
        return 0;
    }
    for(int i=1;i<argc;i++){
        if(argv[i][0]!='-'){
            printf("%s \t",argv[i]);
        }
    }
    return 0;
}