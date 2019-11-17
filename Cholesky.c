#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 

#define tamA 3
#define TINY 1e-20
#define a(i,j) a[(i)*tamA+(j)]
#define lt(i,j) lt[(i)*tamA+(j)]
#define matriz(i,j) matriz[(i)*tamA+(j)]
#define mat(i) matriz[(i)*tamA+(i)]

double *cholesky(double *A, int n) {
    double *L = (double*)calloc(n * n, sizeof(double));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < (i+1); j++) {
            double s = 0;
            for (int k = 0; k < j; k++){
                s += L[i * n + k] * L[j * n + k];
            }
            L[i * n + j] = (i == j) ?
                           sqrt(A[i * n + i] - s) :
                           (1.0 / L[j * n + j] * (A[i * n + j] - s));
        }
    }
    return L;
}

void show_matrix(double *A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%2.5f ", A[i * n + j]);
        printf("\n");
    }
}

double* transpose(double* a, double* dest){
	double *lt = (double*)calloc(tamA * tamA, sizeof(double));
	for (int i = 0; i < tamA; i++){
        for (int j = 0; j < tamA; j++) {
        	lt(j,i) = a(i,j);
        }
    }
    return lt;
}

void substituicao(double *matriz, double *vetor, double *x){
	int i = 0, j = 0;
	float aux = 0;
	for (i = tamA -1; i >= 0; i--){	
		aux = 0;
		for (j = i+1; j < tamA; ++j){
			aux += (matriz(i,j) * x[j]);
		}
		x[i] = (vetor[i] - aux) / mat(i);
	}
}

void substituicao2(double *matriz, double* vetor, double *x){
	int i = 0, j = 0;
	double aux = 0;
	for (i = 0; i < tamA; i++){	
		aux = 0;
		for (j = 0; j < i; j++){
			aux += (matriz(i,j) * x[j]);
		}
		x[i] = (vetor[i] - aux) / mat(i);
	}
}

int main() {
    int n = 3;
    double m1[] = {1, 1, 0,
                   1, 2, -1,
                   0, -1, 3};
    double b[3] = {1,2,3};
    double *c1 = cholesky(m1, n);
    show_matrix(c1, n);
    printf("\n");
    double *ct = transpose(c1,ct);
    show_matrix(ct,n);
    double *xtemp = (double*)malloc(sizeof(double) * n);
    double *x = (double*)malloc(sizeof(double) * n);
    printf("\n");
    substituicao2(c1,b,xtemp);
    for(int i = 0; i < tamA; i++){
    	printf("%lf ",xtemp[i]);
	}
	printf("\n");
	substituicao(ct,xtemp,x);
	for(int i = 0; i < tamA; i++){
    	printf("%lf ",x[i]);
	}
	free(x);
	free(xtemp);
    free(c1);
    return 0;
}
