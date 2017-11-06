#include <stdio.h>
#include "matriz_esparsas.h"
#include "matrizesparsas.c"
#include <stdlib.h>

void main(){
	MATRIZ* m1 = criar_matriz(3, 3);

	MATRIZ* m2 = criar_matriz(3, 3);
	set_matriz(m1, 1, 1, 4);
	set_matriz(m1, 1, 3, 4);
	set_matriz(m1, 2, 2, 4);
	set_matriz(m1, 3, 1, 4);
	set_matriz(m1, 2, 3, 4);
	set_matriz(m2, 2, 1, 8);
	set_matriz(m2, 2, 2, 36);
	set_matriz(m2, 3, 2, 8);
	// MATRIZ* m3 = somar_matriz(m1, m2);
	print_matriz(m2);
	printf("\n" );
	// print_matriz(m2);
	//
	printf("\n" );
	// printf("\n" );
	// print_matriz(m3);
	// resumo_matriz(m3);

	MATRIZ* m4 = transposta_matriz(m2);
	print_matriz(m4);
	double x = determinante_matriz(m4);



	apagar_matriz(&m1);
	apagar_matriz(&m2);

}
