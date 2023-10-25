#include <stdlib.h>
#include <stdio.h>
#include "tarefa.h"

tarefa* criar_tarefa(char* id, int ingresso, int duracao, int prioridade) {
    tarefa* nova = (tarefa*) calloc(1, sizeof(tarefa));

    if(nova != NULL) {
        nova->id = id;
        
        nova->prioridade = prioridade;
        nova->priod = prioridade;

        nova->duracao = duracao;
        nova->restante = duracao;

        nova->ingresso = ingresso;
    }

    return nova;
}

void elevar_prioridade(tarefa* tarefa) {
    tarefa->priod++;
    tarefa->tempo_espera++;
    
    return;
}

void executar(tarefa* tarefa) {
    tarefa->priod = tarefa->prioridade;
    tarefa->restante--;

    return;
}

