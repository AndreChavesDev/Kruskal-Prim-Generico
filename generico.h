#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX_SIZE 100

int numVertices;

typedef struct {
	int topo;
	int itens[MAX_SIZE];
} Pilha;

void inicializaPilha(Pilha *p) {
	p->topo = -1;
}

void empilha(int x, Pilha *p) {
	if(p->topo == numVertices-1) {
		printf("Erro: pilha cheia\n");
		return;
	}
	p->itens[++p->topo] = x;
}

int desempilha(Pilha *p) {
	if (p->topo == -1) {
		printf("\nPilha vazia. Impossível desempilhar.\n");
		return -1; // ou outro valor que indique erro
	}

	return p->itens[(p->topo)--];
}

void imprimePilha(Pilha *p) {
	if (p->topo == -1) {
		printf("Pilha vazia.\n");
	} else {
		printf("Conteudo da pilha: ");
		for (int i = 0; i <= p->topo; ++i) {
			printf("%d ", p->itens[i]);
		}
		printf("\n");
	}
}

void genericoMST(int** grafo) {
	Pilha minhaPilha;
	inicializaPilha(&minhaPilha);
	int i = 0, j = 0, indI, indJ, aux = 0;
	int menor = 10000;
	int *visitados = (int *)malloc(numVertices * sizeof(int));
	printf("\n");
	
	if(visitados == NULL) {
		printf("Erro na alocação de memória\n");
		return;
	}

	for(i = 0; i < numVertices; i++) {
		visitados[i] = 0;
	}

	i = 0;
	visitados[i] = 1;
	empilha(i, &minhaPilha);

	while(aux < numVertices-1) {
		menor = 10000;

		for(j = 0; j < numVertices; j++) {
			if(grafo[i][j] > 0 && visitados[j] == 0) {
				if(menor > grafo[i][j]) {
					menor = grafo[i][j];
					indI = i;
					indJ = j;
				}
			}
		}
		
		if(menor != 10000) {
			printf("[%d][%d] : %d\n", indI+1, indJ+1, menor);
			visitados[indJ] = 1;
			empilha(indJ, &minhaPilha);
			aux++;
			i = indJ;
		} else {
			if(minhaPilha.topo == -1) {
				break;
			}
			i = desempilha(&minhaPilha);
		}
	}

	free(visitados);
}

// Função para alocar dinamicamente uma matriz
int** CriarMatrix(int linhas, int colunas) {
	int** matriz = (int**)malloc(linhas * sizeof(int*));

	int i;
	for (i = 0; i < linhas; i++) {
		matriz[i] = (int*)malloc(colunas * sizeof(int));
	}
	return matriz;
}

// Função para liberar a memória alocada para a matriz
void liberaMatriz(int** matriz, int linhas) {
	int i;
	for (i = 0; i < linhas; i++) {
		free(matriz[i]);
	}
	free(matriz);
}

// Função para imprimir a matriz
void ImprimiMatriz(int** matriz, int tamanho) {
	int i, j;
	for (i = 0; i < tamanho; i++) {
		for (j = 0; j < tamanho; j++) {
			printf("%d ", matriz[i][j]);
		}
		printf("\n");
	}
}

// Função para ler o arquivo e preencher a matriz
int** lerArq(char* nomeArquivo) {
	FILE *arquivo;
	int arestas;

	arquivo = fopen(nomeArquivo, "r");

	if (arquivo == NULL) {
		fprintf(stderr, "Erro ao abrir o arquivo.\n");
		exit(1);
	}

	fscanf(arquivo, "%d %d", &numVertices, &arestas);

	int** matriz = CriarMatrix(numVertices, numVertices);
	int i, j;
	for (i = 0; i < numVertices; i++) {
		for (j = 0; j < numVertices; j++) {
			matriz[i][j] = 0;
		}
	}

	int k;
	for (k = 0; k < arestas; k++) {
		int i, j, w;
		fscanf(arquivo, "%d %d %d", &i, &j, &w);
		matriz[i-1][j-1] = w;
		matriz[j-1][i-1] = w;
	}

	fclose(arquivo);

	printf("Matriz:\n");
	ImprimiMatriz(matriz, numVertices);

	return matriz;
}

int mainGenerico() {
	char nomeArquivo[100];

	strcpy(nomeArquivo, "Grafo.dat");

	int** matriz = lerArq(nomeArquivo);

	genericoMST(matriz);

	liberaMatriz(matriz, numVertices);

	return 0;
}
