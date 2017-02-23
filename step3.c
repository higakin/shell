#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCMDLEN 256
#define MAXWORDNUM 80

void split_cmd(char* cmd, int* ac, char* av[]);
void split_proc(int* ac, char* av[]);
int count_pipe(int* ac, char* av[]); 
//void print_args(int ac, char** av);
int cnt;

int main(void)
{
    char *av[MAXWORDNUM];
    int ac, i, c;

    while(1) {
        char cmd[MAXCMDLEN] = {0};

        printf("mysh $: ");
        if(fgets(cmd, MAXCMDLEN, stdin) == NULL) {
            fprintf(stderr, "input error\n");
        }

        cmd[strlen(cmd) - 1] = '\0';
        split_cmd(cmd, &ac, av);
        c = count_pipe(&ac, av);
        printf("Total Process = %d\n", c + 1);
        for (i = 0; i <= c; i++) {
            printf("Proc%d\n", i + 1);
            split_proc(&ac, av);
        }
    }
}


void split_cmd(char* cmd, int* ac, char* av[])
{
    char *tk;
    *ac =  0;

    cnt = 0;   
    tk = strtok(cmd, " \t");
    

    while(tk != NULL) {
    av[(*ac)++] = tk;
    tk = strtok(NULL, " \t");
    }


}
int count_pipe(int* ac, char* av[])
{
    int i, count = 0;
    
    for (i = 0; i < *ac; i++) {
        if (strcmp(av[i], "|") == 0) {
            count++;
        }
    }
    return count;
}

void split_proc(int* ac, char* av[])
{
    int pac = 0, g;
    char *pav[MAXWORDNUM];

    for (;cnt < *ac; cnt++) {
        if (strcmp(av[cnt], "|") == 0) {
            cnt++;
            break;
        } else {
            pav[pac++] = av[cnt];
        }
    }
    printf("Pac = %d\n", pac);
    for (g = 0; g < pac; g++) {
        printf("Pav[%d] = %s\n", g, pav[g]);
    }
    pac = 0;
}
/*void print_args(int ac, char** av) 
{
    int i;
    for(i = 0; i < ac; i++) {
    printf("Pav[%d] = %s\n", i, av[i]);
    }
}*/
