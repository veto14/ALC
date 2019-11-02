#include <stdio.h>
 
int main(){
    int i,j,k,n;
    float A[50][50],c,x[50],soma=0.0;
    printf("\nInsira a ordem da matriz: ");
    scanf("%d",&n);
    printf("\nInsira os elementos da matriz, note que o elemento extra de cada linha é do vetor solucao:\n\n");
    for(i=1; i<=n; i++){
        for(j=1; j<=(n+1); j++){
            printf("A[%d][%d] : ", i,j);
            scanf("%f",&A[i][j]);
        }
    }
    for(j=1; j<=n; j++){ //loop pra escalonar
        for(i=1; i<=n; i++){
            if(i>j){
                c=A[i][j]/A[j][j];
                for(k=1; k<=n+1; k++){
                    A[i][k]=A[i][k]-c*A[j][k];
                }
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
    x[n]=A[n][n+1]/A[n][n];
    //substituição pra tras
    for(i=n-1; i>=1; i--){
        soma=0;
        for(j=i+1; j<=n; j++){
            soma=soma+A[i][j]*x[j];
        }
        x[i]=(A[i][n+1]-soma)/A[i][i];
    }
    printf("\n Solucoes: \n\n\n");
    for(i=1; i<=n; i++){
        printf("\nx%d=%f\t",i,x[i]); //printa as solucoes
    }
    return(0);
}