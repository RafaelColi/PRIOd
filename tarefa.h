#ifndef TAREFAS_H
#define TAREFAS_H

typedef struct tarefa {
    int ingresso;
    int duracao;
    int prioridade;
    int priod;
    int restante;
    int tempo_espera;
} tarefa;

tarefa* criar_tarefa(int ingresso, int duracao, int prioridade);

void elevar_prioridade(tarefa* tarefa);

void executar(tarefa* tarefa);

#endif