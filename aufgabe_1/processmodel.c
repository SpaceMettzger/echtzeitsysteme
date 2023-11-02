#include "processmodel.h"
#include "queue.h"
#include "process.h"
#include <stdio.h>


void print(struct pctx *ctx){
    printf("\nCurrently running process:\n");
    p_print(ctx->running);
    printf("Processes in queue:\n");
    q_print(ctx->qready);
}


void step(struct pctx *ctx){
    p_switch_state(ctx->running);
    q_add(ctx->qready, ctx->running);
    ctx->running = q_remove(ctx->qready);
    p_switch_state(ctx->running);
}