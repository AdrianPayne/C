#include <stdio.h>

//OPEN
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//READ
#include <unistd.h>
//WAIT
#include <sys/wait.h>
//EXIT
#include <stdlib.h>
int main(int arg,char* argv[]){
	int fd = open(argv[1],O_RDWR);
	int out = open(argv[2],O_RDWR);
	int flag=1,c,i = 0,pid,status;
	char buf;

	char text[1000];
	int resetea(char line[100]){
		for(c=0;c<100;c++){
			line[c] = NULL;
		}
		return(0);
	}
	resetea(text);


	while(read(fd,&buf,1) > 0){
		if(buf == '\n'){
			pid = fork();
			if(pid == 0){
				close(1);
				dup(out);
				execlp("bc","bc",NULL);
				exit(-1);
			}
			wait(&status);
			write(out,"= NAH\n",6);
		}else if(buf == '/'){
			flag = flag * (-1);
		}else if(flag == 1){
			text[i] = buf;
			write(out,&text[i],1);
			i++;
		}
	}
	return 0;
}
