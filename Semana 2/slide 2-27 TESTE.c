#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *realloc_realloc(void *pont, size_t newsize, size_t oldsize);

int main(){
    void *ponteiro;
    size_t tamanho=0;
    size_t tamanhoAUX=0;
    int i=0;
    printf("Digite um valor para o malloc:");
    scanf("%Iu",&tamanho);

    ponteiro = (void*) malloc(sizeof(size_t)*tamanho);

    if(ponteiro == NULL){
        printf("Nao foi possivel fazer o malloc!");
        exit(0);
    }


    *(&ponteiro) = 11;
    *(&ponteiro +1) = 12;
    *(&ponteiro +2) = 13;
    *(&ponteiro +3) = 14;
    *(&ponteiro +4) = 15;
    *(&ponteiro +5) = 16;

        for(int i=0;i<tamanho;i++)
    printf("%d ",*(&ponteiro+i));

    printf("\nDigite um tamanho para reallocar:");
    scanf("%Iu",&tamanhoAUX);

    ponteiro = realloc_realloc(ponteiro,tamanhoAUX,tamanho);

    *(&ponteiro +5) = 16;
    *(&ponteiro +6) = 17;
    *(&ponteiro +7) = 18;
    *(&ponteiro +8) = 19;
    *(&ponteiro +9) = 20;

    for(int i=0;i<tamanhoAUX;i++)
    printf("%d ",*(&ponteiro+i));

    free(ponteiro);
    return 0;
}


void *realloc_realloc(void *pont, size_t newsize, size_t oldsize){
    void *AUX;

    AUX = malloc(sizeof(size_t)*newsize);

    if(AUX == NULL){
        printf("Nao foi possivel fazer o malloc!");
        exit(0);
    }

    memcpy(AUX,&pont,oldsize);

    return (void*) AUX;
}
