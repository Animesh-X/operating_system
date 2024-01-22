#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void h()
{
    fprintf(stderr, "process killed", getpid());
    exit(2);
}

int main()
{
    signal(SIGPIPE, h);
    char buff[BUFSIZ];
    int sizeread;
    while (1)
    {
        sizeread = read(0, buff, BUFSIZ);
        for (int i = 0; i < sizeread; i++)
        {
            if (islower(buff[i]))
                buff[i] = toupper(buff[i]);
            if (isupper(buff[i]))
                buff[i] = tolower(buff[i]);
        }
        if (!sizeread)
            exit(0);
        else if (sizeread > 0)
            write(1, buff, sizeread);
    }
    return 0;
}