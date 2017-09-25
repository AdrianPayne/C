#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int arg, char *args[]){
	int p_dad = getpid();
	int p_son;
	int *state;

	int family = fork();

	switch(family)
	{
		case -1:
			perror("Son didn't born\n");
			break;
		case 0:
			p_son = getpid();
			printf("I'm a son, and my PID is: %d\n",p_son);
			break;
		default:
			wait(state);
			printf("I'm the father, and my PID is: %d\n",p_dad);
			break;
	}

return 0;
}
