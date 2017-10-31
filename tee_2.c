#include <stdio.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main(int arg, char *args[]){
	umask(0000);
	int bytes = 100;
	char *buf[10];

	int val_r = 0;
	int i;
	int j=0;
	int a;

	for(i=1;i<arg;++i){
		printf("VOY A ABRIR %d %s\n",i,strerror(errno));
		a = open(args[i],O_WRONLY|O_CREAT, S_IRWXU);
		printf("%d",a);
	}
	do {
		val_r = read(0,buf,bytes);
		if (val_r == -1){
			write(1,"ERROR\n",bytes);
			_exit(0);
		}
		for(i=0;i<arg;++i){
			j=i+2;
			write(j,buf,val_r);
		}
	} while(val_r > 0);

	for(i=1;i<=arg;++i){
		close(i);
	}

	return 0;
}
