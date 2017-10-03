#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int arg, char *args[]){
	int state;

	int a = 4;
	int b = 8;
	int c = 0;

	int family = fork();

	switch(family)
	{
		case -1:
			perror("Son didn't born\n");
			break;
		case 0:
			c = a + b;
			exit(c);
			break;
		default:
			wait(&state);
			c = WEXITSTATUS(state);
			printf("La suma es: %d\n",c);
			break;
	}

return 0;
}
