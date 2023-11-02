#pragma once

#include "process.h"
#include "queue.h"

struct pctx {
    struct queue *qready;
    struct process *running;
};

void print(struct pctx *ctx);

void step(struct pctx *ctx);