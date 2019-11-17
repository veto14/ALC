#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void troca_linha_vet(float *vetor, int i1, int i2){
	int i;
	float aux = 0;
	aux = vetor[i1];
	vetor[i1] = vetor[i2];
	vetor[i2] = aux;
}
void troca_linha(float **matriz, int i1, int i2,int ordem,float *vetor){
	
	int i;
	float aux;
	for(i =0; i < ordem; i++){
		aux = matriz[i1][i];
		matriz[i1][i] = matriz[i2][i];
		matriz[i2][i] = aux; 
	}
	troca_linha_vet(vetor,i1,i2);	
}
void troca_coluna(float **matriz, int j1, int j2,int ordem){
	
	int i;
	float aux;
	for(i =0; i < ordem; i++){
		aux = matriz[i][j1];
		matriz[i][j1] = matriz[i][j2];
		matriz[i][j2] = aux; 
	}
	
}

int procura_pivo_linha(float **matriz,int ordem, int pivo){
	int linha = pivo,i;
	for(i = pivo; i < ordem; i++){
		if(matriz[pivo][linha] < matriz[i][pivo])
		{
			linha = i;
		}
	}
	return linha;
}

int procura_pivo_coluna(float **matriz,int ordem, int pivo){		
	int coluna = pivo;
	int i;
		for(i = pivo; i < ordem; i++){
		if(matriz[pivo][coluna] < matriz[pivo][i])
		{
			coluna = i;
		}
	}
	return coluna;
}

void pivoteamento_total(float **matriz, int ordem,float *vetor){
	int i = 0;
	//Pivoteamento total:
	int linha = 0, coluna = 0;
		for(i = 0; i < ordem; i++){
			coluna = procura_pivo_coluna(matriz,ordem,i);
			linha = procura_pivo_linha(matriz,ordem,i);

			if(fabs(matriz[i][coluna])> fabs(matriz[linha][i]))
			{
				troca_coluna(matriz,i,coluna,ordem);
			}
			if(fabs(matriz[i][coluna]) < fabs(matriz[linha][i]))
			{
				troca_linha(matriz,i,linha,ordem,vetor);
			}
		}
}

void escalonamento(float **A,int n,float *vetor_b){
	float c = 0;
	int j,i,k;
	for(j = 0; j< n; j++){ //loop pra escalonar
        for(i = 0; i< n; i++){
            if(i > j){
                c = A[i][j] / A[j][j];
                for(k = 0; k < n; k++){
                    A[i][k] = A[i][k] - (c*A[j][k]);
                }
                vetor_b[i] = vetor_b[i] - (c*vetor_b[j]);
            }
        }
    }
}
void substituicao(float **matriz, int ordem, float *vetor, float *x){
	int i = 0, j = 0;
	int omi = 0;
	float aux = 0;
	for (i = ordem -1; i >= 0; i--)
	{	
		aux = 0;
		omi = ordem - i -1;
		for (j = i+1; j < ordem; ++j)
		{
			aux += (matriz[i][j] * x[j]);
		}
		x[i] = (vetor[i] - aux) / matriz[i][i];
	}
}
int main (){

	float **matriz,*vetor_b,*x;
	int ordem,i = 0,j = 0;
	
	printf("Ordem da matriz:\n");
	scanf("%i",&ordem);
	//Alocando espaço da memória:
		matriz = malloc(sizeof(float*) * ordem);
		vetor_b = malloc(sizeof(float) * ordem);
		x = malloc(sizeof(float) * ordem);
		
		for(i = 0;i < ordem; i++)
		{
			matriz[i] = malloc(sizeof(float) * ordem);
		}
	
	for(i = 0; i < ordem; i++)
	{
		for(j = 0; j < ordem; j++)
		{
			scanf("%f",&matriz[i][j]);
		}	
	}
	printf("Agora, insira os dados do vetor b:\n");
	for (i = 0; i < ordem; ++i) {
		scanf("%f",&vetor_b[i]);
	}
	//Pivoteamento total:
		pivoteamento_total(matriz,ordem,vetor_b);
	//

	printf("===============MATRIZ===============\n");
	for(i = 0; i < ordem; i++) {
		for(j = 0; j < ordem; j++)
		{
			printf("[%f] ",matriz[i][j]);
		}	
		printf("\n");
	}
	printf("===============VETOR-B===============\n");
	
	for(j = 0; j < ordem; j++) {
		printf("[%f]\n",vetor_b[j]);
	}
	printf("===============APOS=ESCALONAMENTO===============\n\n\n");
	escalonamento(matriz,ordem,vetor_b);
	printf("===============MATRIZ===============\n");
	for(i = 0; i < ordem; i++) {
		for(j = 0; j < ordem; j++)
		{
			printf("[%f] ",matriz[i][j]);
		}	
		printf("\n");
	}
	printf("===============VETOR-B===============\n");
	
	for(j = 0; j < ordem; j++) {
		printf("[%f]\n",vetor_b[j]);
	}
	substituicao(matriz,ordem,vetor_b,x);
	printf("===============SOLUCOES===============\n");
	for (i = 0; i < ordem; ++i)
	{
		printf("X[%i]: %f\n",i,x[i]);
	}
	printf("\n");
	//Liberando memória alocada:
		for(i = 0;i < ordem; i++)
		{
			free(matriz[i]);
		}
		free(matriz);
		free(vetor_b);
		free(x);
return 0;
}
