#pragma once
#include <stdint.h>

struct my_sigset_t {
    uint32_t mask;
};

int my_sigemptyset(struct my_sigset_t *set);

int my_sigfillset(struct my_sigset_t *set);

int my_sigaddset(struct my_sigset_t *set, int signum);

int my_sigdelset(struct my_sigset_t *set, int signum);

int my_sigismember(const struct my_sigset_t *set, int signum);

