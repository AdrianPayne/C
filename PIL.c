#include <stdio.h>

//OPEN
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//READ
#include <unistd.h>

int main(int arg, char *args[]){
//1. Abrir el fichero de ordenes
	int cmd = open(args[1],O_RDONLY,S_IREAD);
//2.Interpretarlo e iniciar bucle
	int	val_r = 0;
	char buf[1];
	buf[0] = 0;

	char *words[3][8];

	int i = 0;
	int j = 0;
	do {
		val_r = read(cmd,buf,1);
		if (val_r == -1){
			write(1,"ERROR\n",6);
			close(cmd);
			_exit(0);
		}

		words[i][j] = buf[0];
		j++;
		if (buf[0] == ' '){
			printf(words[i]);
			i++;
			j = 0;
		}
	} while(val_r > 0);
//3.Llamar a Fork

	//3.1 Execve del comando deseado	

//4.Finalizar


	return 0;
}
