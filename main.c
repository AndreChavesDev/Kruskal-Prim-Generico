#include<stdio.h>
#include<stdlib.h>

#include "generico.h"
#include "kruskal.h"
#include "prim.h"

int menuPrincipal(){
	
	int op=1;
	
	while(op != 0){
		
		printf("\n\n****** MENU PRINCIPAL ******\n");
		printf("\n [0] - Sair;");
		printf("\n [1] - Generico para deteccao de MSTs;");
		printf("\n [2] - Kruskal;");
		printf("\n [3] - Prim;");
		
		printf("\n\n Escolha um dos algoritmos acima:\n > ");
		scanf("%d", &op);
		switch(op){
			case 0:{
				system("cls");
				printf("\nVoce saiu!!!\n");
				return 0;
				break;
			}
			
			case 1:{
				system("cls");
				printf("\nGenerico: \n\n");
				mainGenerico();
				
				system("pause");
				system("cls");
				menuPrincipal();
				break;
			}	
			
			case 2:{
				system("cls");
				printf("\nKruskal: \n\n");
				menuKruskal();
				
				system("pause");
				system("cls");
				menuPrincipal();
				break;
			}
			
			case 3:{
				system("cls");
				printf("\nPrim: \n\n");
				menuPrim();
				
				system("pause");
				system("cls");
				menuPrincipal();
				break;
			}
			
			default:{
				printf("\nINSIRA UMA OPCAO VALIDA!!!!\n");
				
				menuPrincipal();
				break;
			}
		}
	}
	return 0;
}

void main(){
	
	menuPrincipal();
	
	printf("\n\n Nomes:\n- Andre;\n- Joao;\n\n");
}
