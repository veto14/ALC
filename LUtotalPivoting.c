#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define tamA 3
#define TINY 1e-20
#define a(i,j) a[(i)*tamA+(j)]

void h_pivot_decomp(float *a, int *p, int *q){
    int i,j,k;
    int n=tamA;
    int pi,pj,tmp;
    float max;
    float ftmp;
    for (k=0;k<n;k++){
        pi=-1,pj=-1,max=0.0;
        //achar o pivo na submatriz A(k:n,k:n)
        for (i=k;i<n;i++) {
            for (j=k;j<n;j++) {	
                if (fabs(a(i,j))>max){
                    max = fabs(a(i,j));
                    pi=i;
                    pj=j;
                }
            }
        }
        //troca linhas
        tmp=p[k];
        p[k]=p[pi];
        p[pi]=tmp;
        for (j=0;j<n;j++){
            ftmp=a(k,j);
            a(k,j)=a(pi,j);
            a(pi,j)=ftmp;
        }
        //troca colunas
        tmp=q[k];
        q[k]=q[pj];
        q[pj]=tmp;
        for (i=0;i<n;i++){
            ftmp=a(i,k);
            a(i,k)=a(i,pj);
            a(i,pj)=ftmp;
        }
        //fim do pivo

        //checando o tamanho do pivo e decompondo
        if ((fabs(a(k,k))>TINY)){
            for (i=k+1;i<n;i++){
                //Normalizacao das colunas
                ftmp=a(i,k)/=a(k,k);
                for (j=k+1;j<n;j++){
                    //a(ik)*a(kj) subtraidos dos elementos da submatriz inferior direita
                    a(i,j)-=(ftmp*a(k,j));
                }
            }
        }
        //Fim da decomposicao
    }
}


void h_solve(float *a, float *x, int *p, int *q){
    int i,ii=0,ip,j,tmp;
    float ftmp;
    float xtmp[tamA];
    //troca linhas (x = Px)
    puts("\nFase x = Px");
    for (i=0; i<tamA; i++){
        xtmp[i]=x[p[i]]; //valor que tinha que estar aqui
        printf("x:%.1lf,q:%d\n",xtmp[i],q[i]);
    }
    //Lx=x
    puts("\nFase Lx = x");
    for (i=0;i<tamA;i++){
        ftmp=xtmp[i];
        if (ii != 0)
            for (j=ii-1;j<i;j++)
                ftmp-=a(i,j)*xtmp[j];
        else
            if (ftmp!=0.0)
                ii=i+1;
        xtmp[i]=ftmp;
        printf("x:%.1lf,q:%d\n",xtmp[i],q[i]);
    }
    puts("\nFase Ux=x");
    //resolvendo Uy = z
    xtmp[tamA-1]/=a(tamA-1,tamA-1);
    for (i=tamA-2;i>=0;i--){
        ftmp=xtmp[i];
        for (j=i+1;j<tamA;j++){
            ftmp-=a(i,j)*xtmp[j];
        }
        xtmp[i]=(ftmp)/a(i,i);
    }
    for (i=0;i<tamA;i++)
        printf("x:%.1lf,q:%d\n",xtmp[i],q[i]);

    //resolvendo x = Qy
    puts("\nFase x=Qx");
    for (i=0;i<tamA;i++){
        x[i]=xtmp[q[i]];
        printf("x:%.1lf,q:%d\n",x[i],q[i]);
    }
}


int main(){
    //possiveis matrizes 3x3 com solucoes
    float a[]={1,3,-2,3,5,6,2,4,3};
    float b[]={5,7,8};
    //float a[]={1,2,3,2,-1,1,3,4,-1};
    //float b[]={14,3,8};
    //float a[]={1,-2,1,0,2,2,-2,4,2};
    //float b[]={1,4,2};
    int sig;
    puts("Entradas Declaradas!");

    //pivot array (not used currently)
    int* p_pivot = (int *)malloc(sizeof(int)*tamA);
    int* q_pivot = (int *)malloc(sizeof(int)*tamA);
    puts("Comecando o processo");
    for (unsigned int i=0; i<tamA; i++){
        p_pivot[i]=i;
        q_pivot[i]=i;
        printf("%.1lf|",b[i]);
        for (unsigned int j=0;j<tamA; j++){
            printf("%.1lf,",a(i,j));
        }
        printf(" Pivo p e Pivo q : |%d,%d",p_pivot[i],q_pivot[i]);
        puts("");
    }

    h_pivot_decomp(&a[0],p_pivot,q_pivot);
    puts("\nDepois do pivo");
    for (unsigned int i=0; i<tamA; i++){
        printf("%.1lf|",b[i]);
        for (unsigned int j=0;j<tamA; j++){
            printf("%.1lf,",a(i,j));
        }
        printf("|%d,%d",p_pivot[i],q_pivot[i]);
        puts("");
    }

    h_solve(&a[0],&b[0],p_pivot,q_pivot);
    puts("\nSolucao pronta!");
    puts("\nA = ");
    for (unsigned int i=0; i<tamA; i++){
        for (unsigned int j=0;j<tamA; j++){
            printf("%.1lf,",a(i,j));
        }
        puts("");
    }
    puts("\nb' (Solucoes) = ");
    for (unsigned int i=0; i<tamA; i++){
    	printf("%.1lf\n",b[i]);
	}
}
