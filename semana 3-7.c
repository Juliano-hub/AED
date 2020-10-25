#include <stdio.h>
#include <stdlib.h>

int *apaga(int *vetor,int *n);

int main(){
    int *vetor,tamanho=0,i=0;
    printf("Digite o valor de n:");
    scanf("%d",&tamanho);

    vetor = (int*) malloc(sizeof(int)*(tamanho+1) );

    for(i=0;i<tamanho;i++){
        scanf("%d", (vetor+i) );
    }

    vetor = apaga(vetor,&tamanho);

    for(i=0;i<tamanho;i++){
        printf("%d ", *(vetor+i) );
    }

    free(vetor);
    return 0;
}

int *apaga(int *vetor,int *n){
    int i=0,j=0,aux=0;

    for(i=0; i<*n ;i++){
        for(j=i+1; j<*n ;j++){
        if( *(vetor+j) == *(vetor+i) ){
            aux=j;
            while(aux < *n){
                *(vetor+aux) = *(vetor+(aux+1) );
                aux++;

            }
            *n = *n - 1;
            }else{
                j++;
            }

        }

    }

    vetor = realloc(vetor, sizeof(int)*( (*n) + 1) );

    return (int*) vetor;
}