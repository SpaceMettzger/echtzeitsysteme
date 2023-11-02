#include "processmodel.h"
#include "process.h"
#include "queue.h"
#include <unistd.h>
#include <stdlib.h>

int main() {

    struct queue *q = (struct queue*)malloc(sizeof(struct queue));
    q->start = NULL;
    q->end = NULL;

    struct process *p_1 = (struct process*)malloc(sizeof(struct process));
    struct process *p_2 = (struct process*)malloc(sizeof(struct process));
    struct process *p_3 = (struct process*)malloc(sizeof(struct process));
    struct process *p_4 = (struct process*)malloc(sizeof(struct process));
    struct process *p_5 = (struct process*)malloc(sizeof(struct process));
    struct process *p_6 = (struct process*)malloc(sizeof(struct process));
    struct process *p_7 = (struct process*)malloc(sizeof(struct process));
    struct process *p_8 = (struct process*)malloc(sizeof(struct process));
    struct process *p_9 = (struct process*)malloc(sizeof(struct process));
    struct process *p_0 = (struct process*)malloc(sizeof(struct process));

    p_1->p_id = 1;
    p_1->p_state = RUNNING;
    p_2->p_id = 2;
    p_2->p_state = READY;
    p_3->p_id = 3;
    p_3->p_state = READY;
    p_4->p_id = 4;
    p_4->p_state = READY;
    p_5->p_id = 5;
    p_5->p_state = READY;
    p_6->p_id = 6;
    p_6->p_state = READY;
    p_7->p_id = 7;
    p_7->p_state = READY;
    p_8->p_id = 8;
    p_8->p_state = READY;
    p_9->p_id = 9;
    p_9->p_state = READY;
    p_0->p_id = 0;
    p_0->p_state = READY;

    q_add(q, p_2);
    q_add(q, p_3);
    q_add(q, p_4);
    q_add(q, p_5);
    q_add(q, p_6);
    q_add(q, p_7);
    q_add(q, p_8);
    q_add(q, p_9);
    q_add(q, p_0);

    struct pctx *p = (struct pctx*)malloc(sizeof(struct pctx));
    p->qready = q;
    p->running = p_1;

    while(1) {
        print(p);
        step(p);
        sleep(1);
    }
    
    while (q->start != NULL) {
        struct q_node *node_to_remove = q->start;
        q->start = q->start->next;
        free(node_to_remove->p);
        free(node_to_remove);
    }
    free(q);
    free(p);

return 0;
}