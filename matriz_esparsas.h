#ifndef MATRIZ
#define MATRIZ

typedef struct matriz_esparsa MATRIZ_ESPARSA;

typedef struct CELULA {
	int linha;
	int coluna;
	float valor;
	struct CELULA *direita;
	struct CELULA *abaixo;
} CELULA;

struct matriz_esparsa {
	CELULA **linhas;
	CELULA **colunas;
	int nr_linhas;
	int nr_colunas;
}MATRIZ;

MATRIZ *criar_matriz(int nr_linhas, int nr_colunas)

void apagar_matriz(MATRIZ *matriz)

int set_matriz(MATRIZ *matriz, int linha, int coluna,
double valor)

double get_matriz(MATRIZ *matriz, int linha, int coluna)

MATRIZ  *somar_matriz( MATRIZ *m1,  MATRIZ
*m2)

MATRIZ  *multiplicar_matriz( MATRIZ *m1,
MATRIZ *m2)

MATRIZ  * transposta_matriz(MATRIZ  *matriz)

double determinante_matriz(MATRIZ  *matriz)

void print_matriz(MATRIZ  *matriz)

void resumo_matriz(MATRIZ  *matriz)

MATRIZ  *ler_matriz(const char nome[])

#endif
