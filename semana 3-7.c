#include <stdio.h>
#include <stdlib.h>

float *apaga(float *vetor,int *n);

int main(){
    float *vetor;
    int tamanho=-1,i=0;

    while(tamanho < 0){
    printf("Digite o valor de n:");
    scanf("%d",&tamanho);
    }

    vetor = (float*) malloc(sizeof(float)*(tamanho+1) );

    for(i=0;i<tamanho;i++){
        scanf("%f", (vetor+i) );
    }

    vetor = apaga(vetor,&tamanho);

    printf("\nVetor:\n");
    for(i=0;i<tamanho;i++){
        printf("%.2f ", *(vetor+i) );
    }

    free(vetor);
    return 0;
}

float *apaga(float *vetor,int *n){
    int i=0,j=0,aux=0;

    for(i=0; i<*n ;i++){
        j = i+1;

        while(j < *n){
            if( *(vetor+i) == *(vetor+j) ){
                aux = j;

                while(aux < (*n) ){
                    *(vetor+aux) = *(vetor+(aux+1) );
                    aux = aux + 1;
                }
                *n = *n - 1;
                
            }else{
                j++;
            }

        }

    }

    vetor = realloc(vetor, sizeof(float)*( (*n) + 1) );

    return (float*) vetor;
}