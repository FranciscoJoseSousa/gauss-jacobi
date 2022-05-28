#include "jacobipar.h"

int main(int argc, char *argv[]) {
	printf("Inicio do programa paralelo:\n");
	//int N = atoi(argv[1]);
	//int T = atoi(argv[2]);
	int N = 5;
	int T = 2;
	jacovipar_new(N,T);
	return 0;
}