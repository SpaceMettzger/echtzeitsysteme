#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    struct queue *q = (struct queue*)malloc(sizeof(struct queue));
    q->start = NULL;
    q->end = NULL;

    struct process *p_1 = (struct process*)malloc(sizeof(struct process));
    struct process *p_2 = (struct process*)malloc(sizeof(struct process));
    struct process *p_3 = (struct process*)malloc(sizeof(struct process));

    p_1->p_id = 1;
    p_1->p_state = RUNNING;

    p_2->p_id = 2;
    p_2->p_state = READY;

    p_3->p_id = 3;
    p_3->p_state = READY;

    q_add(q, p_1);
    q_add(q, p_2);
    q_add(q, p_3);

    q_print(q);

    printf("\n");   
    q_remove(q);


    q_print(q);

    while (q->start != NULL) {
        struct q_node *node_to_remove = q->start;
        q->start = q->start->next;
        free(node_to_remove->p);
        free(node_to_remove);
    }

    q_remove(q);
    q_add(q, p_1);
    puts("");
    q_print(q);
    q_remove(q);

    free(q);
    free(p_1);

    return 0;
}