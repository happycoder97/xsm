#ifndef TIMETRAVEL_DEBUG_H
#define TIMETRAVEL_DEBUG_H

#include "memory.h"
#include "machine.h"
#include "registers.h"
#include "word.h"

typedef struct _memdiff {
    int loc;
    xsm_word oldval;
} memdiff;

#define TIMETRAVEL_MAX_STEPS 100000
typedef struct _timetravel_entry {
    xsm_cpu cpu;
    xsm_reg regs[XSM_NUM_REG];
    memdiff *memdiffs;
    int memdiffs_len;
} timetravel_entry;

void timetravel_init();
void timetravel_record();
void timetravel_rstep();
int  timetravel_cur_step();
int  timetravel_get_prev_ip();

#endif

