#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

void q_add(struct queue *q, struct process *p){
    struct q_node *new_node = (struct q_node *)malloc(sizeof(struct q_node));
    if (new_node == NULL) {
        return;
    }

    new_node->p = p;
    new_node->next = NULL;

    if (q->start == NULL) {
        q->start = new_node;
    } 
    else {
        q->end->next = new_node;
    }
    q->end = new_node;
}

struct process *q_remove(struct queue *q) {
    if (q->start == NULL) {
        return NULL;
    }
    struct process *first_element = q->start->p;
    struct q_node *node_to_remove = q->start;

    q->start = q->start->next;
    free(node_to_remove);

    return first_element; 
}


void q_print(struct queue *q) {
    struct q_node *current_node = q->start;

    while (current_node != NULL) {
        p_print(current_node->p);
        current_node = current_node->next;
    }
}
