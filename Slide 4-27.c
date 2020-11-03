#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pessoa{
    char nome[30];
    int idade;
} pessoa;

int menu();
pessoa* Insere(pessoa *p, int *quantidade);
void printar(pessoa *p, int *quantidade);
pessoa* DeletaPorNome(pessoa *p, int *quantidade); 
pessoa* DeletaTopo(pessoa *p, int *quantidade);
pessoa* LimpaPilha(pessoa *p, int *quantidade);

int main(){
    int escolha=0, quantidade=0;
    pessoa *pilha;

    pilha = (pessoa*) malloc(sizeof(pessoa));

    for(;;){
    escolha = menu();
        switch(escolha){
            case 0:
                pilha = Insere(pilha, &quantidade);
            break;

            case 1:
                pilha = DeletaTopo(pilha, &quantidade);
            break;

            case 2:
                pilha = DeletaPorNome(pilha, &quantidade);
            break;

            case 3:
                pilha = LimpaPilha(pilha, &quantidade);
            break;

            case 4:
                printar(pilha, &quantidade);
            break;

            case 5:

            break;

            default:
                printf("\nOP invalida!\n");
            break;
        }

    if(escolha == 5){
        free(pilha);
        break;
    }

    }

    return 0;
}


int menu(){
    int op=0;
    printf("0-Insere pessoa\n");
    printf("1-Deleta pessoa do topo\n");
    printf("2-Deleta pessoa por nome\n");
    printf("3-Limpa a pilha\n");
    printf("4-Lista na tela as pessoas\n");
    printf("5-Sair do programa\n");
    scanf("%d", &op);
    return op;
}

pessoa* Insere(pessoa *p, int *quantidade){
            
    printf("Digite um nome:");
    scanf("%s", &p[*quantidade].nome);

    printf("Digite uma idade:");
    scanf("%d", &p[*quantidade].idade);

    (*quantidade)++;

    p = (pessoa*) realloc(p, sizeof(pessoa)*( (*quantidade) +1) );

    return (pessoa*) p;
}

pessoa* DeletaTopo(pessoa *p, int *quantidade){
    (*quantidade)--;
    p = (pessoa*) realloc(p, sizeof(pessoa)*( (*quantidade) +1) );

    return (pessoa*) p;
}

void printar(pessoa *p, int *quantidade){

    if( (*quantidade) == 0){
        printf("\nLista vazia!\n");
        return;
    }

    for(int i=0; i< (*quantidade); i++){
        printf("-----posicao: %d\n", i);
        printf("%s\n", p[i].nome);
        printf("%d\n", p[i].idade);
    }

}

pessoa* LimpaPilha(pessoa *p, int *quantidade){
    *quantidade = 0;
    free(p);
    p = (pessoa*) malloc(sizeof(pessoa));
    return (pessoa*) p;
}

pessoa* DeletaPorNome(pessoa *p, int *quantidade){
    char AUX[30];
    int i=0;

    getchar();
    printf("Digite um nome para apagar:");
    scanf("%s",&AUX);

    while( strcmp(AUX,p[i].nome) != 0){

        i++;
        if(i > *quantidade){
            printf("\nERRO, nome nao encontrado\n");
            return (pessoa*) p;
        }
    }

    for(i; i<*quantidade; i++){
        p[i] = p[i+1];
    }

    *quantidade = (*quantidade) - 1;
    p = (pessoa*) realloc(p, sizeof(pessoa)*( (*quantidade) + 1));
    return (pessoa*) p; 
}