#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define NTHRDS 5

int sharedData = 0;
pthread_mutex_t mutex;


void *add1000(void *n) {
    pthread_mutex_lock(&mutex);
    int j = sharedData;
    sleep(rand() % 6);
    sharedData = j + 1000;
    pthread_mutex_unlock(&mutex);

    puts("1000 added!");
    return n;
}

int main() {
    pthread_t thread[NTHRDS];
    int t;

    pthread_mutex_init(&mutex, NULL);
    srand(time(NULL));

    for (t = 0; t < NTHRDS; t++)
        pthread_create(&thread[t], NULL, add1000, NULL);

    for (t = 0; t < NTHRDS; t++)
        pthread_join(thread[t], NULL);

    printf("Shared data = %d\n", sharedData);
    return 0;
}

/*
Aufgabe 1 (2 Punkte) Mutex
Was passiert wenn die beiden Zeilen 13 (pthread_mutex_lock(&mutex)) und 17
(pthread_mutex_unlock(&mutex)) des folgenden Programms auskommentiert
werden?
*/

/*
Ohne die Zeilen werden die Ressourcen nicht vor gleichzeitigem Zugriff durch mehrere Threads geschützt. 
Da sharedData in der Funktion add1000 erst eingelesen wird und nach kurzer Zeit wieder zugewiesen wird, kann es zu Race conditions kommen,
in denen ein Thread die Daten einliest und ein anderer Thread die Daten überschreibt bevor der erste Thread seine Operation abschließen kann.
Dadurch kann sharedData unvorhergesehene Werte annehmen.
*/