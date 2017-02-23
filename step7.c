#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXCMDLEN 256
#define MAXWORDNUM 80

void split_cmd(char* cmd, int* ac, char* av[]);
void split_proc(int* ac, char* av[]);
int count_pipe(int* ac, char* av[]); 
//void print_args(int ac, char** av);
int cnt;

int main(void)
{
    char *av[MAXWORDNUM], *comm[MAXWORDNUM];
    int ac, i, c, g, status;

    while(1) {
        char cmd[MAXCMDLEN] = {0};

        printf("mysh $: ");
        if(fgets(cmd, MAXCMDLEN, stdin) == NULL) {
            fprintf(stderr, "input error\n");
        }
        

        cmd[strlen(cmd) - 1] = '\0';
        split_cmd(cmd, &ac, av);

        for (i = 0; i < ac;i++) {
            if(strcmp(av[i], "exit") == 0) {
                exit(0);
            } else if (strcmp(av[i], "cd") == 0) {
                if (av[i + 1] == '\0') {
                    av[i + 1] = getenv("HOME");
                } else if (strcmp(av[i + 1],  ".") == 0 ) {
                    getcwd(av[i + 1], MAXWORDNUM);
                }
                printf("%s\n", av[i + 1]);
                chdir(av[i + 1]);
            }
        }

        while (av[g]) {
            comm[g] = av[g];
            comm[g + 1] = NULL;
            g++;
        }

        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(-1);
        } else if (pid == 0) {
            execvp (comm[0], comm);
            exit(-1);
        }
        wait(&status);


     /*   c = count_pipe(&ac, av);
        printf("Total Process = %d\n", c + 1);
        for (i = 0; i <= c; i++) {
            printf("Proc%d\n", i + 1);
            split_proc(&ac, av);
        }
  */  }
    return 0;
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
/*
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

*/
/*void print_args(int ac, char** av) 
{
    int i;
    for(i = 0; i < ac; i++) {
    printf("Pav[%d] = %s\n", i, av[i]);
    }
}*/
