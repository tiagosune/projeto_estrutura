#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 10000
#define MAX_DESCRIPTION_COUNT 100

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

struct Evento* criar_evento(void);
struct Evento* criar_cabeca(void);
struct Evento* inserir_inicio(struct Evento*);
struct Evento* inserir_final(struct Evento*);
struct Evento* get_ultimo_evento(struct Evento*);
int get_contagem_eventos(struct Evento*);
void ler_evento(struct Evento*);
void imprimir(struct Evento*);
struct Evento* remover_ultimo_lista(struct Evento*);
struct Evento* remover_lista(struct Evento*, char*);
char** get_lista_de_descricoes(void);

int main() {
	struct Evento *cabeca = NULL;

	MenuOption opcao = AdicionarEvento;

	char** all_descriptions = get_lista_de_descricoes();

	while (opcao != Sair)
	{
		int opcaoSelector;

		printf("\nO que deseja fazer?\n1 - Adicionar evento\n2 - Remover ultimo evento\n3 - Listar eventos\n4 - Resetar todos eventos\n5 - Sair\n");
		scanf("%d", &opcaoSelector);
		opcao = (MenuOption)opcaoSelector;

		int eventCount = get_contagem_eventos(cabeca);

		switch (opcao)
		{
			case AdicionarEvento:
				if (eventCount == 0)
				{
					cabeca = criar_cabeca();
					printf("\nLista criada e evento adicionado!\n");
				}
				else
				{
					inserir_final(cabeca);
					printf("\nEvento adicionado!\n");
				}
				break;

			case RemoverEvento:
				if (eventCount > 0)
				{
					cabeca = remover_ultimo_lista(cabeca);
					printf("\nEvento removido!\n");
				}
				else
				{
					printf("\nNao foi possivel remover o evento, pois nao tem nenhum evento na lista!\n");
				}
				break;

			case ListarEventos:
				if (eventCount > 0)
				{
					imprimir(cabeca);
				}
				else
				{
					printf("\nNada a ser listado.\n");
				}
				break;

			case ResetarEventos:
				cabeca = NULL;
				printf("\nEventos resetados!\n");
				break;

			default:
				printf("\nFinalizando...\n");
				break;
		}
	}


}

struct Evento* criar_evento(void)
{
	struct Evento* evento = (struct Evento*) malloc(sizeof(struct Evento));
	ler_evento(evento);

	return evento;
}

struct Evento* criar_cabeca(void)
{
	struct Evento* cabeca = criar_evento();
	cabeca->proximo = NULL;

	return cabeca;
}

struct Evento* inserir_inicio(struct Evento* cabeca)
{
	struct Evento* novaCabeca = criar_evento();
	novaCabeca->proximo = cabeca;

	return novaCabeca;
}

struct Evento* inserir_final(struct Evento* cabeca)
{
	struct Evento* evento = criar_evento();
	evento->proximo = NULL;

	struct Evento* ultimoEvento = get_ultimo_evento(cabeca);
	ultimoEvento->proximo = evento;

	return cabeca;
}

struct Evento* get_ultimo_evento(struct Evento* cabeca)
{
	struct Evento *ultimoEvento = cabeca;

	while (ultimoEvento->proximo != NULL)
	{
		ultimoEvento = ultimoEvento->proximo;
	}

	return ultimoEvento;
}

int get_contagem_eventos(struct Evento* cabeca)
{
	if (cabeca == NULL)
	{
		return 0;
	}

	int eventCount = 1;

	struct Evento* iterador = cabeca;

	while (iterador->proximo != NULL)
	{
		iterador = iterador->proximo;
		eventCount++;
	}

	return eventCount;
}

void ler_evento(struct Evento *evento)
{
	FILE *arquivo;
	char linha[MAX_LINE_LENGTH];

	arquivo = fopen("/var/log/syslog", "r");
	
	if (arquivo == NULL) {
		return;
	}

	while (fgets(linha, MAX_LINE_LENGTH, arquivo)) {
		bool hasActivation = strstr(linha, "Activation") != NULL;
		bool hasDesactivation = strstr(linha, "Desactivation") != NULL;
		if (hasActivation || hasDesactivation) {
			strcpy(evento->descricao, linha);
			break;
		}
	}

	fclose(arquivo);
}

void imprimir(struct Evento *cabeca)
{
	if (cabeca == NULL)
	{
		return;
	}

	struct Evento *iterador;
	iterador = cabeca;

	int eventCount = 1;

	printf("\n-----Descricoes-----\n");
	do 
	{
		printf("Evento %d: %s", eventCount, iterador->descricao);
		iterador = iterador->proximo;
		eventCount++;
	} while (iterador != NULL);
	printf("--------------------\n");
}

struct Evento* remover_ultimo_lista(struct Evento* cabeca)
{
	struct Evento *evento = cabeca;
	struct Evento *eventoAnterior = cabeca;

	if (cabeca->proximo == NULL)
	{
		return NULL;
	}

	while (evento->proximo != NULL)
	{
		eventoAnterior = evento;
		evento = evento->proximo;
	}

	eventoAnterior->proximo = NULL;

	return cabeca;
}

char** get_lista_de_descricoes(void) //Tentei fazer aparecer eventos diferentes, mas nao consegui.
{
	char** todas_descricoes = (char**) malloc(sizeof(char *) * MAX_DESCRIPTION_COUNT);

	FILE *arquivo;
	char* linha = (char*) malloc(sizeof(char) * MAX_LINE_LENGTH);

	arquivo = fopen("/var/log/syslog", "r");
	if (arquivo == NULL) {
		return todas_descricoes;
	}

	int i = 0;

	while (fgets(linha, MAX_LINE_LENGTH, arquivo)) {
		bool hasActivation = strstr(linha, "Activation") != NULL;
		bool hasDesactivation = strstr(linha, "Desactivation") != NULL;
		if (hasActivation || hasDesactivation) {
			todas_descricoes[i] = (char*)malloc(sizeof(char) * MAX_LINE_LENGTH);
			strcpy(todas_descricoes[i], linha);
			i++;
		}
	}

	fclose(arquivo);

	return todas_descricoes;
}
