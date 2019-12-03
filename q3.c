#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define tam 21
#define less 1e-20
#define a(i,j) a[(i)*tam+(j)]

void pivot(float *a, int *p, int *q){
    int n=tam;
    int i,j,k;
    int p_i,p_j,tmp;
    float tempf;
    float max;
    for (k=0;k<n;k++){
        p_i=-1,p_j=-1,max=0.0;
        for (i=k;i<n;i++) {
            for (j=k;j<n;j++) {
                if (fabs(a(i,j))>max){
                    max = fabs(a(i,j));
                    p_i=i;
                    p_j=j;
                }
            }
        }
        tmp=p[k];
        p[k]=p[p_i];
        p[p_i]=tmp;
        for (j=0;j<n;j++){
            tempf=a(k,j);
            a(k,j)=a(p_i,j);
            a(p_i,j)=tempf;
        }
        tmp=q[k];
        q[k]=q[p_j];
        q[p_j]=tmp;
        for (i=0;i<n;i++){
            tempf=a(i,k);
            a(i,k)=a(i,p_j);
            a(i,p_j)=tempf;
        }
        if ((fabs(a(k,k))>less)){
            for (i=k+1;i<n;i++){
                tempf=a(i,k)/=a(k,k);
                for (j=k+1;j<n;j++){
                    a(i,j)-=(tempf*a(k,j));
                }
            }
        }
    }
}


void resolve(float *a, float *x, int *p, int *q){
    int i,ii=0,ip,j,tmp;
    float temp_f;
    float temp_x[tam];
    puts("\nFase Px = x");
    for (i=0; i<tam; i++){
        temp_x[i]=x[p[i]];	
        printf("%.1lf\n",temp_x[i]);
    }
    puts("\nFase Lx = x");
    for (i=0;i<tam;i++){
        temp_f=temp_x[i];
        if (ii != 0){
            for (j=ii-1;j<i;j++){
                temp_f-=a(i,j)*temp_x[j];
            }
    	}
        else{
            if (temp_f!=0.0){
                ii=i+1;
            }
    	}
        temp_x[i]=temp_f;
        printf("%.1lf\n",temp_x[i]);
    }
    puts("\nFase x = Ux");
    temp_x[tam-1]/=a(tam-1,tam-1);
    for (i=tam-2;i>=0;i--){
        temp_f=temp_x[i];
        for (j=i+1;j<tam;j++){
            temp_f-=a(i,j)*temp_x[j];
        }
        temp_x[i]=(temp_f)/a(i,i);
    }
    for (i=0;i<tam;i++)
        printf("%.1lf\n",temp_x[i]);

    puts("\nFase x = Qx");
    for (i=0;i<tam;i++){
        x[i]=temp_x[q[i]];
        printf("%.1lf\n\n",x[i]);
    }
}


int main(){
    float a[]={
	0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
	1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,
	2,1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,
	3,2,1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,
	4,3,2,1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,
	5,4,3,2,1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
	6,5,4,3,2,1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,
	7,6,5,4,3,2,1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,
	8,7,6,5,4,3,2,1,0,1,2,3,4,5,6,7,8,9,10,11,12,
	9,8,7,6,5,4,3,2,1,0,1,2,3,4,5,6,7,8,9,10,11,
	10,9,8,7,6,5,4,3,2,1,0,1,2,3,4,5,6,7,8,9,10,
	11,10,9,8,7,6,5,4,3,2,1,0,1,2,3,4,5,6,7,8,9,
	12,11,10,9,8,7,6,5,4,3,2,1,0,1,2,3,4,5,6,7,8,
	13,12,11,10,9,8,7,6,5,4,3,2,1,0,1,2,3,4,5,6,7,
	14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,1,2,3,4,5,6,
	15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,1,2,3,4,5,
	16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,1,2,3,4,
	17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,1,2,3,
	18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,1,2,
	19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,1,
	20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0
	};
    float b[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21};
    int sig;
    int* pivoP = (int *)malloc(sizeof(int)*tam);
    int* pivoQ = (int *)malloc(sizeof(int)*tam);
    for (int i=0; i<tam; i++){
        pivoP[i]=i;
        pivoQ[i]=i;
        //printf("%.1lf|",b[i]);
        for (int j=0;j<tam; j++){
            //printf("%.1lf,",a(i,j));
        }
        //printf("|%d,%d",pivoP[i],pivoQ[i]);
        //puts("");
    }
    pivot(&a[0],pivoP,pivoQ);
    for (int i=0; i<tam; i++){
        printf("%.1lf|",b[i]);
        for (int j=0;j<tam; j++){
            printf("%.1lf,",a(i,j));
        }
        printf("|%d,%d",pivoP[i],pivoQ[i]);
        puts("");
    }
    resolve(&a[0],&b[0],pivoP,pivoQ);
    for (int i=0; i<tam; i++){
        printf("[");
        for (int j=0;j<tam; j++){
            printf("%.1lf,",a(i,j));
        }
        printf("] %.1lf",b[i]);
        puts("");
    }
}
