#include <stdio.h>

//OPEN
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//READ
#include <unistd.h>

//EXIT
#include <stdlib.h>

//WAIT
#include <sys/wait.h>

int main(int arg, char* args[]){
//1. Abrir el fichero de ordenes

	int cmd = open(args[1],O_RDONLY);

//2.Interpretarlo e iniciar bucle

	int	val_r = 0;
	char buf;


	char words[3][8];

	int i = 0;
	int j = 0;

	int n;
	int m;
		//Inicializacion words
	for(n=0;n<3;n++){
		for(m=0;m<8;m++){
			words[i][n] = ' ';
		}
	}

		//Fork and execve
	int pid = 0;

	char *argv[] = {NULL,NULL};
	char *env[] = {NULL};

		//Exit and wait
	int *status;

	do {
		val_r = read(cmd,&buf,1);
		//EXCEPTION
		if (val_r == -1){
			printf("ERROR lectura\n");
			close(cmd);
			exit(0);
		}

		if ((buf == '\n' || buf == '\0') && val_r != 0){
			i=0;
			j=0;

/*			for(n=0;n<3;n++){
				printf("%s \n",words[n]);
			}
*/

		//3.Llamar a Fork
			pid = fork();

			if(pid != 0){
				printf("Soy papa! \n");
				wait(status);
				printf("%d! \n",*status);
				if(*status != -1){
					printf("SON WORKED! \n");
				}else{
					printf("SON FAILED! \n");
				}
			}else{
				printf("SON PROCESS\n");
				printf("-----------\n");
				printf("Execute %s\n",words[0]);
			//3.1 Execve del comando deseado
				argv[0] = words[0];
				execve(words[0],argv,env);
				printf("ALGO HA FALLADO!\n");
				exit(-1);
			}
		}else if(buf == ' '){
			i++;
			j = 0;
		}else{
			words[i][j] = buf;
			j++;
		}

	} while(val_r > 0);

	
//4.Finalizar


	return 0;
}
