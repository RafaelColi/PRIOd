#include <stdlib.h>
#include <stdio.h>
#include "tarefa.h"
#include "lista_tarefas.h"

typedef struct cpu {
    int clock;
    int concluido;
} cpu;

cpu* criar_cpu() {
    cpu* nova = (cpu*) calloc(1, sizeof(cpu));

    return nova;
}

void ingressar(lista_tarefas* tarefas, lista_tarefas* ingressadas, cpu* cpu) {
    for(int i = 0; i < tarefas->tam; i++) {
        tarefa* pronta = tarefas->tarefas[i];

        if(cpu->clock == pronta->ingresso) {
            add_tarefa(pronta, ingressadas);
        }
    }

    return;
}

void priod(lista_tarefas* ingressadas, cpu* cpu, lista_tarefas* tarefas) {
    ingressar(tarefas, ingressadas, cpu);
    
    int prio_max = 0;

    for(int i = 0; i < ingressadas->tam; i++) {
        tarefa* tarefa = ingressadas->tarefas[i];

        if(tarefa->priod > ingressadas->tarefas[prio_max]->priod) {
            prio_max = i;
        }
    }

    for(int i = 0; i < ingressadas->tam; i++) {
        tarefa* tarefa = ingressadas->tarefas[i];

        if(i == prio_max) {
            executar(tarefa);

            if(tarefa->restante == 0) {
                cpu->concluido++;
                remover_tarefa(tarefa, ingressadas);
            }

        } else {
            elevar_prioridade(tarefa);
        }
    }
}

int main() {

    int n_tarefas = 5;
    cpu* cpu = criar_cpu();

    lista_tarefas* tarefas = criar_lista_tarefas(n_tarefas);
    lista_tarefas* ingressadas = criar_lista_tarefas(n_tarefas);

    tarefa* t1 = criar_tarefa(0, 4, 1);
    tarefa* t2 = criar_tarefa(0, 1, 4);
    tarefa* t3 = criar_tarefa(1, 5, 2);
    tarefa* t4 = criar_tarefa(3, 2, 3);
    tarefa* t5 = criar_tarefa(5, 3, 5);


    add_tarefa(t1, tarefas);
    add_tarefa(t2, tarefas);
    add_tarefa(t3, tarefas);
    add_tarefa(t4, tarefas);
    add_tarefa(t5, tarefas);

    while(cpu->concluido < tarefas->tam) {
        priod(ingressadas, cpu, tarefas);
        cpu->clock++;
    }
    
    double tempo_total_duracao = 0;
    double tempo_total_espera = 0;

    for(int i = 0; i < tarefas->tam; i++) {
        tarefa* tarefa = tarefas->tarefas[i];

        tempo_total_duracao += tarefa->duracao + tarefa->tempo_espera;
        tempo_total_espera += tarefa->tempo_espera;
    }

    double tempo_medio_duracao = tempo_total_duracao / tarefas->tam;
    double tempo_medio_espera = tempo_total_espera / tarefas->tam;

    printf("Tempo medio de duracao = %f\nTempo medio de espera = %f\n", tempo_medio_duracao, tempo_medio_espera);
}