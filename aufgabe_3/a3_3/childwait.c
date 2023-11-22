#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

int n = 0;

void sigchld_handler(int signo) {
    if (signo == SIGCHLD) {
        n--;
        printf("Parent %d: Child terminated (n=%d)\n", getpid(), n);
        if (n == 0) {
            printf("Parent %d: All children terminated. Exiting.\n", getpid());
            exit(EXIT_SUCCESS);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <int>\n", argv[0]);
        return 1;
    }

    int value = atoi(argv[1]);

    if (value <= 0 || argv[1][0] == '-') {
        fprintf(stderr, "Invalid input: not a positive integer.\n");
        return 1;
    }

    signal(SIGCHLD, sigchld_handler);

    for (int i = 0; i < value; i++) {
        int child_pid = 0;
        pid_t pid = fork();
        if (pid == -1) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            child_pid = getpid();
            sleep(2);
            wait(NULL);
            
            exit(EXIT_SUCCESS);
        } else {
            n++;
            printf("Child %d: started (n=%d)\n", child_pid, n);
            //printf("Child %d: terminated (n=%d)\n", child_pid, n);
            printf("Parent %d: sleep(2)\n", getpid());
            sleep(2);
        }
    }

    while (n > 0) {
        pause();
    }

    printf("Parent %d: All children terminated. Exiting.\n", getpid());
    exit(EXIT_SUCCESS);
}