#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main() {
    int ch;
    int nonAlphabeticCount=0;
    
    while ((ch=getchar())!=EOF) {
        if (!isalpha(ch) || isspace(ch)) {
            nonAlphabeticCount++;
        }
        putchar(ch);
    }

    fprintf(stderr,"Non-alphabetic count: %d\n",nonAlphabeticCount);

    exit(0);
}



















// #include <stdio.h>
// #include <fcntl.h>
// #include <unistd.h>

// #define BUFFER_SIZE 1024

// int main() {
//     int filedes;
//     int count=0;
//     char buffer[BUFFER_SIZE];
//     filedes=open("example.txt",O_RDONLY);
//     if (filedes<0) {
//         printf("File does not exist!!");
//         return 0;
//     }
//     int sz=read(filedes,buffer,BUFFER_SIZE);
//     if (sz<0){
//         printf("Error reading file");
//         return 0;
//     }
//     printf("\nContent of the file---\n%s\n\n",buffer);
//     for (int i=0;buffer[i]!='\0';i++) {
//         if (!((buffer[i]>=65 && buffer[i]<=90) || (buffer[i]>=97 && buffer[i]<=122))) {
//             count++;
//         }
//     }
//     printf("Number of Non-Alphabetic Character--%d\n",count);
//     return 0;
// }
