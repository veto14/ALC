#include <stdio.h>

int main(){
    int i,j,k,n;
    float A[50][50],c,x[50],soma=0.0;
    printf("\nInsira a ordem da matriz: ");
    scanf("%d",&n);
    printf("\nInsira os elementos da matriz, note que o elemento extra de cada linha faz parte do vetor solucao:\n\n");
    for(i=1; i<=n; i++){
        for(j=1; j<=(n+1); j++){
            printf("A[%d][%d] : ", i,j);
            scanf("%f",&A[i][j]);
        }
    }
    for(i=n; i>0; i--){
        for (j=i-1; j>=0; j--) {
            c = A[j][i]/A[i][i];
            for (k=0; k<=n+1; k++) {
                A[j][k] = A[j][k]-(c*A[i][k]);
            }
        }
	}
    for(i = 1; i <= n; i++){
        printf("[");
        for(j = 1; j <= n+1; j++){
            printf("%f ",A[i][j]);
        }
        printf("]\n");
    }
}
