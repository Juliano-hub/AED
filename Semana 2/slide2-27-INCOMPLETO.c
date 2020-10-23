#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *replace_realloc(void *pont, size_t newsize);
void printar(void *pont,size_t p);

int main(){
    void *ponteiro;
    size_t tamanho=0;

    printf("Digite um valor para o malloc:");
    scanf("%d",&tamanho);

    ponteiro = (int *) malloc(sizeof(int)*tamanho);

    printar(ponteiro,tamanho);

    printf("Digite um tamanho para reallocar:");
    scanf("%d",&tamanho);

    ponteiro = replace_realloc(ponteiro,tamanho);

    printar(ponteiro,tamanho);

    free (ponteiro);
    return 0;
}


void *replace_realloc(void *pont, size_t newsize){
    void *new_ptr;

    new_ptr = (int*) malloc(sizeof(int)*newsize);

   memcpy(new_ptr,pont,newsize);

    return pont;
}

void printar(void *pont,size_t p){
    int i=0;

    for(i=0;i<p;i++)
        *(int*) (pont +(sizeof(int) *(i))) = i;

    printf("-----Vetor:\n");

    for(i=0;i<p;i++)
        printf("%d ", *(int*) (pont+sizeof(int)*i));
}