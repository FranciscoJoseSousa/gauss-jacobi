#include "parametro.h"

double **malloc_matrix_par(int lin, int col, int T) {
	double **matrix = (double **)malloc(lin * sizeof(double *));
	int i;
#pragma omp parallel for private(i) num_threads(T)
	for (i = 0; i < lin; ++i)
		matrix[i] = (double *)malloc(col * sizeof(double));

	return matrix;
}

void fill_matrix_par(double **matrix, int lin, int col, int T) {
	srand(seed);
#pragma omp parallel for num_threads(T) 
	for (int i = 0; i < lin; i++) {
		for (int j = 0; j < col; j++) {
			matrix[i][j] = rand() % 100;
			if (i == j && lin == col) {
				matrix[i][j] = rand() % 100;
			}
		}
	}
}

void fill_matrix_par_a(double **matrix, int lin, int col, int T) {
	srand(seed);
	int criterio_convergencia;
	for (int i = 0; i < lin; i++) {
		criterio_convergencia = 0;
		for (int j = 0; j < col; j++) {
			if (i == j) {
				matrix[i][i] += rand() % 100;
			} else {
				matrix[i][j] = rand() % 100;
				criterio_convergencia += matrix[i][j];
			}
		}
		matrix[i][i] += criterio_convergencia;
	}
}

void print_matrix_par(double **matrix, int lin, int col) {
	for (int i = 0; i < lin; i++) {
		for (int j = 0; j < col; j++) {
			printf("%-10f ", matrix[i][j]);
		}
		printf("\n");
	}
}

void get_matrix_par_c(
	double **matrix_a,
	double **matrix_c,
	int lin,
	int col,
	int T) {
#pragma omp parallel for num_threads(T) collapse(2)
	for (int i = 0; i < lin; i++) {
		for (int j = 0; j < col; j++) {
			if (i == j) {
				matrix_c[i][j] = 0.0;
			} else {
				matrix_c[i][j] =
					-(double)matrix_a[i][j] / (double)matrix_a[i][i];
			}
		}
	}
}

void get_matrix_par_g(
	double **matrix_a,
	double **matrix_b,
	double **matrix_g,
	int lin,
	int T) {
#pragma omp parallel for num_threads(T)
	for (int i = 0; i < lin; i++) {
		matrix_g[i][0] = (double)matrix_b[i][0] / (double)matrix_a[i][i];
	}
}

void apply_jacobi_par(
	double **matrix_c,
	double **matrix_g,
	double **matrix_x,
	double **matrix_x0,
	double **matrix_cx,
	int N,
	int T) {
	while (1 == 1) {
		double **matrix_cx = malloc_matrix_par(N, 1, T);
		double maximoX = -1000000.00;
		double maximodX = -1000000.00;
		double diferencaX;
		double dx;

		#pragma omp parallel for num_threads(T) 
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < 1; j++) {
				matrix_cx[i][j] = 0.0;
				for (int k = 0; k < N; k++) {
					matrix_cx[i][j] += matrix_c[i][k] * matrix_x0[k][j];
				}
			}
		}
		#pragma omp parallel for num_threads(T)
		for (int i = 0; i < N; i++) {
			matrix_x[i][0] = matrix_cx[i][0] + matrix_g[i][0];
		}

		for (int i = 0; i < N; i++) {
			maximoX = fmax(maximoX, fabs(matrix_x[i][0]));
		}

		maximoX = fabs(maximoX);
		for (int i = 0; i < N; i++) {
			diferencaX = fabs(matrix_x[i][0] - matrix_x0[i][0]);
			maximodX = fmax(maximodX, diferencaX);
		}

		dx = maximodX / maximoX;
		// printf("Matriz X:\n");
		// print_matrix_par(matrix_x, N, 1);
		// printf("\n");
		// printf("maximoX = %f\n", maximoX);
		// printf("maximodX = %f\n", maximodX);
		// printf("dx = %f\n", dx);
		if (dx < e){
			free_matrix(matrix_cx, N);
			break;
		}
#pragma omp parallel for num_threads(T)
		for (int i = 0; i < N; i++) {
			matrix_x0[i][0] = matrix_x[i][0];
		}
	}
}

void equacao_par(
	double **matrix_a,
	double **matrix_b,
	double **matrix_x,
	int N,
	int T) {
	int n = Ne, i;
	double resultado = 0.0;

/*printf("Escolha qual equacao_par vc quer substituir: \n");
scanf("%d", &n);
while (n > N) {
	printf("Escolha uma equacao_par valida: \n");
	scanf("%d", &n);
}*/
#pragma omp parallel for num_threads(T) private(i) reduction(+ : resultado)
	for (i = 0; i < N; i++) {
		resultado += matrix_a[n - 1][i] * matrix_x[i][0];
	}
	printf(
		"O resultado obtido foi %f\nresultado esperado eh %f\n",
		resultado,
		matrix_b[n - 1][0]);
}

double jacobipar(int N, int T) {
	double tempo = omp_get_wtime ();
	// Definir e alocar memoria para as matrizes
	double **matrix_a;
	double **matrix_b;
	double **matrix_c;
	double **matrix_g;
	double **matrix_x;
	double **matrix_x0;
	double **matrix_cx;
	omp_set_dynamic(0);     
	// Alocar memoria
	matrix_a = malloc_matrix_par(N, N, T);
	matrix_b = malloc_matrix_par(N, 1, T);
	matrix_c = malloc_matrix_par(N, N, T);
	matrix_g = malloc_matrix_par(N, 1, T);
	matrix_x = malloc_matrix_par(N, 1, T);
	matrix_x0 = malloc_matrix_par(N, 1, T);
	matrix_cx = malloc_matrix(N, 1);

	printf("Mem??ria alocada com sucesso! ????\n");
	fill_matrix_par_a(matrix_a, N, N, T);
	fill_matrix_par(matrix_b, N, 1, T);

	printf("Matriz prenchida com sucesso! ????\n");

	// print_matrix_par(matrix_a, N, N);
	// print_matrix_par(matrix_b, N, 1);

	printf("Matriz printada com sucesso! ????\n");
	get_matrix_par_c(matrix_a, matrix_c, N, N ,T);
	get_matrix_par_g(matrix_a, matrix_b, matrix_g, N ,T);
	apply_jacobi(matrix_c, matrix_g, matrix_x, matrix_x0,matrix_cx, N,T);

	equacao_par(matrix_a, matrix_b, matrix_x ,N ,T);
	free_matrix(matrix_a, N);
	free_matrix(matrix_b, N);
	free_matrix(matrix_c, N);
	free_matrix(matrix_g, N);
	free_matrix(matrix_x, N);
	free_matrix(matrix_x0, N);
	free_matrix(matrix_cx, N);

	printf("Matrizes   free  com sucesso! ????\n");

	tempo = omp_get_wtime () - tempo;

	printf("Tempo: %f\n\n", tempo);

	return tempo;
}