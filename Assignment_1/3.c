#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main()
{
    int c = 007;
    while(c != EOF)
    {
        c = getchar();
        if(islower(c))
        {
            c = toupper(c);
        } else if(isupper(c))
        {
            c = tolower(c);
        }
        if(c != EOF)
            putchar(c);
    }
    exit(0);
}



// #include <stdio.h>
// #include <stdlib.h>

// int main(){
//     char ch[100];
//     puts("Enter string");
//     gets(ch);

//     for(int i = 0; ch[i] != '\0'; i++){
//         if(ch[i] >= 'a' && ch[i] <= 'z'){
//             ch[i] = (char)('A' + ch[i] - 'a');
//         }
//         else if(ch[i] >= 'A' && ch[i] <= 'Z'){
//             ch[i] = (char)('a' + ch[i] - 'A');
//         }
//         printf("%c", ch[i]);
//     }
    
//     exit(0);
// }
