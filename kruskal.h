#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 20

/*
- 'pai' e 'classificacao': São arrays que armazenam informações sobre os conjuntos disjuntos durante a execução do algoritmo do Kruskal. 
- 'pai' é utilizado para rastrear o pai de cada vértice no conjunto disjunto, enquanto classificacaoé usado para melhorar a união por classificação.
- 'tam': Variável global que armazena o número de arestas na árvore geradora mínima.
*/
int pai[MAX_VERTICES], classificacao[MAX_VERTICES];
unsigned long int tam = 0;

typedef struct ARESTA {
	int origem;
	int destino;
	int peso;
} Aresta;

// Troca de valores entre duas variáveis ​​do tipo Aresta.
void trocar(Aresta *x, Aresta *y) {
	Aresta temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

// Imprime as arestas da Árvore Geradora Mínima (AGM).
void imprimirAGM(Aresta *arvoreGeradora, int numArestas) {
	int i, custo = 0;
	printf("Arestas Selecionadas:\nOrigem  Destino  Peso\n");
	for (i = 0; i < numArestas; i++) {
		printf("%d       %d        %d\n", arvoreGeradora[i].origem, arvoreGeradora[i].destino, arvoreGeradora[i].peso);
		custo += arvoreGeradora[i].peso;
	}
	printf("\nCusto = %d\n", custo);
}

// É utilizada para imprimir a matriz resultante após a execução do algoritmo de Kruskal.
void imprimirMatriz(short matriz[MAX_VERTICES][MAX_VERTICES], int numVertices) {
	int i, j;
	printf("\nMatriz Resultante:\n");
	for (i = 0; i < numVertices; i++) {
		for (j = 0; j < numVertices; j++) {
			printf("%4hd ", matriz[i][j]);
		}
		printf("\n");
	}
}

// Imprima o gráfico gerado a partir da matriz de adjacência.
void imprimirGrafo(short matriz[MAX_VERTICES][MAX_VERTICES], int numVertices) {
	int i, j;
	printf("\nGrafo Gerado:\n");
	for (i = 0; i < numVertices; i++) {
		for (j = i + 1; j < numVertices; j++) {
			if (matriz[i][j] != 0) {
				printf("%d -- %d  Peso: %d\n", i + 1, j + 1, matriz[i][j]);
			}
		}
	}
}

// Lógica do algoritmo.
void imprimirAlgoritmoKruskal() {
	printf("\n\nAlgoritmo de Kruskal:\n");
	printf("1. Ordene todas as arestas em ordem crescente de seus pesos.\n");
	printf("2. Para cada aresta, verifique se ela forma um ciclo com as arestas incluidas no grafo minimo atual.\n");
	printf("   - Se nao, inclua a aresta no grafo minimo.\n");
	printf("   - Se sim, descarte a aresta.\n");
	printf("3. Repita o passo 2 ate que o grafo minimo contenha (V-1) arestas, onde V e o numero de vertices.\n");
}

/*
- O algoritmo de ordenação rápida (quicksort) para ordenar arestas em ordem não decrescente de peso. 
- A função particionarseleciona um elemento como pivô e particiona o array em dois subarrays.
- A função QuickSortchama recursivamente a função particionarpara ordenar as duas metades do array.
*/
int particionar(Aresta *arestas, int inicio, int fim) {
	int i, p = inicio, pivot = arestas[fim].peso;
	for (i = inicio; i < fim; i++) {
		if (arestas[i].peso <= pivot) {
			trocar(&arestas[i], &arestas[p]);
			p++;
		}
	}
	trocar(&arestas[fim], &arestas[p]);
	return p;
}

/*
- O quicksort é utilizado para ordenar arestas em ordem não decrescente de peso. 
- A função particionarseleciona um elemento como pivô e particiona o array em dois subarrays.
- A função QuickSortchama recursivamente a função particionarpara ordenar as duas metades do array.
*/
void QuickSort(Aresta *arestas, int inicio, int fim) {
	int q;
	if (inicio >= fim)
		return;
	q = particionar(arestas, inicio, fim);
	QuickSort(arestas, inicio, q - 1);
	QuickSort(arestas, q + 1, fim);
}

/*
- Realiza a operação de encontrar o conjunto ao qual um vértice pertence no conjunto disjunto. 
- Em outras palavras: 
  Percorrer a cadeia de pais até encontrar o representante do conjunto e, ao mesmo tempo, fazer as atualizações de caminho para melhorias futuras operações de busca.
*/
int encontrar(int u) {
	int i = 0, caminho[MAX_VERTICES];
	while (u != pai[u]) {
		caminho[i] = u;
		u = pai[u];
		i++;
	}
	i--;
	while (i >= 0) {
		pai[caminho[i]] = u;
		i--;
	}
	return u;
}

// Realiza a união de dois conjuntos disjuntos considerando a classificação.
void unirPorClassificacao(int u, int v) {
	int x, y;
	x = encontrar(u);
	y = encontrar(v);
	if (classificacao[x] < classificacao[y])
		pai[x] = y;
	else if (classificacao[y] < classificacao[x])
		pai[y] = x;
	else {
		pai[x] = y;
		classificacao[y]++;
	}
}

/*
- A função começa ordenando as arestas em ordem não decrescente de peso usando o quicksort. 
- Em seguida, itera sobre as arestas, adicionando aquelas que não formam ciclos na árvore geradora mínima. Durante esse processo, a matriz de adjacência também é atualizada. 
- Finalmente, são chamadas as funções para imprimir as informações relevantes.
*/
void Kruskal(Aresta *arestas, int numVertices, int numArestas, short matriz[MAX_VERTICES][MAX_VERTICES]) {
	int i, j, x, y, origem, destino;
	Aresta *arvoreGeradora;
	arvoreGeradora = (Aresta *)malloc((numVertices - 1) * sizeof(Aresta));
	QuickSort(arestas, 0, numArestas - 1);
	j = 0;
	for (i = 0; i < numArestas; i++) {
		if (j == numVertices - 1)
			break;
		origem = arestas[i].origem;
		destino = arestas[i].destino;
		x = encontrar(origem);
		y = encontrar(destino);
		if (x != y) {
			arvoreGeradora[j] = arestas[i];
			unirPorClassificacao(x, y);
			j++;
			// Atualize a matriz resultante
			matriz[origem - 1][destino - 1] = arestas[i].peso;
			matriz[destino - 1][origem - 1] = arestas[i].peso;
		}
	}

	imprimirAGM(arvoreGeradora, numVertices - 1);
	imprimirAlgoritmoKruskal();
	imprimirMatriz(matriz, numVertices);
	imprimirGrafo(matriz, numVertices);
}

// Essa é utilizada para realizar operações de limpeza no console, como pausa e limpeza da tela :)
void Limp() {
	printf("\n\n");
	system("pause");
	system("cls");
}

void menuKruskal() {
	int i, j, k, numVertices, numArestas, peso;
	Aresta *arestas;

	// Abertura de arquivo para leitura
	FILE *arquivo = fopen("Grafo.dat", "r");
	if (arquivo == NULL) {
		printf("Erro ao abrir o arquivo.\n");
		return;
	}

	// Le o numero de vertices e arestas
	fscanf(arquivo, "%d %d", &numVertices, &numArestas);

	// Aloca espaco para as arestas
	arestas = (Aresta *)malloc(numArestas * sizeof(Aresta));

	// Inicializa estruturas para o algoritmo de Kruskal
	for (i = 1; i < numVertices + 1; i++) {
		pai[i] = i;
		classificacao[i] = 0;
	}

	// Le as arestas do arquivo
	for (k = 0; k < numArestas; k++) {
		fscanf(arquivo, "%d %d %d", &i, &j, &peso);
		arestas[k].origem = i;
		arestas[k].destino = j;
		arestas[k].peso = peso;
	}

	// Fecha o arquivo apos a leitura
	fclose(arquivo);

	// Declare uma matriz para armazenar os pesos das arestas
	short matriz[MAX_VERTICES][MAX_VERTICES];

	// Popule a matriz com 0's
	printf("\nPopulando a matriz...\n");
	for (i = 0; i < numVertices; i++) {
		for (j = 0; j < numVertices; j++) {
			matriz[i][j] = 0;
		}
	}
	printf("\nMatriz populada!");
	
	// Executa o algoritmo de Kruskal
	Kruskal(arestas, numVertices, numArestas, matriz);

	// Libera a memoria alocada para as arestas
	free(arestas);
}

