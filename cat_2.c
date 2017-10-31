#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

int main(int arg, char *args[]){
	int bytes = 100;
	char *buf[10];

	int fd = open(args[1],S_IREAD,O_RDONLY);
	int val_r = 0;

	int fd2 = open(args[2],O_WRONLY, S_IWRITE);
/* AQUI EMPIEZA EL SALSEO*/
	close(fd);
	dup(0);
	close(fd2);
	dup(1);
/* HASTA AQUI */
	do {
		val_r = read(fd,buf,bytes);
		if (val_r == -1){
			write(1,"ERROR\n",bytes);
			close(fd);
			close(fd2);
			_exit(0);
		}
		
		write(fd2,buf,val_r);
		printf("BRO");
	} while(val_r > 0);

	close(fd);
	close(fd2);

    return 0;
}
