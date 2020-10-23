#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *realloc_realloc(void *pont, size_t newsize);

int main(){
    void *ponteiro;
    size_t tamanho=0;
    size_t tamanhoAUX=0;

    printf("Digite um valor para o malloc:");
    scanf("%Iu",&tamanho);

    ponteiro = (void*) malloc(sizeof(size_t)*tamanho);

    if(ponteiro == NULL){
        printf("Nao foi possivel fazer o malloc!");
        exit(0);
    }


    printf("\nDigite um tamanho para reallocar:");
    scanf("%Iu",&tamanhoAUX);

    ponteiro = realloc_realloc(ponteiro,tamanhoAUX);

    //printf("%p\n",ponteiro);

    free(ponteiro);

    //getchar();
    //getchar();
    return 0;
}


void *realloc_realloc(void *pont, size_t newsize){
    void *AUX;

    AUX = malloc(sizeof(size_t)*newsize);

    if(AUX == NULL){
        printf("Nao foi possivel fazer o malloc!");
        exit(0);
    }

    AUX=  memcpy(AUX,pont,newsize);

    //printf("%p\n",AUX);
    free(pont);

    return (void*) AUX;
}
