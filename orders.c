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
//STRCAT
#include <string.h>

int main(int arg,char* args[]){
	int pid,in,out,status,c,d;
	//Array de palabras y su funcion de inicilizado
	char words[3][8];
	int resetear(char words[3][8]){
		for(c=0;c<3;c++){
			for(d=0;d<8;d++){
				words[c][d] = NULL;
			}
		}
		return 0;
	}

	int bfr; //bytes for read
	char buf;
	int i,j =0;

	int cmd = open(args[1],O_RDONLY);

	resetear(words);


	while(bfr = read(cmd,&buf,1) > 0){
		if(buf == ' '){
			j=0;
			i++;
		}else if(buf == '\n'){
			pid = fork();
			if(pid == 0){
				in = open(words[1],O_RDONLY);
				out = open(words[2],O_WRONLY);
				printf("Voy a ejecutar:<%s> | Entrada: <%s> | Salida: <%s>\n",words[0],words[1],words[2]);
				close(0);
				close(1);
				dup(in);
				dup(out);
				
				execlp(words[0],words[0],NULL);
				exit(-1);
			}
			wait(&status);
			if(status == 0){
				printf("%s","Ejecucion correcta\n");
			}else{
				printf("%s","Ejecucion incorrecta\n");
			}
			resetear(words);
			i=0;
			j=0;
		}else{
			words[i][j] = buf;
			j++;
		}
	}
	return 0;
}
