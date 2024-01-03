#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int sum_of_digits(const char *num) {
    if (num == NULL || *num == '\0') {
        puts("Ungültiger Parameter übergeben");
        return -1;
    }

    int sum = 0;

    while (*num != '\0') {
        if (*num >= '0' && *num <= '9') {
            sum += (*num - '0');
        } else if (*num != '\n') {
            printf("Ungültiger char: %c ist keine Zahl\n", *num);
        }
        num++;
    }

    return sum;
}

char *read_line(FILE *f, ssize_t *len) {
    char *line = NULL;
    size_t bufsize = 0;

    *len = getline(&line, &bufsize, f);

    if (*len == -1 && line != NULL) {
        free(line);
        line = NULL;
    }

    return line;
}

char **read_file(const char *filename, size_t *num_lines) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Datei konnte nicht geöffnet werden");
        return NULL;
    }
    ssize_t len;

    char *temp_line;
    while ((temp_line = read_line(file, &len)) != NULL) {
        (*num_lines)++;
        free(temp_line);
    }
    fseek(file, 0, SEEK_SET);

    char **lines = (char **)malloc((*num_lines + 1) * sizeof(char *));
    if (lines == NULL) {
        perror("Speicher konnte nicht reserviert werden");
        free(lines);
        fclose(file);
        return NULL;
    }

    for (size_t i = 0; i < *num_lines; i++) {
        lines[i] = read_line(file, &len);
        if (lines[i] == NULL) {
            perror("Zeile konnte nicht gelesen werden");
            for (size_t j = 0; j < i; j++) {
                free(lines[j]);
            }
            free(lines);
            fclose(file);
            return NULL;
        }
    }

    fclose(file);

    lines[*num_lines] = NULL;
    return lines;
}

struct ThreadArgs {
    char **numbers;
    int offset;
    int count;
    int *result;
};

void *thread_sum(void *args) {
    struct ThreadArgs *threadArgs = (struct ThreadArgs *)args;
    int sum = 0;

    for (int i = threadArgs->offset; i < threadArgs->offset + threadArgs->count; i++) {
        sum += sum_of_digits(threadArgs->numbers[i]);
    }

    pthread_mutex_lock(&mutex);
    *(threadArgs->result) += sum;
    pthread_mutex_unlock(&mutex);

    free(threadArgs);

    pthread_exit(NULL);
}

void gen_threads(char **numbers, pthread_t *threads, int n, int *total_sum) {
    int lines_count = 0;
    while (numbers[lines_count] != NULL) {
        lines_count++;
    }
    free(numbers[lines_count]);

    int numbers_per_thread = (lines_count + n - 1) / n;

    for (int i = 0; i < n; i++) {
        int offset = i * numbers_per_thread;
        int count = (i == n - 1) ? (lines_count - offset) : numbers_per_thread;

        struct ThreadArgs *args = (struct ThreadArgs *)malloc(sizeof(struct ThreadArgs));
        args->numbers = numbers;
        args->offset = offset;
        args->count = count;
        args->result = total_sum;

        if (pthread_create(&threads[i], NULL, thread_sum, (void *)args) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    size_t lines_count = 0;

    char **file_output = read_file(filename, &lines_count);
    int sum = 0;

    int a = 1;

    if (a == 0) {
        for (size_t i = 0; i < lines_count; i++) {
            sum += sum_of_digits(file_output[i]);
        }
    }

    if (a == 1) {
        int n = 5;
        pthread_t threads[n];

        gen_threads(file_output, threads, n, &sum);

        for (int i = 0; i < n; i++) {
            pthread_join(threads[i], NULL);
        }

        for (size_t i = 0; i < lines_count; i++) {
            free(file_output[i]);
        }
        free(file_output);

        printf("Summe aller Quersummen: %d\n", sum);
    }

    return 0;
}
