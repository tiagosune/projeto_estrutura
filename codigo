#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 10000

struct Evento {
    char descricao[MAX_LINE_LENGTH];
    struct Evento *proximo;
};

typedef struct Evento Evento;

typedef enum {
    AdicionarEvento = 1,
    RemoverEvento,
    ListarEventos,
    ResetarEventos,
    Sair,
}MenuOption;

struct Evento* inserir_inicio(struct Evento* cabeca);
struct Evento* criar_lista(void);
struct Evento* inserir_final(struct Evento* cabeca);
struct Evento* remover_lista(struct Evento* cabeca, char *desc);

int main () {
    struct Evento *cabeca;
    cabeca = criar_lista();
    cabeca = inserir_inicio(cabeca);
  

    MenuOption opcao;
    while (opcao != Sair){
        int opcaoInt;

        printf("\nO que deseja fazer?\n1 - Adicionar evento\n2 - Remover evento\n3 - Listar eventos\n4 - Resetar todos eventos\n5 - Sair\n");
        scanf("%d", &opcaoInt);
        opcao = opcaoInt;


        switch (opcao){

            case AdicionarEvento:
                inserir_final(cabeca);
                printf("\nEvento adicionado!\n");
                break;

            case RemoverEvento:

            	remover_lista(cabeca);
                printf("\nEvento removido!\n");
                break;

            case ListarEventos:
                imprimir(cabeca);
                break;

            case ResetarEventos:
                printf("\nEventos resetados!\n");
                break;

            default:
                printf("\nFinalizando...\n");
                break;
            }
    }


}

struct Evento* criar_lista(void)
{
    return NULL;
}

struct Evento* inserir_inicio(struct Evento* cabeca) {
    struct Evento* evento = (struct Evento*) malloc(sizeof(struct Evento));

    lerEvento(evento);

    evento->proximo = cabeca;

    return (evento);
}

struct Evento* inserir_final(struct Evento* cabeca) {
    struct Evento* evento = malloc(sizeof(struct Evento));

    lerEvento(evento);

    struct Evento *ultimoEvento = cabeca;

    while (ultimoEvento->proximo != NULL)
    {
        ultimoEvento = ultimoEvento->proximo;
    }

    ultimoEvento->proximo = evento;

    return evento;
}

void lerEvento(struct Evento *evento)
{
    FILE *arquivo;
    char linha[MAX_LINE_LENGTH];

    arquivo = fopen("/var/log/syslog", "r");

    if(arquivo == NULL){
        return 1;
    }

    while (fgets(linha, MAX_LINE_LENGTH, arquivo)){
        bool hasActivation = strstr(linha, "Activation") != NULL;
        bool hasDesactivation = strstr(linha, "Desactivation") != NULL;

        if(hasActivation || hasDesactivation){
            strcpy(evento->descricao, linha);
            break;
        }
    }
    fclose(arquivo);
}

void imprimir(struct Evento *cabeca) {
    struct Evento *proximoEvento;
    proximoEvento = cabeca;

    while (proximoEvento->proximo != NULL)
    {
        printf("Descricao: %s\n", proximoEvento->descricao);
        proximoEvento = proximoEvento->proximo;
    }
}

struct Evento* remover_lista(struct Evento* cabeca, char *desc) {
 struct Evento *evento = cabeca;
 struct Evento *anterior_evento = NULL;

 while (evento != NULL && strcmpi(evento->descricao, desc) != 0) {
 anterior_evento = evento;
 evento = evento->proximo;
 }
 // A função cairá no if abaixo caso o nodo a ser excluído não exista na lista.
 if (evento == NULL)
 return NULL;
 // A função cairá no if abaixo caso o nodo a ser excluído seja o primeiro da lista.
 if (anterior_evento == NULL)
 cabeca = evento->proximo;
 /* O else será realizado caso o nodo a ser excluído seja qualquer um diferente
do primeiro da lista.
 */
 else
 anterior_evento->proximo = evento->proximo;
 free(evento);
 return cabeca;
}
