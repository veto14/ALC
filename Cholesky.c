#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 

#define tamA 3
#define TINY 1e-20
#define a(i,j) a[(i)*tamA+(j)]
#define lt(i,j) lt[(i)*tamA+(j)]
#define matriz(i,j) matriz[(i)*tamA+(j)]
#define mat(i) matriz[(i)*tamA+(i)]

void show_matrix(double *A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%2.5f ", A[i * n + j]);
        printf("\n");
    }
}

int isSimetrica(double* A, int n){
	int elem = 0;
	int i,j,k;
	double **a = (double**)malloc(sizeof(double*) * n);
	double **at = (double**)malloc(sizeof(double*) * n);
	for(i = 0; i < n; i++){
		a[i] = (double*)malloc(sizeof(double) * n);
		at[i] = (double*)malloc(sizeof(double) * n);
	}
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			a[i][j] = A[elem];
			at[j][i] = A[elem];
			elem++;
		}
	}
	for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
        	if(a[i][j] != at[i][j]){
        		return 0;
			}
		}
    }
	return 1;
}

int determinante(double *A, int n){
	int elem = 0;
	double factor = 0;	
    double temp = 0;	
    int count = 0;
	int i,j,k;
	double **a = (double**)malloc(sizeof(double*) * n);
	for(i = 0; i < n; i++){
		a[i] = (double*)malloc(sizeof(double) * n);
	}
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			a[i][j] = A[elem];
			elem++;
		}
	}
	for(i = 0; i < n - 1; i++){
        if(a[i][i] == 0){
            for(k = i; k < n; k++){
                if(a[k][i] != 0){
                    for(j = 0; j < n; j++){
                        temp = a[i][j];
                        a[i][j] = a[k][j];
                        a[k][j] = temp;
                    }
                    k = n;
                }
            }
            count++;
        }

        if(a[i][i] != 0){
            for(k = i + 1; k < n; k++){
                factor = -1.0 * a[k][i] /  a[i][i];
                for(j = i; j < n; j++){
                    a[k][j] = a[k][j] + (factor * a[i][j]);
                }
            }
        }
    }
    temp = 1.0;
    for(i = 0; i < n; i++){
    	temp *= a[i][i];
    }
    if(count % 2 == 0){
        return temp;
    }
    else{
        return -1.0 * temp;
	}
}

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
    if(isSimetrica(m1,n) != 1 || determinante(m1,n) == 0){
    	puts("O sistema nao possui solucao, ja que a matriz dada nao e simetrica ou nao cumpre os prerequisitos de matriz definida positiva.\n");
    	return 1;
	}
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
