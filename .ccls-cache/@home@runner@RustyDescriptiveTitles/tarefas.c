#include <stdio.h>
#include <string.h>
#include "tarefas.h"

ERROS criarTarefa(Tarefa tarefas[], int *pos){
    if(*pos >= TOTAL)
        return MAX_TAREFA;

    printf("Entre com a prioridade: ");
    scanf("%d", &tarefas[*pos].prioridade);
    clearBuffer();
    printf("Entre com a categoria: ");
    fgets(tarefas[*pos].categoria, 100, stdin);

    printf("Entre com a descricao: ");
    fgets(tarefas[*pos].descricao, 300, stdin);

    (*pos)++; 

    return OK;
}

ERROS deletarTarefa(Tarefa tarefas[], int *pos){

    if(*pos == 0)
        return SEM_TAREFAS;


    int pos_deletar;
    printf("Entre com a posicao da tarefa a ser deletada: ");
    scanf("%d", &pos_deletar);
    pos_deletar--; 
    if(pos_deletar >= *pos || pos_deletar < 0)
        return NAO_ENCONTRADO;

for(int i = pos_deletar; i < *pos - 1; i++){
        tarefas[i] = tarefas[i+1]; 
    }

    (*pos)--;

    return OK;
}

ERROS listarTarefas(Tarefa tarefas[], int *pos){
    if(*pos == 0)
        return SEM_TAREFAS;

    for(int i=0; i<*pos; i++){
        printf("Pos: %d\t", i+1);
        printf("Prioridade: %d\t", tarefas[i].prioridade);
        printf("Categoria: %s\t", tarefas[i].categoria);
        printf("Descricao: %s\n", tarefas[i].descricao);
    }

    return OK;
}

  ERROS salvarTarefas(Tarefa tarefas[], int *pos){
    FILE *f = fopen("tarefas.bin", "wb");
    if(f == NULL)
        return ABRIR;

    size_t qtd = fwrite(tarefas, sizeof(Tarefa), *pos, f);
    if(qtd != *pos)
        return ESCREVER;

    qtd = fwrite(pos, sizeof(int), 1, f);
    if(qtd != 1)
        return ESCREVER;

    if(fclose(f) != 0)
        return FECHAR;

    return OK;
}

  ERROS carregarTarefas(Tarefa tarefas[], int *pos){
    FILE *f = fopen("tarefas.bin", "rb");
    if(f == NULL)
        return ABRIR;

    size_t qtd = fread(tarefas, sizeof(Tarefa), TOTAL, f);
    if(qtd != TOTAL)
        return LER;

    qtd = fread(pos, sizeof(int), 1, f);
    if(qtd != 1)
        return LER;

    if(fclose(f) != 0)
        return FECHAR;

    return OK;
}

void clearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}