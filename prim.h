#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int numVertices;

int chaveMinima(int chave[], bool conjuntoMST[]) {
	int min = INT_MAX, indice_min, v;
	for (v = 0; v < numVertices; v++)
		if (conjuntoMST[v] == false && chave[v] < min)
			min = chave[v], indice_min = v;
	return indice_min;
}

void imprimirMST(int pai[], int** grafo) {
	printf("\n\nAresta \\ Peso\n");
	int i;
	for (i = 1; i < numVertices; i++)
		printf("[%d][%d] \t%d \n", pai[i] + 1, i + 1, grafo[i][pai[i]]);
}

// Prim
void primMST(int** grafo) {
	int pai[numVertices];
	int chave[numVertices];
	bool conjuntoMST[numVertices];


	int i;
	for (i = 0; i < numVertices; i++)
		chave[i] = INT_MAX, conjuntoMST[i] = false;


	chave[0] = 0;
	pai[0] = -1;

	int count;
	for (count = 0; count < numVertices - 1; count++) {
		int u = chaveMinima(chave, conjuntoMST);
		conjuntoMST[u] = true;
		int v;
		for (v = 0; v < numVertices; v++)
			if (grafo[u][v] && conjuntoMST[v] == false && grafo[u][v] < chave[v])
				pai[v] = u, chave[v] = grafo[u][v];
	}

	imprimirMST(pai, grafo);
}

int** criarMatriz(int linhas, int colunas) {
	int** matriz = (int**)malloc(linhas * sizeof(int*));

	int i;
	for (i = 0; i < linhas; i++) {
		matriz[i] = (int*)malloc(colunas * sizeof(int));
	}
	return matriz;
}


void liberarMatriz(int** matriz, int linhas) {
	int i;
	for (i = 0; i < linhas; i++) {
		free(matriz[i]);
	}
	free(matriz);
}

void ImprimeMatriz(int** matriz, int tamanho) {
	int i, j;
	for (i = 0; i < tamanho; i++) {
		for (j = 0; j < tamanho; j++) {
			printf("%d ", matriz[i][j]);
		}
		printf("\n");
	}
}

int** ler(char* nomeArquivo) {
	FILE *arquivo;
	int arestas;

	arquivo = fopen(nomeArquivo, "r");

	if (arquivo == NULL) {
		fprintf(stderr, "Erro ao abrir o arquivo.\n");
		exit(1);
	}

	fscanf(arquivo, "%d %d", &numVertices, &arestas);

	int** matriz = criarMatriz(numVertices, numVertices);
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
	ImprimeMatriz(matriz, numVertices);

	return matriz;
}

void menuPrim() {
	char nomeArquivo[100];
	int numa;
	strcpy(nomeArquivo, "Grafo.dat");
	/*printf("[1] - Para usar (.dat) padrão\n[2] - Digitar (.dat)\n> ");

	scanf("%d", &numa);
	if(numa != 1) {
		printf("\nDigite o nome do arquivo\n> ");
		scanf("%s", &nomeArquivo);
	}*/

	int** matriz = ler(nomeArquivo);

	primMST(matriz);

	return;
}

