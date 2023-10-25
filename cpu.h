#ifndef CPU_H
#define CPU_H

typedef struct cpu {
    int clock;
    int concluido;
    int prio;
} cpu;

cpu* criar_cpu();

void prox_clock(cpu* cpu);

void def_prio(cpu* cpu, int prio);

#endif