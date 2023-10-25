#include <stdlib.h>
#include <stdio.h>
#include "tarefa.h"
#include "lista_tarefas.h"
#include "cpu.h"


/*Define a prioridade da CPU para a próxima tarefa a ser executada.
Percorre a lista INGRESSADAS e escolhe a tarefa com maior prioridade.*/
void escolher_tarefa(lista_tarefas* ingressadas, cpu* cpu) {
    for(int i = 0; i < ingressadas->tam; i++) {
        tarefa* tarefa = ingressadas->tarefas[i];

        if(tarefa->priod > ingressadas->tarefas[cpu->prio]->priod) {
            def_prio(cpu, i);
        }
    }

    return;
}


/*Percorre a lista TAREFAS.
Compara o momento de ingresso da tarefa e o clock atual da CPU.
Se o momento de ingresso e clock forem correspondentes, adiciona a tarefa na lista INGRESSADAS.*/
void ingressar(lista_tarefas* tarefas, lista_tarefas* ingressadas, cpu* cpu) {
    for(int i = 0; i < tarefas->tam; i++) {
        tarefa* pronta = tarefas->tarefas[i];

        if(cpu->clock == pronta->ingresso) {
            add_tarefa(pronta, ingressadas);
        }
    }

    return;
}


/*Percorre a lista INGRESSADAS e executa a tarefa com a prioridade definida na CPU.
As demais tarefas aumentam em 1 sua prioridade dinâmica e ficam em espera.
Ao ser concluída, a tarefa sai da lista INGRESSADAS e aumenta o número de tarefas concluídas pela CPU.*/
void priod(lista_tarefas* ingressadas, cpu* cpu) {
    int removida = -1;

    for(int i = 0; i < ingressadas->tam; i++) {
        tarefa* tarefa = ingressadas->tarefas[i];

        if(i == cpu->prio && i != removida) {
            executar(tarefa);
            printf("Tarefa executada no clock %d\n", cpu->clock);
            printf("Tarefa %s -> Prioridade: %d, Tempo de espera: %d, Tempo restante: %d\n", tarefa->id, tarefa->priod, tarefa->tempo_espera, tarefa->restante);

            if(tarefa->restante == 0) {
                //printf("Tarefa concluida no clock %d\n", cpu->clock);
                //printf("Tarefa %s -> Prioridade: %d, Tempo de espera: %d, Tempo restante: %d\n", tarefa->id, tarefa->priod, tarefa->tempo_espera, tarefa->restante);
                cpu->concluido++;
                remover_tarefa(tarefa, ingressadas, cpu);
                removida = i;
                i--;
            }

        } else {
            elevar_prioridade(tarefa);
            //printf("Tarefa em espera no clock %d\n", cpu->clock);
            //printf("Tarefa %s -> Prioridade: %d, Tempo de espera: %d, Tempo restante: %d\n", tarefa->id, tarefa->priod, tarefa->tempo_espera, tarefa->restante);
        }
    }

    return;
}

/*Inicializa o algoritmo  PRIOd.*/
void start(lista_tarefas* tarefas, lista_tarefas* ingressadas, cpu* cpu) {
    /*ingressar(tarefas, ingressadas, cpu);
    escolher_tarefa(ingressadas, cpu);

    while(cpu->concluido < tarefas->tam) {
        priod(ingressadas, cpu);
        prox_clock(cpu);
        escolher_tarefa(ingressadas, cpu);
        ingressar(tarefas, ingressadas, cpu);
    }
    */

    while(cpu->concluido < tarefas->tam) {
        ingressar(tarefas, ingressadas, cpu);
        escolher_tarefa(ingressadas, cpu);
        priod(ingressadas, cpu);
        prox_clock(cpu);
    }


    return;
}

int main() {

    int n_tarefas = 5;
    cpu* cpu = criar_cpu();

    lista_tarefas* tarefas = criar_lista_tarefas(n_tarefas);
    lista_tarefas* ingressadas = criar_lista_tarefas(n_tarefas);

    tarefa* t1 = criar_tarefa("t1" ,0, 4, 1);
    tarefa* t2 = criar_tarefa("t2", 0, 1, 4);
    tarefa* t3 = criar_tarefa("t3", 1, 5, 2);
    tarefa* t4 = criar_tarefa("t4", 3, 2, 3);
    tarefa* t5 = criar_tarefa("t5", 5, 3, 5);


    add_tarefa(t1, tarefas);
    add_tarefa(t2, tarefas);
    add_tarefa(t3, tarefas);
    add_tarefa(t4, tarefas);
    add_tarefa(t5, tarefas);

    start(tarefas, ingressadas, cpu);
    
    double tempo_total_duracao = 0;
    double tempo_total_espera = 0;

    for(int i = 0; i < tarefas->tam; i++) {
        tarefa* tarefa = tarefas->tarefas[i];

        printf("Tarefa %s -> Tempo de espera: %d, Tempo duracao: %d\n", tarefa->id, tarefa->tempo_espera, tarefa->duracao);
        tempo_total_duracao += tarefa->duracao + tarefa->tempo_espera;
        tempo_total_espera += tarefa->tempo_espera;
    }

    double tempo_medio_duracao = tempo_total_duracao / tarefas->tam;
    double tempo_medio_espera = tempo_total_espera / tarefas->tam;

    printf("Tempo medio de duracao = %f\nTempo medio de espera = %f\n", tempo_medio_duracao, tempo_medio_espera);
}