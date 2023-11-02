#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <sys/wait.h>


void handler1() {
    struct passwd *pws;
    pws = getpwuid(geteuid()); 
    printf("Goodbye %s\n", pws->pw_name);
}


int main() {
    int child_pid = fork();

    if (child_pid < 0) {
        // Fehlerbehandlung
        perror("Fork failed");
        return 1;
    } else if (child_pid == 0) {
        // Kindprozess
        printf("Child Process:\n");
        printf("PID: %d\n", getpid()); // Kind PID
        printf("PPID: %d\n", getppid()); // Eltern PID   
        sleep(2);  // Wartet darauf, dass der Elternprozess beendet wird
        printf("PID: %d\n", getpid()); // Kind PID
        printf("PPID: %d\n", getppid()); // Ist jetzt systemd (Nachfolger von init) 
        wait(NULL);
        exit(0);
    } else {
        // Elternprozess
        atexit(handler1);
        printf("Parent Process:\n");
        printf("PID: %d\n", getpid()); // Eltern PID
        printf("PPID: %d\n", getppid()); // Großeltern PID (bash)
        exit(0); // Beendigung des Eltern Prozess.
    }

    sleep(4);
    return 0;
}
