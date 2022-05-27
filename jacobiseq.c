#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 5
#define e 0.001
#define seed 1

void print_matrizA(int matriz[N][N]);
void print_matrizB(int matriz[N]);
void print_matrizC(float matriz[N][N]);
void print_matrizG(float matriz[N]);

int main()
{
    srand(seed);
    int **A;
    int *B;
    float *X,*X0;
    B = malloc(N * sizeof(int));
    X = malloc(N * sizeof(float));
    X0 = malloc(N * sizeof(float));
    A = malloc(N * sizeof(int));
    for(int i = 0;i<N;i++){
        A[i] = malloc(N * sizeof(int));
    }
    int criterio_convergencia;
    for (int i = 0; i < N; i++)
    {
        criterio_convergencia = 0;
        for (int j = 0; j < N; j++)
        {
            if(i == j)
            {
                A[i][j] = rand() % 1000;
            }
            else{
                A[i][j] = rand() % 100;
                criterio_convergencia += A[i][j];
            }
        }
        A[i][i] += criterio_convergencia;
    }
    for (int i = 0; i < N; i++)
    {
        B[i] = rand() % 1000;
        X0[i] = 0.0;
    }
    // printf("Matriz A:\n");
    // print_matrizA(A);
    // printf("Matriz B:\n");
    // print_matrizB(B);
    // printf("\n");
    float **C;
    C = malloc(N * sizeof(float));
    for(int i = 0;i<N;i++){
        C[i] = malloc(N * sizeof(float));
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == j)
            {
                C[i][j] = 0.0;
                continue;
            }
            C[i][j] = -(float)A[i][j] / (float)A[i][i];
        }
    }
    float *G;
    G = malloc(N * sizeof(float));
    for (int i = 0; i < N; i++)
    {
        G[i]= (float)B[i] / (float)A[i][i];
    }
    // printf("Matriz C:\n");
    // print_matrizC(C);
    // printf("Matriz G:\n");
    // print_matrizG(G);
    // printf("\n");
    float erro = e;
    float dx;
    float *CX;
    CX = malloc(N * sizeof(float));
    while(1==1)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < 1; j++)
            {
                CX[i] = 0.0;

                for (int k = 0; k < N; k++)
                {
                    CX[i] += C[i][k] * X0[k];
                }
            }
        }

        for (int i = 0; i < N; i++)
        {
            X[i] = CX[i] + G[i];
        }
        float maximoX = -1000000.00;
        float maximodX = -1000000.00;
        for(int i = 0;i<N;i++){
            maximoX = fmax(maximoX,fabs(X[i]));
        }
        maximoX = fabs(maximoX);
        float diferencaX;
        for(int i = 0;i<N;i++){
            diferencaX = fabs(X[i]-X0[i]);
            maximodX = fmax(maximodX,diferencaX);
        }
        dx = maximodX/maximoX;
        // printf("Matriz X:\n");
        // print_matrizG(X);
        // printf("\n");
        printf("maximoX = %f\n",maximoX);
        printf("maximodX = %f\n",maximodX);
        printf("dx = %f\n",dx);
        if(dx < erro) break;
        for(int i = 0;i<N;i++){
            X0[i] = X[i];
        }
    }
    printf("Escolha qual equacao vc quer substituir: \n");
    int n;
    scanf("%d",&n);
    while(n > N){
      printf("Escolha uma equacao valida: \n");
      scanf("%d",&n);
    }
    float resultado = 0.0;
    for(int i = 0;i<N;i++){
      resultado += A[n-1][i]*X[i];
    }
    printf("O resultado obtido foi %f\nresultado esperado eh %d\n",resultado,B[n-1]);
    return 0;
}

void print_matrizA(int matriz[N][N])
{
    printf("[ ");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d, ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("]\n");
}

void print_matrizB(int matriz[N])
{
    printf("[ ");
    for (int i = 0; i < N; i++)
    {
        printf("%d ,", matriz[i]);
    }
    printf("]\n");
}

void print_matrizC(float matriz[N][N])
{
    printf("[ ");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%f, ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("]\n");
}

void print_matrizG(float matriz[N])
{
    printf("[ ");
    for (int i = 0; i < N; i++)
    {
        printf("%f ,", matriz[i]);
    }
    printf("]\n");
}