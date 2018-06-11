#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

	/* Declarations */
	int Pipe_Dad[2], Pipe_Son[2];
	int Pid;
	int Fd_In, Fd_Out;

	char Character, Buffer[500], Buffer_2[500];
	int B_to_Read_from_IN, B_to_Read_from_SON, i = 0, j, Flag_Comment = -1;
	

	/*PIPES*/
	pipe(Pipe_Dad); pipe(Pipe_Son);

	/*FORKS*/
	Pid = fork();
	
	if(Pid == 0){ /*SON*/

		close(Pipe_Dad[1]);
		close(Pipe_Son[0]);

		dup2(Pipe_Dad[0],0);
		dup2(Pipe_Son[1],1);

		execlp("bc","bc",NULL);
		perror("execlp failed");
		
	}else{ /*DAD*/
		
		close(Pipe_Dad[0]);
		close(Pipe_Son[1]);

		/*OPEN FILE AND START TO READ*/
		Fd_In = open(argv[1], O_RDONLY);
		Fd_Out = open(argv[2], O_CREAT|O_RDWR,0777);

		do{

			B_to_Read_from_IN = read(Fd_In, &Character,1);
			if(B_to_Read_from_IN == 0){	/*FINISH WHEN '\0'*/

			}else if(Character != '\n'){ /*FULL BUFFER UNTIL '\n' or '/*'*/
				
				if(Character == '/'){
					Flag_Comment = Flag_Comment * (-1);
				}
				
				if(Flag_Comment != 1 && Character != '/'){
					Buffer[i] = Character;
					i++;
				}

			}else{

				Buffer[i] = '\n';
				i++;

				for(j = 0; j <= i; j++){

					switch(Buffer[j]){ /*TRANSLATE BUFFER*/

						case 'a':
							Buffer[j] = ' ';
							Buffer[j+1] = '+';
							Buffer[j+2] = ' ';
							j = j + 2;
							break;

						case 's':
							Buffer[j] = ' ';
							Buffer[j+1] = '-';
							Buffer[j+2] = ' ';
							j = j + 2;
							break;

						case 'm':
							Buffer[j] = ' ';
							Buffer[j+1] = '*';
							Buffer[j+2] = ' ';
							j = j + 2;
							break;

						case 'd':
							Buffer[j] = ' ';
							Buffer[j+1] = '/';
							Buffer[j+2] = ' ';
							j = j + 2;
							break;
					}
				}
;
				/*WRITE TO SON*/
				write(Pipe_Dad[1],&Buffer,i);

				for(j=0;j<=32;j++){
					Buffer_2[j] = ' ';
				}

				/*READ FROM SON*/
				read(Pipe_Son[0],&Buffer_2, 32);
				j = 0;

				/*MAKE UP ' = '*/
				Buffer[i-1] = ' ';
				Buffer[i] = '=';
				Buffer[i+1] = ' ';
				i = i + 2;

				do{
					i++;
					Buffer[i] = Buffer_2[j];
					j++;
				}while(Buffer_2[j] != '\n' && Buffer_2[j] != '\0');

				Buffer[i+1] = '\n';

				/*WRITE TO OUTPUT FILE*/
				write(Fd_Out,&Buffer,i+j);
				i = 0;
			}
		}while(B_to_Read_from_IN != 0);

	}
	return 0;
}
