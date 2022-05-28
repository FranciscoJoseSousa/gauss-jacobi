#include "parametro.h"

int main(int argc, char *argv[]) {
	double tempo = omp_get_wtime ();
	int N = atoi(argv[1]);
	
	printf("Inicio do programa sequencial para N = %d:\n", N);
	
	jacoviseq_new(N);

	tempo = omp_get_wtime () - tempo;

	printf("Tempo de execução: %f ⏱️\n", tempo);
	
	return 0;
}