#ifndef LISTA_TAREFAS_H
#define LISTA_TAREFAS_H
#include "tarefa.h"
#include "cpu.h"

typedef struct lista_tarefas {
    tarefa** tarefas;
    int tam;
    int cap;
} lista_tarefas;

/*Aloca memória para uma lista_tarefas com capacidade para N tarefas. Retorna um ponteiro para lista_tarefas*/
lista_tarefas* criar_lista_tarefas(int n);

/*Adiciona TAREFA na LISTA_TAREFAS*/
void add_tarefa(tarefa* tarefa, lista_tarefas* lista_tarefas);

/*Remove a TAREFA da LISTA_TAREFAS. Atualiza a prioridade na CPU com a maior prioridade das tarefas restantes*/
void remover_tarefa(tarefa* tarefa, lista_tarefas* lista_tarefas, cpu* cpu);

/*Verifica se a LISTA_TAREFAS está cheia. Retorna 1 se sim e 0 se não*/
int lista_tarefas_esta_cheia(lista_tarefas* lista_tarefas);

/*Verifica se a LISTA_TAREFAS está vazia. Retorna 1 se sim e 0 se não*/
int lista_tarefas_esta_vazia(lista_tarefas* lista_tarefas);

#endif