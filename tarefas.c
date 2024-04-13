#include <stdio.h>
#include <string.h>
#include "tarefas.h"

ERROS criarTarefa(Tarefa tarefas[], int *pos){
    if(*pos >= TOTAL_TAREFAS)
        return MAX_TAREFA;

    printf("Entre com a prioridade: ");
    scanf("%d", &tarefas[*pos].prioridade);
    clearBuffer();
    printf("Entre com a categoria: ");
    fgets(tarefas[*pos].categoria, 100, stdin);

    printf("Entre com a descricao: ");
    fgets(tarefas[*pos].descricao, 300, stdin);

    *pos = *pos + 1;

    return OK;
}

ERROS deletarTarefa(Tarefa tarefas[], int *pos){
    // teste se existem tarefas
    if(*pos == 0)
        return SEM_TAREFAS;

    // verifica se a tarefa escolhida existe
    int pos_deletar;
    printf("Entre com a posicao da tarefa a ser deletada: ");
    scanf("%d", &pos_deletar);
    pos_deletar--; // garantir posicao certa no array
    if(pos_deletar >= *pos || pos_deletar < 0)
        return NAO_ENCONTRADO;

    for(int i = pos_deletar; i < *pos; i++){
        tarefas[i].prioridade = tarefas[i+1].prioridade;
        strcpy(tarefas[i].categoria, tarefas[i+1].categoria);
        strcpy(tarefas[i].descricao,  tarefas[i+1].descricao);
    }

    *pos = *pos - 1;

    return OK;
}


ERROS listarTarefas(Tarefa tarefas[], int *pos) {
    if (*pos == 0) {
        printf("Sem tarefas.\n");
        return SEM_TAREFAS;
    }

    char categoria[TAM_CATEGORIA];
    printf("Entre com a categoria (deixe em branco para listar todas as tarefas): ");
    clearBuffer();
    fgets(categoria, TAM_CATEGORIA, stdin);
    categoria[strcspn(categoria, "\n")] = '\0'; // Remover quebra de linha

    int encontradas = 0;
    for (int i = 0; i < *pos; i++) {
        if (categoria[0] == '\0' || strcmp(tarefas[i].categoria, categoria) == 0) {
            printf("Pos: %d\t", i + 1);
            printf("Prioridade: %d\t", tarefas[i].prioridade);
            printf("Categoria: %s\t", tarefas[i].categoria);
            printf("Descricao: %s\n", tarefas[i].descricao);
            encontradas++;
        }
    }

    if (encontradas == 0)
        printf("Nenhuma tarefa encontrada para a categoria especificada.\n");

    return OK;
}

ERROS exportarTarefas(Tarefa tarefas[], int *pos) {
    char nomeArquivo[100];
    printf("Digite o nome do arquivo para exportar as tarefas: ");
    scanf("%s", nomeArquivo);

    FILE *f = fopen(nomeArquivo, "w");
    if (f == NULL)
        return ABRIR;

    for (int i = 0; i < *pos; i++) {
        fprintf(f, "%d %s %s\n", tarefas[i].prioridade, tarefas[i].categoria, tarefas[i].descricao);
    }

    fclose(f);
    printf("Tarefas exportadas para %s com sucesso.\n", nomeArquivo);
    return OK;
}

ERROS carregarTarefas(Tarefa tarefas[], int *pos) {
    char nomeArquivo[100];
    printf("Digite o nome do arquivo para carregar as tarefas: ");
    scanf("%s", nomeArquivo);

    FILE *f = fopen(nomeArquivo, "r");
    if (f == NULL)
        return ABRIR;

    *pos = 0; // Zerar contador de tarefas

    while (fscanf(f, "%d %[^\n] %[^\n]", &tarefas[*pos].prioridade, tarefas[*pos].categoria,
                  tarefas[*pos].descricao) != EOF) {
        (*pos)++;
        if (*pos >= TOTAL_TAREFAS)
            break;
    }

    fclose(f);
    printf("Tarefas carregadas de %s com sucesso.\n", nomeArquivo);
    return OK;
}

void clearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
