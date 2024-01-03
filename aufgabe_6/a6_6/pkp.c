#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include "semaphore.h"

#define MAX_BUFFER_SIZE 100

semaphore mutex, empty, full;
int buffer[MAX_BUFFER_SIZE];
int buffer_size;

void init_buffer() {
    for (int i = 0; i < buffer_size; ++i) {
        buffer[i] = 0;
    }
}

void insert_item(int item, int producer_id) {
    down(&empty);
    down(&mutex);

    for (int i = 0; i < buffer_size; ++i) {
        if (buffer[i] == 0) {
            buffer[i] = item;
            printf("p%d: insert Item (buffer fill level: %d)\n", producer_id, i + 1);
            break;
        }
    }

    up(&mutex);
    up(&full);
}

int remove_item(int consumer_id) {
    down(&full);
    down(&mutex);

    // Remove item from the buffer
    int item = -1;
    for (int i = buffer_size - 1; i >= 0; --i) {
        if (buffer[i] != 0) {
            item = buffer[i];
            buffer[i] = 0;
            printf("c%d: remove Item (buffer fill level: %d)\n", consumer_id, i);
            break;
        }
    }

    up(&mutex);
    up(&empty);

    return item;
}


void* producer(void* id) {
    int producer_id = *((int*)id);
    for (int i = 1; i <= 15; ++i) {
        insert_item(i, producer_id);
        usleep(100000);
    }
    pthread_exit(NULL);
}

void* consumer(void* id) {
    int consumer_id = *((int*)id);
    for (int i = 1; i <= 10; ++i) {
        remove_item(consumer_id);
        usleep(150000);
    }
    pthread_exit(NULL);
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    buffer_size = atoi(argv[1]);

    if (buffer_size <= 0 || buffer_size > MAX_BUFFER_SIZE) {
        fprintf(stderr, "Ungültiger Buffer. Bitte einen Buffer der Größe 0 < %d eingeben.\n", MAX_BUFFER_SIZE);
        exit(EXIT_FAILURE);
    }

    init_buffer();
    sem_init(&mutex, 1);
    sem_init(&empty, buffer_size);
    sem_init(&full, 0);

    pthread_t producers[2], consumers[3];
    int producer_ids[2] = {1, 2};
    int consumer_ids[3] = {1, 2, 3};

    for (int i = 0; i < 2; ++i) {
        pthread_create(&producers[i], NULL, producer, (void*)&producer_ids[i]);
    }

    for (int i = 0; i < 3; ++i) {
        pthread_create(&consumers[i], NULL, consumer, (void*)&consumer_ids[i]);
    }

    for (int i = 0; i < 2; ++i) {
        pthread_join(producers[i], NULL);
    }

    for (int i = 0; i < 3; ++i) {
        pthread_join(consumers[i], NULL);
    }

    return 0;
}
