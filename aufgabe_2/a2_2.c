#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(int args, char *argv[]) {
    if (args != 2) {
        // Incorrect number of command-line arguments
        fprintf(stderr,"Usage: %s <int>\n", argv[0]);
        fprintf(stderr,"Description: This program takes an int as an argument and creates x zombie processes based on the number provided.\n");
        return 1;
    }

    int value = atoi(argv[1]);

    if (value == 0 && argv[1][0] != '0') {
        fprintf(stderr,"Invalid input: not an integer.\n");
        return 1;
    }

    int forks = 0;

    if (value == -1) {
        while ((forks = fork()) != -1)
        {
            if (forks < 0) {
                perror("Fork failed");
                exit(EXIT_FAILURE);
            } else if (forks == 0) {
                exit(EXIT_SUCCESS);
            }
        }
    }
    else {
        for (int i = 0; i < value; i++) {
            forks = fork();
            if (forks == -1) {
                perror("Fork failed");
                exit(EXIT_FAILURE);
            } else if (forks == 0) {
                exit(EXIT_SUCCESS);
            }
        }
    }
    getchar();
    exit(EXIT_SUCCESS);

}

/*
Ein Kindprozess wird ein Zombieprozess, wenn er beendet wird ohne dass wait(NULL) aufgerufen wird 

#include <sys/wait.h> 

wait(NULL); 

aufgerufen wird. Das ist ähnlich wie ein free(). 
*/

/*
Grundsätzlicher Ablauf:

mit fork() werden kinderprozesse erzeugt. 
Wenn der Elternprozess vor dem Kindprozess beendet wird, ist de Kindprozess verwaist. 
Wenn der Kindprozess beendet wird, wird er zu einem Zombieprozess. Er bleibt so lange ein Zombieprozess, bis wait() aufgerufen wird.
Wenn der Elternprozess beendet wird, bevor er wait aufgrufen hat, wird der (Zombie-) Kindprozess ein verwaister Zombie-Prozess.  
*/