#include "matriz_esparsa.h"
#include <stdlib.h>
#include <stdio.h>

MATRIZ *criar_matriz(int nr_linhas, int nr_colunas){
//Função responsàvel pela criação da matriz, e alocação de memória necessária
	MATRIZ* mat = (MATRIZ*) malloc(sizeof(MATRIZ));//aloca espaco para o ponteiro da matriz

	mat->nr_linhas = nr_linhas;
	mat->nr_colunas = nr_colunas;

	mat->linhas = (CELULA**) malloc(sizeof(CELULA*) * nr_linhas);//aloca espaço para o ponteiro de linhas da matriz
	mat->colunas = (CELULA **) malloc(sizeof(CELULA*) * nr_colunas);//aloca espaço paa o ponteiro de colunas de matriz

	int i;
	for(i=0; i<nr_linhas; i++){//aloca espaço para cada linha da matriz
		mat->linhas[i] = (CELULA*) malloc(sizeof(CELULA));
		mat->linhas[i]->direita = mat->linhas[i];
		mat->linhas[i]->coluna = -1;//a coluna é setada -1 para que esete ponteiro seja o nó cabeça da respectiva coluna
		mat->linhas[i]->linha = i+1;
	}
	for(i=0; i<nr_colunas; i++){//aloca espaço para cada coluna da matriz
		mat->colunas[i] = (CELULA*) malloc(sizeof(CELULA));
		mat->colunas[i]->abaixo = mat->colunas[i];
		mat->colunas[i]->coluna = i+1;
		mat->colunas[i]->linha = -1;//igualmente à linha, a cluna é setada -1 para representar o nó cabeça;

	}
	return mat;
}

void apagar_matriz(MATRIZ *matriz) {
	int k;
	for (k = 0; k < (matriz)->nr_linhas; k++) {//itera todas as linhas da matriz
		CELULA* aux = (matriz)->linhas[k]->direita;

		while (aux->direita->coluna != -1) {//itera em cada linha pelos elementos que não são nulos para remover cada um deles
			CELULA* remover = aux;
			aux = aux->direita;
			free(remover);
		}

		free((matriz)->linhas[k]);//libera o espaço referente àquela linha
	}
	free((matriz)->linhas);
	free((matriz)->colunas);
	free((matriz));//libera o ponteiro da matriz
	matriz = NULL;
}

void print_matriz(MATRIZ *matriz){//função para imprimir a matriz
	int i,j;
	for(i=0; i<matriz->nr_linhas; i++){//itera pelo numero de linhas da matriz
		for(j=0; j<matriz->nr_colunas;j++){//itera pelo numero de colunas da matriz
			double x = get_matriz(matriz, i+1,j+1);//variavel para  guardar o valor da celula na posicao desejada, os indices sao i+1 e j+1 devido à mariz comecar na posicao 1,1 e não 0,0.
			printf("%.2f\t",x);
		}
		printf("\n");
	}
}

int set_matriz(MATRIZ *matriz, int linha, int coluna, double valor){//função rsponsável por setar valores à celulas específicas da matriz
	CELULA* cel_nova;//cria uma nova célula
	CELULA* cel_at = matriz->linhas[linha-1];//cria uma celula para guardar a celula seguinte à nova
	CELULA* cel_aux = matriz->linhas[linha-1];//cria uma célula para guardar a celula anterior à celula adicionada
	while(cel_at->coluna <= coluna){//procura a celula seguinte à que deve ser adicionada
		if(cel_at->direita->coluna == -1){
			break;//como a lista é circular, o indice -1 indica que a linha da matriz acabou e o inidice voltou à celula nó cabeça
		}
		cel_aux = cel_at;
		cel_at = cel_at->direita;//re-atribui valor aos indices criados para axilio
	}
	if(cel_aux->coluna == coluna){//se já há um valor na celula especificada, a função deve apenas trocar o valor da celula
		cel_aux->valor = valor;
		return 1;
	}else{//se não hvia valor na celula, deve-se criar uma nova célula e atribuir os parametros necessarioas à ela
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
	//colocar excessao do 0
}

double get_matriz(MATRIZ* matriz, int linha, int coluna){//função responsavel por retornar o valor de uma celula
	if(linha <= matriz->nr_linhas && coluna <= matriz->nr_colunas){//só fara alguma coisa se a linha e a coluna dadas pertencerem à matriz
		CELULA* aux = matriz->linhas[linha-1];
		while(aux->coluna != coluna){
			aux = aux->direita;
			if(aux->direita->coluna == -1)//neste caso o auxliliar percorreu toda a matriz e não encontrou nada
				break;
		}
		if(aux->coluna == coluna){
			return aux->valor;
		}
	}
	return 0;//retorna 0 se não encontrou nenhum valor
}

MATRIZ *somar_matriz(MATRIZ* m1, MATRIZ* m2){//função responsável por somar duas matrizes
	if(m1->nr_linhas != m2->nr_linhas || m1->nr_colunas != m2->nr_colunas){//condicional para poder somar matrizes
		return NULL;
	}
	MATRIZ* msoma = criar_matriz(m1->nr_linhas, m1->nr_colunas);//cria a matriz resultante
	int i,j;
	for(i=0; i<m1->nr_linhas; i++){
		for(j=0; j<m1->nr_colunas; j++){
			set_matriz(msoma, i+1, j+1, get_matriz(m1, i+1, j+1)+get_matriz(m2, i+1, j+1));//seta o valor i+1,j+1 da matriz soma como a soma dessa posição nas duas matrizes iniciais
		}
	}
	return msoma;

}

void resumo_matriz(MATRIZ* matriz){//igual a função print_matriz, porem só imprime os valores diferentes de 0
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

MATRIZ *ler_matriz(const char arquivo[]){
	FILE *file;
	file = fopen(arquivo, "r");

	int nl;   // numero de linhas da matriz do arquivo
	int nc;   // numero de colunas da matriz do arquivo

	fscanf(file, "%d %d", &nl, &nc);
	MATRIZ* mat = criar_matriz(nl, nc);

	int i; // i e j para percorrer todos os elementos da matriz
	int j;
	float valor; // valor armazenado em determinada posiçao do arquivo

	for(i=0; i<nl; i++){
		for(j=0; j<nc; j++){
			fscanf(file, "%f", &valor);
			if(valor != 0){		//se for igual à zero nao é necessário mexer na matriz esparsa
				set_matriz(mat, i+1, j+1, valor);
			}
		}
	}

	fclose(file);
	return mat;
}

MATRIZ *multiplicar_matriz(MATRIZ* m1, MATRIZ* m2){
	int i,j,k;
	MATRIZ* m3 = criar_matriz((m1)->nr_linhas, (m2)->nr_colunas);//cria a matriz resultante
	double produto=0;
	if(m1->nr_colunas != m2->nr_linhas){//condicional para poder multiplicar duas matrizes
		return NULL;
	}
 	else{
		for(i=1; i<=(m1)->nr_linhas;i++) {
			for(j=1;j<=(m2)->nr_colunas;j++){
				for(k=1; k<=(m1)->nr_colunas;k++) {
					produto = produto + (get_matriz(m1,i,k))*(get_matriz(m2, k, j));
				}
				int a = set_matriz(m3, i, j, produto);
				produto=0;
				}
			}
		}
	return m3;
}

MATRIZ* transposta_matriz(MATRIZ* matriz){
	int i,j;
	MATRIZ* m = criar_matriz(matriz->nr_colunas, matriz->nr_linhas);
	for(i=1; i<= matriz->nr_linhas;i++){
		for(j=1; j<= matriz->nr_colunas; j++){
			set_matriz(m, i, j, get_matriz(matriz, j, i));
		}
	}
	return m;
}

double determinante_matriz(MATRIZ* matriz){

}
