#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

int main(int arg, char *args[]){
	int bytes = 30;
	char buf[100];
	int val_r = 0;

	int i;
	do {
		val_r = read(0,buf,bytes);

		if (val_r == -1){
			write(1,"ERROR\n",bytes);
			_exit(0);
		}
		for (i = 0; i < 3; i++){
			printf("Salida %d: \n",i);
			write(1,buf,val_r);
		}
	} while(val_r > 0);
    return 0;
}
