#ifndef LISTA_TAREFAS_H
#define LISTA_TAREFAS_H
#include "tarefa.h"
#include "cpu.h"

typedef struct lista_tarefas {
    tarefa** tarefas;
    int tam;
    int cap;
} lista_tarefas;

lista_tarefas* criar_lista_tarefas(int n);

void add_tarefa(tarefa* tarefa, lista_tarefas* lista_tarefas);

void remover_tarefa(tarefa* tarefa, lista_tarefas* lista_tarefas, cpu* cpu);

int lista_tarefas_esta_cheia(lista_tarefas* lista_tarefas);

int lista_tarefas_esta_vazia(lista_tarefas* lista_tarefas);

#endif