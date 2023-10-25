#ifndef TAREFAS_H
#define TAREFAS_H

typedef struct tarefa {
    char* id;
    int ingresso;
    int duracao;
    int prioridade;
    int priod;
    int restante;
    int tempo_espera;
} tarefa;

/*Aloca memória para uma tarefa e inicializa os campos ID, INGRESSO, DURAÇÃO, PRIORIDADE e priod. Retorna um ponteiro para a tarefa criada*/
tarefa* criar_tarefa(char* id, int ingresso, int duracao, int prioridade);

/*Aumenta a prioridade dinâmica da TAREFA em 1 e contabiliza o tempo de espera*/
void elevar_prioridade(tarefa* tarefa);

/*Retorna a prioridade dinâmica da TAREFA para o valor da prioridade fixa e diminui o tempo restante para conclusão da tarefa*/
void executar(tarefa* tarefa);

#endif