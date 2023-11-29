#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
            return -1;
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


int child_sum(char **numbers, int offset, int count) {
    int sum = 0;

    for (int i = offset; i < offset + count; i++) {
        sum += sum_of_digits(numbers[i]);
        free(numbers[i]);
    }

    return sum;
}


void gen_workers(char **numbers, int pfd[], int n) {
    int pid;

    int lines_count = 0;
    while (numbers[lines_count] != NULL) {
        lines_count++;
    }
    free(numbers[lines_count]);

    int numbers_per_child = (lines_count + n - 1) / n; 

    for (int i = 0; i < n; i++) {
        int offset = i * numbers_per_child;
        int count = (i == n - 1) ? (lines_count - offset) : numbers_per_child;

        if ((pid = fork()) == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {
            close(pfd[0]);
            int child_result = child_sum(numbers, offset, count);
            if (write(pfd[1], &child_result, sizeof(child_result)) == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }
            close(pfd[1]); 
            exit(EXIT_SUCCESS);
        }
    }
    close(pfd[1]); 
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
        int pfd[2];
        if (pipe(pfd) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        gen_workers(file_output, pfd, 5);

        close(pfd[1]);

        int child_result;

        while (read(pfd[0], &child_result, sizeof(child_result)) > 0) {
            sum += child_result;
        }

        close(pfd[0]);
    }

    for (size_t i = 0; i < lines_count; i++) {
            free(file_output[i]);
        }
    free(file_output);

    printf("Summe aller Quersummen: %d\n", sum);

    return 0;
}
