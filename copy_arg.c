#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

int main(int arg, char *args[]){
	int bytes = 100;
	char *buf[100];

	int fd = open(args[1],O_RDONLY, S_IREAD);
	int val_r = 0;

	int fd2 = open(args[2],O_WRONLY, S_IWRITE);

	do {
		val_r = read(fd,buf,bytes);
		if (val_r == -1){
			write(1,"ERROR\n",bytes);
			close(fd);
			close(fd2);
			_exit(0);
		}
		
		write(fd2,buf,val_r);
	} while(val_r > 0);

	close(fd);
	close(fd2);

    return 0;
}
