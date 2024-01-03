#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

/*
typ start end
o 1 1
o 2 2
w 1 2
w 2 3
w 3 1
o 3 3
*/


typedef struct {
    char type;  // 'o' für occupied, 'w' für waiting
    int start;  // Startknoten
    int end;    // Endknoten
} Edge;

typedef struct {
    int marked;
} Node;

int num_threads, num_resources = 0;



int DFS(Node *nodes, int graph[][num_threads + num_resources], int num_nodes, int current_node) {
    switch (nodes[current_node].marked) {
        case BLACK:
            return 0;  // Knoten trägt nicht zu Deadlock bei
        case GRAY:
            return 1;  // Knoten könnte zu Deadlock beitragen.
        case WHITE:
            nodes[current_node].marked = GRAY;

            for (int i = 0; i < num_nodes; i++) {
                if (graph[current_node][i] && DFS(nodes, graph, num_nodes, i)) {
                    return 1;  // Deadlock gefunden
                }
            }

            nodes[current_node].marked = BLACK;
            return 0;  // Trägt nicht zum Deadlock bei
    }
    return 0;
}

int Cycle(Node *nodes, int graph[][num_threads + num_resources], int num_nodes) {
    for (int i = 0; i < num_nodes; i++) {
        nodes[i].marked = WHITE;
    }
    for (int i = 0; i < num_nodes; i++) {
        if (!nodes[i].marked && DFS(nodes, graph, num_nodes, i)) {
            return 1;  // Deadlock gefunden
        }
    }
    return 0;  // Kein Deadlock gefunden
}

/*
void make_graph(int graph[][num_threads + num_resources], int num_resources, int num_threads) {

    for (int i = 0; i < num_threads + num_resources; i++) {
        for (int j = 0; j < num_threads + num_resources; j++) {
            printf("%d", graph[i][j]);
        }   
        printf("\n");
    }

    char filename[] = "graph.dot";
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Datei konnte nicht geöffnet werden.\n");
        return;
    }
    fputs("digraph {\n", file);

    for (int i = 0; i < num_resources; i++) {
        fprintf(file, "r%d [shape=box, style=filled, fillcolor=\"orange\"];\n", i + 1);
    }

    for (int i = 0; i < num_threads; i++) {
        fprintf(file, "t%d [style=filled, fillcolor=\"green\"];\n", i + 1);
    }


    for (int i = 0; i < num_threads + num_resources; i++) {
        for (int j = 0; j < num_threads + num_resources; j++) {
            //printf("%d\n", graph[i][j]);
            if (graph[i][j] == 1) {
                printf("%d, %d", i, j);
                if (i <= num_threads) {
                    fprintf(file, "t%d -> r%d;\n", i + 1, j + 1 - num_threads);
                } else if (i >= num_threads) {
                    fprintf(file, "r%d -> t%d;\n", i + 1 - num_threads, j + 1);
                }
            }
        }
    }

    fputs(" }\n", file);
    fclose(file);
}
*/


void make_graph(Edge edges[], int num_lines, int num_resources, int num_threads) {
    char filename[] = "graph.dot";
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Datei konnte nicht geöffnet werden.\n");
    }
    fputs("digraph {\n", file);

    for(int i = 0; i < num_resources; i++) {
        fprintf(file, "r%d [shape=box, style=filled, fillcolor=\"orange\"];\n", i+1);
    }

    for(int i = 0; i < num_threads; i++) {
        fprintf(file, "t%d [style=filled, fillcolor=\"green\"];\n", i+1);
    }

    for(int i = 0; i < num_lines; i++) {
        if (edges[i].type == 'w') {
            fprintf(file, "t%d -> r%d;\n", edges[i].start, edges[i].end);
        }
        if (edges[i].type == 'o') {
            fprintf(file, "r%d -> t%d;\n", edges[i].start, edges[i].end);
        }
    }
    fputs(" }\n", file);
    fclose(file);
}   


int main(int argc, char *argv[]) {
    if (argc != 2) {
        
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];    
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Datei konnte nicht geöffnet werden.\n");
        return 1;
    }

    int num_threads, num_resources = 0;
    fscanf(file, "%d", &num_threads);
    fscanf(file, "%d", &num_resources);

    //Kanten initialisiern
    Edge edges[num_threads * num_resources];
    for (int i = 0; i < num_threads * num_resources; i++) {
        edges[i].type = 'x';
        edges[i].start = 0;
        edges[i].end = 0;
    }

    // Matrix initialisieren 
    int graph[num_threads + num_resources][num_threads + num_resources];    
    for (int i = 0; i < num_threads + num_resources; i++) {
        for (int j = 0; j < num_threads + num_resources; j++) {
            graph[i][j] = 0;
        }
    }

    // Graph aus der Textdatei einlesen
    int num_lines = 0;
    for (int i = 0; i < num_threads * num_resources; i++) {
        if (fscanf(file, " %c %d %d", &edges[i].type, &edges[i].start, &edges[i].end) == 3) {
            num_lines++;
        }
    }

    for (int i = 0; i < num_lines; i++) {
        if (edges[i].type == 'o') { 
            // Ressource belegt von thread 
            graph[edges[i].start + num_resources -1][edges[i].end-1] = 1;
        } else if (edges[i].type == 'w') {
            // Thread wartet auf Ressource
            graph[edges[i].end-1][edges[i].start + num_threads -1] = 1;
        }
        else {
            printf("%c", edges[i].type);
        }
    }

    for (int i = 0; i < num_threads + num_resources; i++) {
        for (int j = 0; j < num_threads + num_resources; j++) {
            printf("%d", graph[i][j]);
        }   
        printf("\n");
    }

    fclose(file);

    Node nodes[num_lines];

    if (Cycle(nodes, graph, num_lines)) {
        printf("Deadlock gefunden.\n");
    } else {
        printf("Kein Deadlock gefunden.\n");
    }

    make_graph(edges, num_lines, num_resources, num_threads);

    return 0;
}



// Zum Erstellen des Graphen:
// dot -Tpdf myfile.dot -o myfile.pdf 