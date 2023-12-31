#include <stdlib.h>
#include <stdio.h>
#include "lista_tarefas.h"

lista_tarefas* criar_lista_tarefas(int n) {
    lista_tarefas* nova = (lista_tarefas*) calloc(n, sizeof(lista_tarefas*));

    if(nova != NULL) {
        nova->tarefas = (tarefa**) calloc(n, sizeof(tarefa*));
        nova->cap = n;
    }

    return nova;
}

void add_tarefa(tarefa* tarefa, lista_tarefas* lista_tarefas) {
    if(!lista_tarefas_esta_cheia(lista_tarefas)) {
        lista_tarefas->tarefas[lista_tarefas->tam] = tarefa;
        lista_tarefas->tam++;
    }

    return;
}

void remover_tarefa(tarefa* removida, lista_tarefas* lista_tarefas, cpu* cpu) {
    if(!lista_tarefas_esta_vazia(lista_tarefas)) {
        for(int i = 0; i < lista_tarefas->tam; i++) {
            if(lista_tarefas->tarefas[i] == removida) {
                for(int j = i; j < lista_tarefas->tam; j++) {
                    lista_tarefas->tarefas[j] = lista_tarefas->tarefas[j + 1];
                }

                lista_tarefas->tam--;
            }
        }
    }
    
    def_prio(cpu, 0);

    return;
}

int lista_tarefas_esta_cheia(lista_tarefas* lista_tarefas) {
    if(lista_tarefas != NULL) {
        if(lista_tarefas->cap == lista_tarefas->tam) {
            return 1;
        }
    }

    return 0;
}

int lista_tarefas_esta_vazia(lista_tarefas* lista_tarefas) {
    if(lista_tarefas != NULL) {
        if(lista_tarefas->tam == 0) {
            return 1;
        }
    }

    return 0;
}