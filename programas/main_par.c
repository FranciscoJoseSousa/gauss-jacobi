#include "parametro.h"

int main(int argc, char *argv[]) {
	double tempo = omp_get_wtime ();
	int N = atoi(argv[1]);
	int T = atoi(argv[2]);
	
	printf("Inicio do programa par para N = %d e T = %d:\n", N, T);
	
	jacovipar_new(N,T);

	tempo = omp_get_wtime () - tempo;

	printf("Tempo de execução: %f ⏱️\n", tempo);
	
	return 0;
}