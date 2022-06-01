#include "parametro.h"

int main(int argc, char *argv[]) {
	int mode = atoi(argv[1]);
	int N, T;
	FILE *in_file_seq = fopen("testeseq.txt", "r"); // read only
	FILE *in_file_par = fopen("testepar.txt", "r"); // read only
	FILE *out_file = fopen("resultado.txt", "a+");  // write only

	// test for files not existing.
	if (in_file == NULL || out_file == NULL) {
		printf("Error! Could not open file\n");
		exit(-1); // must include stdlib.h
	}

	// write to file vs write to screen
	// fprintf(file, "this is a test %d\n", integer); // write to file

	// fprintf(stdout, "this is a test %d\n", integer); // write to screen
	// printf("this is a test %d\n", integer);			 // write to screen

	// read from file/keyboard. remember the ampersands!
	// fscanf(file, "%d %d", &int_var_1, &int_var_2);

	// fscanf(stdin, "%d %d", &int_var_1, &int_var_2);
	// scanf("%d %d", &int_var_1, &int_var_2);

	if (mode == 1 || mode == 3) {
		fprintf(out_file, "Rodando no modo %d\n", mode);
		while (1 == 1) {
			fscanf(in_file_seq, "%d %d", &N, &T);

			if (N == 0)
				break;

			seq = jacobiseq(N);

			// printf("%d %d %f %f %f\n", N, T,jacobipar(N,T), seq);
			fprintf(out_file, "%d %f\n", N, seq);
		}
	}

	if (mode == 2 || mode == 3) {
		fprintf(out_file, "Rodando no modo %d\n", mode);
		while (1 == 1) {
			fscanf(in_file_par, "%d %d", &N, &T);

			if (N == 0)
				break;

			par = jacobipar(N, T);

			// printf("%d %d %f %f %f\n", N, T,jacobipar(N,T), seq);
			fprintf(out_file, "%d %d %f\n", N, T, par);
		}
	}

	fclose(in_file_seq);
	fclose(in_file_par);
	fclose(out_file);

	return 0;
}