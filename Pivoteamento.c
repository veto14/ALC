#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void troca_linha(float **matriz, int i1, int i2,int ordem){
	
	int i;
	float aux;
	for(i =0; i < ordem; i++){
		aux = matriz[i1][i];
		matriz[i1][i] = matriz[i2][i];
		matriz[i2][i] = aux; 
	}
	
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

void pivoteamento_total(float **matriz, int ordem){

	//Pivoteamento total:
		for(int i = 0; i < ordem; i++){
			if(fabs(matriz[i][procura_pivo_coluna(matriz,ordem,i)])> fabs(matriz[procura_pivo_linha(matriz,ordem,i)][i]))
			{
				troca_coluna(matriz,i,procura_pivo_coluna(matriz,ordem,i),ordem);
			}
			if(fabs(matriz[i][procura_pivo_coluna(matriz,ordem,i)]) < fabs(matriz[procura_pivo_linha(matriz,ordem,i)][i]))
			{
				troca_linha(matriz,i,procura_pivo_linha(matriz,ordem,i),ordem);
			}
		}
}

int main (){

	float **matriz;
	int ordem,i = 0,j = 0;
	
	printf("Ordem da matriz:\n");
	scanf("%i",&ordem);
	
	matriz = malloc(sizeof(float*) * ordem);
	
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
	//Pivoteamento total:
		for(i = 0; i < ordem; i++){
			if(fabs(matriz[i][procura_pivo_coluna(matriz,ordem,i)])> fabs(matriz[procura_pivo_linha(matriz,ordem,i)][i]))
			{
				troca_coluna(matriz,i,procura_pivo_coluna(matriz,ordem,i),ordem);
			}
			if(fabs(matriz[i][procura_pivo_coluna(matriz,ordem,i)]) < fabs(matriz[procura_pivo_linha(matriz,ordem,i)][i]))
			{
				troca_linha(matriz,i,procura_pivo_linha(matriz,ordem,i),ordem);
			}	
		}
	for(i = 0; i < ordem; i++)
	{
		for(j = 0; j < ordem; j++)
		{
			printf("[%.2f]\t",matriz[i][j]);
		}	
		printf("\n");
	}
	
	
	for(i = 0;i < ordem; i++)
	{
		free(matriz[i]);
	}
	free(matriz);
return 0;
}
