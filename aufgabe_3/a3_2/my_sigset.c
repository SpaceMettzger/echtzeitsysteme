#include "my_sigset.h"

int my_sigemptyset(struct my_sigset_t *set) {
    set->mask = 0;
    return 0;
}


int my_sigfillset(struct my_sigset_t *set) {
    set->mask = ~0U;
    return 0;
}


int my_sigaddset(struct my_sigset_t *set, int signum) {
    if (signum >= 0 && signum < 32) {
        set->mask |= (1U << signum);
        return 0;
    } else {
        return -1;
    }
}


int my_sigdelset(struct my_sigset_t *set, int signum) {
    if (signum >= 0 && signum < 32) {
        set->mask &= ~(1U << signum);
        return 0;
    } else {
        return -1;
    }
}


int my_sigismember(const struct my_sigset_t *set, int signum) {
    if (signum >= 0 && signum < 32) {
        return (set->mask & (1U << signum)) != 0;
    } else {
        return -1;
    }
}
