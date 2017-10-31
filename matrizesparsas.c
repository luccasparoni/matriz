#include "matriz_esparsas.h"
#include <stdlib.h>
#include <stdio.h>

MATRIZ *criar_matriz(int nr_linhas, int nr_colunas){

	MATRIZ* mat = (MATRIZ*) malloc(sizeof(MATRIZ));

	mat->nr_linhas = nr_linhas;
	mat->nr_colunas = nr_colunas;

	mat->linhas = (CELULA**) malloc(sizeof(CELULA*) * nr_linhas);
	mat->colunas = (CELULA **) malloc(sizeof(CELULA*) * nr_colunas);

	int i;
	for(i=0; i<nr_linhas; i++){
		mat->linhas[i] = (CELULA*) malloc(sizeof(CELULA));
		mat->linhas[i]->direita = mat->linhas[i];
		mat->linhas[i]->coluna = -1;
		mat->linhas[i]->linha = i+1;
	}
	for(i=0; i<nr_colunas; i++){
		mat->colunas[i] = (CELULA*) malloc(sizeof(CELULA));
		mat->colunas[i]->abaixo = mat->colunas[i];
		mat->colunas[i]->coluna = i+1;
		mat->colunas[i]->linha = -1;

	}
	return mat;
}

void apagar_matriz(MATRIZ **matriz) {
	int k;
	for (k = 0; k < (*matriz)->nr_linhas; k++) {
		CELULA* aux = (*matriz)->linhas[k]->direita;

		while (aux->direita->coluna != -1) {
			CELULA* remover = aux;
			aux = aux->direita;
			free(remover);
		}

		free((*matriz)->linhas[k]);
	}
	free((*matriz)->linhas);
	free((*matriz)->colunas);
	free((*matriz));
	*matriz = NULL;
}

void print_matriz(MATRIZ *matriz){
	int i,j;
	for(i=0; i<matriz->nr_linhas; i++){
		for(j=0; j<matriz->nr_colunas;j++){
			double x = get_matriz(matriz, i+1,j+1);
			printf("%.2f\t",x);
		}
		printf("\n");
	}
}

int set_matriz(MATRIZ *matriz, int linha, int coluna, double valor){
	CELULA* cel_nova;
	CELULA* cel_at = matriz->linhas[linha-1];
	CELULA* cel_aux = matriz->linhas[linha-1];
	while(cel_at->coluna <= coluna){
		if(cel_at->direita->coluna == -1){
			break;
		}
		cel_aux = cel_at;
		cel_at = cel_at->direita;
	}
	if(cel_aux->coluna == coluna){
		cel_aux->valor = valor;
		return 1;
	}else{
		cel_nova = (CELULA*) malloc(sizeof(CELULA));
		cel_nova->linha = linha;
		cel_nova->coluna = coluna;
		cel_nova->valor = valor;
		cel_nova->direita = cel_at;
		cel_aux->direita = cel_nova;
	}

	//faz tudo denovo para colunas
	CELULA* cel_at2 = matriz->colunas[coluna-1];
	while(cel_at2->linha <= linha){
		cel_aux = cel_at2;
		cel_at2 = cel_at2->abaixo;
		if(cel_at2->abaixo->linha == -1){
			break;
		}
	}
	if(!(cel_aux->linha == linha)){
		cel_nova->abaixo = cel_at2;
		cel_aux->abaixo = cel_nova;
		return 1;
	}
	else{
		return 0;
	}
}

double get_matriz(MATRIZ* matriz, int linha, int coluna){
	if(linha <= matriz->nr_linhas && coluna <= matriz->nr_colunas){
		CELULA* aux = matriz->linhas[linha-1];
		while(aux->coluna != coluna){
			aux = aux->direita;
			if(aux->direita->coluna == -1)
				break;
		}
		if(aux->coluna == coluna){
			return aux->valor;
		}
	}
	return 0;
}

MATRIZ *somar_matriz(MATRIZ* m1, MATRIZ* m2){
	if(m1->nr_linhas != m2->nr_linhas || m1->nr_colunas != m2->nr_colunas){//condicional para poder somar matrizes
		return NULL;
	}
	MATRIZ* msoma = criar_matriz(m1->nr_linhas, m1->nr_colunas);
	int i,j;
	for(i=0; i<m1->nr_linhas; i++){
		for(j=0; j<m1->nr_colunas; j++){
			set_matriz(msoma, i+1, j+1, get_matriz(m1, i+1, j+1)+get_matriz(m2, i+1, j+1));
		}
	}
	return msoma;

}

void resumo_matriz(MATRIZ* matriz){
	int i,j;
	for(i=0; i<matriz->nr_linhas; i++){
		for(j=0; j<matriz->nr_colunas;j++){
			double x = get_matriz(matriz, i+1,j+1);
			if(x!=0){
				printf("%.2f\n",x);
			}
		}
	}
}
