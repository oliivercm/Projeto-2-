#include <stdio.h>
#include "tarefas.h"

int main() {
    funcao fs[] = {criarTarefa, deletarTarefa, listarTarefas, salvarTarefas, carregarTarefas};

    Tarefa tarefas[TOTAL_TAREFAS];
    int pos = 0; 
    ERROS erro = fs[4](tarefas, &pos);
    if(erro != OK)
        printf("Erro ao carregar tarefas. Código de erro: %d\n", erro);
    else
        printf("Tarefas carregadas com sucesso.\n");

    int opcao;
    do {
        printf("\nMenu principal\n");
        printf("1 - Criar tarefa\n");
        printf("2 - Deletar tarefa\n");
        printf("3 - Listar tarefas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        if(opcao > 3 || opcao < 0) {
            printf("Opcao invalida\n");
            continue; 
        }

        if(opcao == 0) {
            printf("Sair...\n");
            break; 
        }

        erro = fs[opcao - 1](tarefas, &pos); 
        if(erro != OK)
            printf("Erro ao executar a operacao. Código de erro: %d\n", erro);
    } while(opcao != 0);

    erro = fs[3](tarefas, &pos); // Salvar tarefas antes de sair
    if(erro != OK)
        printf("Erro ao salvar tarefas. Código de erro: %d\n", erro);

    return 0;
}