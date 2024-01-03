#include <string.h>
#include <stdio.h>
#include <pthread.h>


pthread_mutex_t mutex;
static char* nextToken = NULL;

char* new_strtok(char str[], const char s) {
    pthread_mutex_lock(&mutex);

    if (str != NULL) {
        nextToken = str;
    } else {
        // Wenn der String NULL ist, muss der Mutex geunlocked werden.
        if (nextToken == NULL) {
            pthread_mutex_unlock(&mutex);
            return NULL;
        }
    }

    char* token = NULL;

    // Stelle des Trenzeichens finden und token zuweisen
    char* delimiterPos = strchr(nextToken, s);

    if (delimiterPos != NULL) {
        *delimiterPos = '\0';
        token = nextToken;
        nextToken = delimiterPos + 1;

    } else if (nextToken != NULL) {
        // Keine Trennzeichen mehr da, aber noch String übrig
        token = nextToken;
        nextToken = NULL;
    }

    pthread_mutex_unlock(&mutex);
    return token;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input_string>, <delimiter>\n", argv[0]);
        return 1;
    }

    const char* s = argv[2];
    char *token;

    token = new_strtok(argv[1], *s);

    while (token != NULL) {
        printf("%s\n", token);
        token = new_strtok(NULL, *s);
    }

    return 0;
}