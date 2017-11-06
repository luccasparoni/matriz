#ifndef MATRIZ_h
#define MATRIZ_h

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
}MATRIZ;

MATRIZ *criar_matriz(int nr_linhas, int nr_colunas);//ok

void apagar_matriz(MATRIZ** matriz);//ok

int set_matriz(MATRIZ* matriz, int linha, int coluna,double valor);//ok

double get_matriz(MATRIZ* matriz, int linha, int coluna);//ok

MATRIZ  *somar_matriz( MATRIZ* m1,  MATRIZ* m2);//ok

MATRIZ* multiplicar_matriz( MATRIZ* m1,
MATRIZ* m2);

MATRIZ* transposta_matriz(MATRIZ* matriz);

double determinante_matriz(MATRIZ* matriz);

void print_matriz(MATRIZ* matriz);//ok

void resumo_matriz(MATRIZ* matriz);//ok

MATRIZ *ler_matriz(const char nome[]);

#endif
