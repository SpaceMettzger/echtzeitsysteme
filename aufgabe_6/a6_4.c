#include <stdio.h>
#include <pthread.h>

void *thread_function() {
    pthread_join(pthread_self(), NULL); // Selbst-join (potentieller deadlock)
    perror("pthread_join(pthread_self(), NULL)");
  
    printf("Thread sollte nicht hier ankommen\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;

    pthread_create(&thread, NULL, thread_function, NULL);
    pthread_join(thread, NULL); 

    printf("Main thread wird beendet\n");

    return 0;
}


/*
Was passiert wenn ein Thread die Anweisung pthread_join(pthread_self(), NULL)
ausführt? Überlegen Sie sich eine Antwort und verifizieren Sie diese mit Hilfe
eines kleinen Programms.
*/

/*
Wenn ein Thread auf sich selber joinen soll, wartet der Thread auf die Terminierung von sich selbst.
Da der Thread nie terminiert da er auf sich selbst wartet, handelt es sich um einen Deadlock.
Dabei sollte der Fehler EDEADLK auftreten. 
Das passiert aber nicht. Vermutlich erkennt der Compiler das und optimiert die Zeile weg. 
*/