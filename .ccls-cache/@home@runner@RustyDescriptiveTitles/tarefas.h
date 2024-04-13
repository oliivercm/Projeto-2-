#define TOTAL_TAREFAS 100
#define TAM_DESCRICAO 300
#define TAM_CATEGORIA 100

typedef struct {
    int prioridade;
    char descricao[300];
    char categoria[100];
} Tarefa;

typedef enum {OK, MAX_TAREFA, SEM_TAREFAS, NAO_ENCONTRADO, ABRIR, FECHAR, ESCREVER, LER} ERROS;


typedef ERROS (*funcao)(Tarefa[], int*);

ERROS criarTarefa(Tarefa tarefas[], int *pos);
ERROS deletarTarefa(Tarefa tarefas[], int *pos);
ERROS listarTarefas(Tarefa tarefas[], int *pos);
ERROS exportarTarefas(Tarefa tarefas[], int *pos);
ERROS carregarTarefas(Tarefa tarefas[], int *pos);

void clearBuffer();
