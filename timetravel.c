#include "timetravel.h"
#include "machine.h"
#include "registers.h"
#include "memory.h"
#include "word.h"
#include <stdlib.h>
#include <string.h>

static timetravel_entry _timetravel_entries[TIMETRAVEL_MAX_STEPS];
static int timetravel_len = 0;

static xsm_word _mem_buf1[XSM_MEMORY_SIZE];
static xsm_word _mem_buf2[XSM_MEMORY_SIZE];

static xsm_word *_membuf_prev = _mem_buf2;
static xsm_word *_membuf_cur = _mem_buf1;

static memdiff _memdiffs[XSM_MEMORY_SIZE];
int _memdiffs_len;



void timetravel_init() {
    timetravel_len = 0;
    _memdiffs_len = 0;
}


void timetravel_record() {
    timetravel_entry *entry = &_timetravel_entries[timetravel_len];
    timetravel_len ++;

    // Swap bufs
    void *temp = _membuf_prev;
    _membuf_prev = _membuf_cur;
    _membuf_cur = temp;

    /* memory_clone(_membuf_cur); */

    _memdiffs_len = 0;

    /* for(int i = 0; i<XSM_MEMORY_SIZE; i++) { */
    /*     if(strcmp(word_get_string(&_membuf_prev[i]), word_get_string(&_membuf_cur[i])) != 0) { */
    /*         memdiff *diff = &_memdiffs[_memdiffs_len]; */
    /*         _memdiffs_len++; */
    /*         diff->loc = i; */
    /*         diff->oldval = _membuf_prev[i]; */
    /*         #<{(| printf("[%d] Record %d was '%s'\n", timetravel_len-1, diff->loc, word_get_string(&diff->oldval)); |)}># */
    /*     } */
    /* } */
    entry->cpu = machine_clone_state();
    registers_clone(entry->regs);
    /* entry->memdiffs = malloc(sizeof(memdiff)*_memdiffs_len); */
    /* memcpy(entry->memdiffs, _memdiffs, sizeof(memdiff)*_memdiffs_len); */
    /* entry->memdiffs_len = _memdiffs_len; */

}

void timetravel_rstep() {
    if(timetravel_len <= 1) return;

    /* memory_clone(_membuf_cur); */

    timetravel_len --;
    timetravel_entry *entry = &_timetravel_entries[timetravel_len];
    /* for(int i = 0; i<entry->memdiffs_len; i++) { */
    /*     memdiff *diff = &entry->memdiffs[i]; */
    /*     _membuf_cur[diff->loc] = diff->oldval; */
    /*     #<{(| printf("[%d] 1 Undo %d to '%s'\n", timetravel_len, diff->loc, word_get_string(&diff->oldval)); |)}># */
    /* } */
    /*  */
    timetravel_len --;
    entry = &_timetravel_entries[timetravel_len-1];
    /* for(int i = 0; i<entry->memdiffs_len; i++) { */
    /*     memdiff *diff = &entry->memdiffs[i]; */
    /*     _membuf_cur[diff->loc] = diff->oldval; */
    /*     printf("2 Undo %d to '%s'\n", diff->loc, word_get_string(&diff->oldval)); */
    /* } */

    machine_set_state(&entry->cpu);
    registers_set(entry->regs);
    /* memory_set(_membuf_cur); */
}

int timetravel_cur_step() {
    return timetravel_len;
}

int timetravel_get_prev_ip() {
    if(timetravel_len<=1) {
        return -1;
    }
    timetravel_entry *entry = &_timetravel_entries[timetravel_len-2];
    return word_get_integer(&entry->regs[IP]);
}
