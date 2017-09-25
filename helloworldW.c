#include <stdio.h>
#include <unistd.h>

int main(int arg, char *args[]){
    write(1,"Hola Mundo!\n",12);
    return 0;
}
