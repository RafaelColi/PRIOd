#include <stdlib.h>
#include <stdio.h>
#include "cpu.h"

cpu* criar_cpu() {
    cpu* nova = (cpu*) calloc(1, sizeof(cpu));

    return nova;
}

void prox_clock(cpu* cpu) {
    cpu->clock++;

    return;
}

void def_prio(cpu* cpu, int prio) {
    cpu->prio = prio;

    return;
}