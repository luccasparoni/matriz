#ifndef MATRIZ_ESPARSA_h
#define MATRIZ_ESPARSA_h

typedef struct CELULA {
	int linha;
	int coluna;
	float valor;
	struct CELULA *direita;
	struct CELULA *abaixo;
} CELULA;

typedef struct matriz_esparsa {
	CELULA **linhas;
	CELULA **colunas;
	int nr_linhas;
	int nr_colunas;
}MATRIZ_ESPARSA;

MATRIZ_ESPARSA *criar_matriz(int nr_linhas, int nr_colunas);//ok

void apagar_matriz(MATRIZ_ESPARSA* matriz);//ok

int set_matriz(MATRIZ_ESPARSA* matriz, int linha, int coluna,double valor);//ok

double get_matriz(MATRIZ_ESPARSA* matriz, int linha, int coluna);//ok

MATRIZ_ESPARSA  *somar_matriz( MATRIZ_ESPARSA* m1,  MATRIZ_ESPARSA* m2);//ok

MATRIZ_ESPARSA* multiplicar_matriz( MATRIZ_ESPARSA* m1,
MATRIZ_ESPARSA* m2);

MATRIZ_ESPARSA* transposta_matriz(MATRIZ_ESPARSA* matriz);

double determinante_matriz(MATRIZ_ESPARSA* matriz);

void print_matriz(MATRIZ_ESPARSA* matriz);//ok

void resumo_matriz(MATRIZ_ESPARSA* matriz);//ok

MATRIZ_ESPARSA *ler_matriz(const char nome[]);

#endif
