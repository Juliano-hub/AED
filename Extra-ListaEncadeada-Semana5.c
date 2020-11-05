#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct dados{
    char nome[20];
    int telefone;
}dados;

typedef struct Nodo{
    dados dado;
    struct Nodo *pProx;
}Nodo;

typedef struct inicio{
    Nodo *pIni;
}inicio;

int menu();
inicio* criaLista();
Nodo* criaNodo();
void adicionar(inicio *p, Nodo *AUX);
Nodo* buscar(inicio *p);
void remover(inicio *p, Nodo *AUX);
void printar(inicio *p);
void freeAgenda(inicio *p);

int main(){
    inicio *lista;
    Nodo *AUX;

    int escolha=0;
    lista = criaLista();
    for(;;){

        escolha = menu();

        switch(escolha){
            case 1:
                AUX = criaNodo();

                adicionar(lista, AUX);
            break;

            case 2:
                AUX = buscar(lista);
                if(AUX != NULL){
                    printf("\n-----Dado encontrado:");
                    printf("\nNome:%s", AUX->dado.nome);
                    printf("\nTelefone:%d\n", AUX->dado.telefone);
                }
            break;

            case 3:
                AUX = buscar(lista);

                if(AUX != NULL){
                    remover(lista, AUX);
                }
            break;

            case 4:
                printar(lista);
            break;

            case 5:

            break;

            default:
                printf("\nOp nao encontrada!\n");
            break;
        }

    if(escolha == 5){
        freeAgenda(lista);
        break;
    }

    }

    return 0;
}

int menu(){
    int escolha;
    printf("1-Adicionar\n");
    printf("2-Buscar\n");
    printf("3-Apagar\n");
    printf("4-Listar\n");
    printf("5-Sair\n");
    scanf("%d", &escolha);

    return escolha;
}

inicio* criaLista(){
    inicio *AUX;
    AUX = (inicio*) malloc(sizeof(inicio));

    if(AUX == NULL){
        printf("\nNao foi possivel fazer o malloc!\n");
    }
    
    AUX->pIni = NULL;

    return (inicio*) AUX;
}

Nodo* criaNodo(){
    Nodo *AUX;

    AUX = (Nodo*) malloc(sizeof(Nodo));
    printf("Digite um nome:");
    scanf("%s", &AUX->dado.nome);
    printf("Digite uma telefone:");
    scanf("%d", &AUX->dado.telefone);

    AUX->pProx = NULL;

    return (Nodo*) AUX;
}

void adicionar(inicio *p, Nodo *AUX){
    Nodo *inicio_AUX;

    // adiciona no inicio caso for vazio a primeira vez
    if(p->pIni == NULL){
        p->pIni = AUX;
        p->pIni->pProx = NULL;

        return;
    }

    inicio_AUX = p->pIni;
    // inicio_AUX aponta para o primeiro elemento

    // enquanto o próximo conteudo n for NULL para ADD no fim, ele passa para o próximo conteúdo
    while(inicio_AUX->pProx != NULL){
        inicio_AUX = inicio_AUX->pProx;
    }

    inicio_AUX->pProx = AUX;
    // ADD o conteudo do nodo AUX no próximo elemento


    return;
}

Nodo* buscar(inicio *p){
    Nodo *inicio_AUX;
    Nodo *Vazio;
    char c[20];

    Vazio = NULL;
    inicio_AUX = p->pIni;
    // inicio_AUX aponta para o primeiro elemento

    if(inicio_AUX == NULL){
        printf("-----Lista Vazia!\n");
        return (Nodo*) Vazio;
    }

    printf("\nDigite um nome:");
    scanf("%s", &c);

    while(strcmp(c, inicio_AUX->dado.nome) != 0){

        inicio_AUX = inicio_AUX->pProx;

        if(inicio_AUX == NULL){
            printf("-----Nome nao encontrado!\n");
        return (Nodo*) Vazio;
        }

    }
    //printf("-----Nome encotrado:");
    //printf("\nNome: %s", inicio_AUX->dado.nome);
    //printf("\ntelefone: %d\n", inicio_AUX->dado.telefone);

    return (Nodo*) inicio_AUX;
}

void remover(inicio *p, Nodo *AUX){
    Nodo *inicio_AUX;

    inicio_AUX = p->pIni;
    // inicio_AUX aponta para o primeiro elemento


    if(strcmp(inicio_AUX->dado.nome, AUX->dado.nome) == 0){
        p->pIni = p->pIni->pProx;
        free(inicio_AUX);
        return;
    }

    while(strcmp(inicio_AUX->pProx->dado.nome, AUX->dado.nome) != 0){
        inicio_AUX = inicio_AUX->pProx;
    }

    inicio_AUX->pProx = AUX->pProx;
    free(AUX);

    return;
}


void printar(inicio *p){
    Nodo *inicio_AUX;

    inicio_AUX = p->pIni;
    // inicio_AUX aponta para o primeiro elemento

    if(inicio_AUX == NULL){
        printf("-----Lista Vazia!\n");
        return;
    }

    printf("\n-----Lista\n");

    // enquanto o conteúdo não for NULL
    while(inicio_AUX != NULL){
        printf("nome: %s\n", inicio_AUX->dado.nome);
        printf("telefone: %d\n", inicio_AUX->dado.telefone);

        // ele passa para o próximo conteúdo
        inicio_AUX = inicio_AUX->pProx;
    }

}

void freeAgenda(inicio *p){
        Nodo *AUX;

        AUX = p->pIni;

        while( p->pIni != NULL ){

            p->pIni = (p->pIni->pProx);
            free(AUX);
        }
        
        free(p);   
    
}


