

int main(int args, char *argv[]) {
    if (args != 2) {
        // Incorrect number of command-line arguments
        printf("Usage: %s <int>\n", argv[0]);
        printf("Description: This program takes an int as an argument and creates x zombie processes based on the number provided.\n");
        return 1;
    }

    int value = atoi(argv[1]);

    if (value == 0 && argv[1][0] != '0') {
        printf("Invalid input: not an integer.\n");
        return 1;
    }

    int forks;

    if (value == -1) {
        while (1)
        {
            forks = fork();
        }
    }
    else {
        value = value / 2;
        for (int i = 0; i <= value; i++) {
            forks = fork();
        }
    }

}

/*
Jeder Kindprozess bleibt so lange ein Zombieprozess, bis von 

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