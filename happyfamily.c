
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void)
{
        int     fd1[2], fd2[2], nbytes;
        pid_t   childpid;
        char    string[] = "Hello, world!\n";
		int 	a, b, resultado = 0;
		int 	state;

// Creacion de tuberias e hijo
        if ((pipe(fd1)) == -1)
		{
                printf("Error with pipe 1 \n");
                perror("fork");
                _exit(-1);
		}
        if ((pipe(fd2)) == -1)
		{
                printf("Error with pipe 2 \n");
                perror("fork");
                _exit(-1);
		}
        
        if((childpid = fork()) == -1)
        {
                printf("Error with son\n");
                perror("fork");
                _exit(-1);
        }

// Padre e hijo
        if(childpid == 0)
        {
                /* PADRE */
                close(fd1[0]);
                close(fd2[1]);

                /* Send "string" through the output side of pipe */
				a = 5;
				b = 6;
                write(fd1[1], &a, sizeof(int));
                write(fd1[1], &b, sizeof(int));
				printf("PADRE | Se van a sumar los números %d y %d\n", a, b);
				wait(state);
                nbytes = read(fd2[0], &resultado, sizeof(int));
                printf("PADRE | Resultado = %d\n", resultado);

				//exit
                close(fd1[1]);
                close(fd2[0]);

        }
        else
        {
                /* HIJO */
                close(fd1[1]);
                close(fd2[0]);

                /* Read in a string from the pipe */

				printf("HIJO | Comienzo a leer\n");
                nbytes = read(fd1[0], &a, sizeof(int));
                nbytes = read(fd1[0], &b, sizeof(int));
				resultado = a + b;
                printf("HIJO | Suma: %d + %d = %d\n", a, b, resultado);
                write(fd2[1], &resultado, sizeof(int));

				//exit
                close(fd1[0]);
                close(fd2[1]);
				exit(1);
        }
        
        return(0);
}
