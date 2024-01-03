#include "processmodel.h"
#include "process.h"
#include "queue.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct pctx *global_p;

void sig_usr(int signum){
    pthread_mutex_lock(&mutex);
    if(signum == SIGUSR1) {
        if (global_p->running != NULL) {
            p_switch_to_blocked(global_p->running);
            q_add(global_p->qblocked, global_p->running);
            global_p->running = q_remove(global_p->qready);
            p_switch_state(global_p->running);
        }
    }
    if(signum == SIGUSR2) {
        if (global_p->qblocked->start) {
            struct process *proc = q_remove(global_p->qblocked);
            p_switch_to_blocked(proc);
            q_add(global_p->qready, proc);
        }
    }
    pthread_mutex_unlock(&mutex);

    //signal(SIGINT, SIG_DFL);
}


int main() {

    if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
        perror("Unable to register SIGUSR1 handler");
        return EXIT_FAILURE;
    }

    if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
        perror("Unable to register SIGUSR2 handler");
        return EXIT_FAILURE;
    }

    struct queue *q = (struct queue*)malloc(sizeof(struct queue));
    q->start = NULL;
    q->end = NULL;

    struct queue *b = (struct queue*)malloc(sizeof(struct queue));
    b->start = NULL;
    b->end = NULL;

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
    global_p = p; 
    p->qready = q;
    p->qblocked = b;
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
    free(b);
    free(p);

return 0;
}