#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 5
#define e 0.01
#define seed 1
double X0[N][1];

void print_matrizA(int matriz[N][N]);
void print_matrizB(int matriz[N][1]);
void print_matrizC(double matriz[N][N]);
void print_matrizG(double matriz[N][1]);

int main()
{
    srand(seed);
    int A[N][N];
    double X[N][1];
    int B[N][1];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A[i][j] = rand() % 100;
            if(i == j)
            {
                A[i][j] = rand() % 1000;
            }
        }
    }
    for (int i = 0; i < N; i++)
    {
        B[i][0] = rand() % 100;
    }
    printf("Matriz A:\n");
    print_matrizA(A);
    printf("Matriz B:\n");
    print_matrizB(B);
    printf("\n");
    double C[N][N];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == j)
            {
                C[i][j] = 0.0;
                continue;
            }
            C[i][j] = -(double)A[i][j] / (double)A[i][i];
        }
    }
    double G[N][1];
    for (int i = 0; i < N; i++)
    {
        G[i][0] = (double)B[i][0] / (double)A[i][i];
    }
    printf("Matriz C:\n");
    print_matrizC(C);
    printf("Matriz G:\n");
    print_matrizG(G);
    printf("\n");
    double erro = e;
    double dx;
    while(1==1)
    {
        double CX[N][1];
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < 1; j++)
            {
                CX[i][j] = 0.0;

                for (int k = 0; k < N; k++)
                {
                    CX[i][j] += C[i][k] * X0[k][j];
                }
            }
        }

        for (int i = 0; i < N; i++)
        {
            X[i][0] = CX[i][0] + G[i][0];
        }
        double maximoX = -1000000.00;
        double maximodX = -1000000.00;
        for(int i = 0;i<N;i++){
            maximoX = fmax(maximoX,fabs(X[i][0]));
        }
        maximoX = fabs(maximoX);
        double diferencaX;
        for(int i = 0;i<N;i++){
            diferencaX = fabs(X[i][0]-X0[i][0]);
            maximodX = fmax(maximodX,diferencaX);
        }
        dx = maximodX/maximoX;
        printf("Matriz X:\n");
        print_matrizG(X);
        printf("\n");
        printf("maximoX = %f\n",maximoX);
        printf("maximodX = %f\n",maximodX);
        printf("dx = %f\n",dx);
        if(dx < erro) break;
        for(int i = 0;i<N;i++){
            X0[i][0] = X[i][0];
        }
    }
    printf("Escolha qual equacao vc quer substituir: \n");
    int n;
    scanf("%d",&n);
    while(n > N){
      printf("Escolha uma equacao valida: \n");
      scanf("%d",&n);
    }
    double resultado = 0.0;
    for(int i = 0;i<N;i++){
      resultado += A[n-1][i]*X[i][0];
    }
    printf("O resultado obtido foi %f\nresultado esperado eh %d\n",resultado,B[n-1][0]);
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

void print_matrizB(int matriz[N][1])
{
    printf("[ ");
    for (int i = 0; i < N; i++)
    {
        printf("%d ,", matriz[i][0]);
    }
    printf("]\n");
}

void print_matrizC(double matriz[N][N])
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

void print_matrizG(double matriz[N][1])
{
    printf("[ ");
    for (int i = 0; i < N; i++)
    {
        printf("%f ,", matriz[i][0]);
    }
    printf("]\n");
}