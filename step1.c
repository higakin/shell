#include<stdio.h>
#include<string.h>

#define MAXLEN 256

int main(void)
{
    char str[MAXLEN];

    for (;;) {
        printf("mysh $");
        if (fgets(str, sizeof(str) + 2, stdin) == NULL) 
            printf("NULL\n");

        if (strchr(str, '\n') != NULL) {
            str[strlen(str) - 1] = '\0';  
            printf("%s \n", str);
        } else {
            while(getchar() != '\n');
            printf("Over Max Length\n");
        }
    }
}
