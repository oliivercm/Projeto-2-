#include <stdio.h>
#include "tarefas.h"

int main(){
    funcao fs[] = {criarTarefa, deletarTarefa, listarTarefas, salvarTarefas, carregarTarefas};

    Tarefa tarefas[TOTAL];
    int pos = 0; 
    ERROS erro = fs[4](tarefas, &pos);
    if(erro != OK)
      erro = fs[3](tarefas, &pos);


    int opcao;
    do{
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

      fs[opcao - 1](tarefas, &pos); 
} while(opcao != 0);

fs[3](tarefas, &pos);

    return 0;
}