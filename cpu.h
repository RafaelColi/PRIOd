#ifndef CPU_H
#define CPU_H

typedef struct cpu {
    int clock;
    int concluido;
    int prio;
} cpu;

/*Aloca memória para uma cpu. Retorna um ponteiro para a cpu criada*/
cpu* criar_cpu();

/*Atualiza o ciclo de clock da CPU*/
void prox_clock(cpu* cpu);

/*Define a tarefa prioritária da CPU para PRIO */
void def_prio(cpu* cpu, int prio);

#endif