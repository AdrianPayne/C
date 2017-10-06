#include <unistd.h>
#include <stdio.h>

int main(int arg, char *args[]){
    char *argv[] = {"ls", NULL};
    char *env[] = {"PATH=/usr/local/sbin/", NULL};
    execve("ls",argv,env);
    printf("Oh, no!\n");
    return -1;
}
