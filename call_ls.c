#include <unistd.h>
#include <stdio.h>

int main(int arg, char *args[]){
    char *argv[] = {"ls",NULL};
    char *env[] = {NULL};
    execve("/bin/ls",argv,env);

    printf("Oh, no!\n");
    return -1;
}
