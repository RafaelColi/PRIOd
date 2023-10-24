#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "tarefa.h"
#include "lista_tarefas.h"

typedef struct cpu {
    int clock;
    int concluido;
    int prio;
} cpu;

cpu* criar_cpu() {
    cpu* nova = (cpu*) calloc(1, sizeof(cpu));

    return nova;
}

tarefa* proxima_a_executar(lista_tarefas* ingressadas, cpu* cpu, lista_tarefas* tarefas, lista_tarefas* concluidas) {
    int prio_max = 0;

    for(int i = 0; i < ingressadas->tam; i++) {
        tarefa* tarefa = ingressadas->tarefas[i];

        if(tarefa->priod > ingressadas->tarefas[prio_max]->priod) {
            prio_max = i;
        }
    }
}

void ingressar(lista_tarefas* tarefas, lista_tarefas* ingressadas, cpu* cpu, lista_tarefas* concluidas) {
    for(int i = 0; i < tarefas->tam; i++) {
        tarefa* pronta = tarefas->tarefas[i];

        if(cpu->clock == pronta->ingresso) {
            add_tarefa(pronta, ingressadas);
        }
    }

    return;
}

void priod(lista_tarefas* ingressadas, cpu* cpu, lista_tarefas* tarefas, lista_tarefas* concluidas) {
    ingressar(tarefas, ingressadas, cpu, concluidas);

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

            printf("Tarefa executada no clock %d\n", cpu->clock);
            printf("Tarefa %s -> Prioridade: %d, Tempo restante: %d, Tempo de espera: %d\n", tarefa->id, tarefa->priod, tarefa->restante, tarefa->tempo_espera);

            if(tarefa->restante == 0) {
                cpu->concluido++;
                add_tarefa(tarefa, concluidas);
                remover_tarefa(tarefa, ingressadas);

                printf("Tarefa concluida no clock %d\n", cpu->clock + 1);
                printf("Tarefa %s -> Prioridade: %d, Tempo restante: %d, Tempo de espera: %d\n", tarefa->id, tarefa->priod, tarefa->restante, tarefa->tempo_espera);
            }

        } else {
            elevar_prioridade(tarefa);
            printf("Tarefa em espera no clock %d\n", cpu->clock);
            printf("Tarefa %s -> Prioridade: %d, Tempo restante: %d, Tempo de espera: %d\n", tarefa->id, tarefa->priod, tarefa->restante, tarefa->tempo_espera);
        }
    }
}

int main() {

    int n_tarefas = 5;
    cpu* cpu = criar_cpu();

    lista_tarefas* tarefas = criar_lista_tarefas(n_tarefas);
    lista_tarefas* ingressadas = criar_lista_tarefas(n_tarefas);
    lista_tarefas* concluidas = criar_lista_tarefas(n_tarefas);

    tarefa* t1 = criar_tarefa("t1", 0, 4, 1);
    tarefa* t2 = criar_tarefa("t2", 0, 1, 4);
    tarefa* t3 = criar_tarefa("t3", 1, 5, 2);
    tarefa* t4 = criar_tarefa("t4", 3, 2, 3);
    tarefa* t5 = criar_tarefa("t5", 5, 3, 5);


    add_tarefa(t1, tarefas);
    add_tarefa(t2, tarefas);
    add_tarefa(t3, tarefas);
    add_tarefa(t4, tarefas);
    add_tarefa(t5, tarefas);

    while(cpu->concluido < tarefas->tam) {
        priod(ingressadas, cpu, tarefas, concluidas);
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