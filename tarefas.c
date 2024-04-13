#include <stdio.h>
#include <string.h>
#include "tarefas.h"

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