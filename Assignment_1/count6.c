#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int n;
    if (argc >= 2)
    {
        if (argv[1][0]=='-')
        {
            n = atoi(argv[1]+1);
            if (n <= 0)
            {
                fprintf(stderr, "Process %d: Invalid value of n provided. Exiting.", getpid());
                exit(2);
            }
        }
    }
    int c;
    int cnt=0, t=0;
    while ((c = getchar()) !=EOF)
    {
        if (!isalpha(c))
        {
            cnt++;
            putchar(c);
        }
        else
            putchar(c);
        t++;
        if(n !=0 && t==n)
            break;
    }
    fprintf(stderr,"%d",cnt);
    exit(0);
}