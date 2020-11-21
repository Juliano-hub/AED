#include <stdio.h>
#include <stdlib.h>

typedef struct Dados{
    int valor;
}Dados;

typedef struct Nodo{
    Dados dado;
    struct Nodo *esquerda;
    struct Nodo *direita;
}Nodo;

Nodo *CriaNodo();
int adicionar(Nodo **INICIO, Nodo *AUX);
int menu();
void PrintarPreordem(Nodo **INICIO);
Nodo *buscar(Nodo **INICIO, int AUX);
void printar(Nodo **INICIO, int contadorEspaco);
void Remover(Nodo **INICIO, Nodo *AUX);
void Antecessor(Nodo **INICIO, Nodo **AUX);
void LiberaArvore(Nodo **INICIO);

int main(){
    Nodo *INICIO, *AUX;
    int escolha, BUSCA;

    INICIO = NULL;

    do{
        escolha = menu();

        switch(escolha){
            case 1:
                AUX = CriaNodo();
                if(AUX != NULL){
                    adicionar(&INICIO, AUX);
                }
            break;

            case 2:
                printf("Digite um numero para remover:");
                scanf("%d", &BUSCA);

                AUX = buscar(&INICIO, BUSCA);

                if(AUX != NULL){
                    if(AUX->dado.valor == BUSCA){
                        Remover(&INICIO, AUX);
                    }
                }

            break;

            case 3:
                printf("Digite um numero para a busca:");
                scanf("%d", &BUSCA);

                AUX = buscar(&INICIO, BUSCA);

                if(AUX != NULL){
                    if(AUX->dado.valor == BUSCA){
                        printf("Dado encontrado: %d\n", AUX->dado.valor);
                    }
                }

            break;

            case 4:
                PrintarPreordem(&INICIO);
            break;

            case 5:
            break;

            default:
            printf("\n OP invalida\n");
            break;
        }
    }while(escolha != 5);

    LiberaArvore(&INICIO);

    return 0;
}

int menu(){
    int op=0;
    do{
        printf("1-Adicionar\n");
        printf("2-Remover\n");
        printf("3-Buscar\n");
        printf("4-Printar PREORDEM\n");
        printf("5-Sair\n");
    scanf("%d", &op);

    }while(op <= 0 || op > 5);

    return op;
}

Nodo *CriaNodo(){
    Nodo *AUX;
    int num;

    AUX = (Nodo*) malloc(sizeof(Nodo));

    if(AUX == NULL){
        printf("\nNao foi possivel fazer o malloc!\n");
        return (Nodo*) NULL;
    }

    printf("\nDigite um numero:");
    scanf("%d", &num);
    AUX->dado.valor = num;

    AUX->esquerda = NULL;
    AUX->direita = NULL;

    return (Nodo*) AUX;
}

int adicionar(Nodo **INICIO, Nodo *AUX){

    if(*INICIO == NULL){
        // se inicio for igual a NULL, significa que achou um local vago
        *INICIO = AUX;
        // e coloca o dado lá
        return;
    }

    if( (*INICIO)->dado.valor > AUX->dado.valor){
        // se o valor digitado for menor que o atual
        adicionar(&( (*INICIO)->esquerda), AUX);


        Balanceamento( INICIO  );

        // ele vai para esquerda
        return;
    }
    
    if( (*INICIO)->dado.valor < AUX->dado.valor){
        // se o valor digitado for maior que o atual
        adicionar( &( (*INICIO)->direita), AUX);

        Balanceamento( INICIO  );

        // ele vai para direita
    }else{
        printf("\nTentou inserir um valor repitido!\n");
        free(AUX);
    }

}

void Remover(Nodo **INICIO, Nodo *AUX){
    Nodo *Reserva;

    if( (*INICIO) != NULL){


        if( (*INICIO)->dado.valor > AUX->dado.valor){
            // se o valor digitado for menor que o atual
            Remover( &( (*INICIO)->esquerda), AUX );
            // ele vai para esquerda

            // return para quando for desempilhar
            return;
        }

        if( (*INICIO)->dado.valor < AUX->dado.valor){
            // se o valor digitado for maior que o atual
            Remover( &( (*INICIO)->direita), AUX );
            // ele vai para direita
            return;
        }

        //-----Achou o dado que vai remover

        // se o dado que quero remover não tiver filho na direita (também está servindo para excluir as folhas)
        if( (*INICIO)->direita == NULL ){
            Reserva = *INICIO;
            // pega a posição que vai ser deletada
            *INICIO = (*INICIO)->esquerda;
            // ele passa para o filho da esquerda
            free(Reserva);
            return;
        }

        // se o dado que quero remover tem um filho a esquerda e tem outro na direita
        
        if( (*INICIO)->esquerda != NULL ){
            // eu passo a posição atual que quero remover e passo o filho a esquerda dela
            //(pois para remover deve pegar o filho mais a direita da subárvore a esquerda)
            // ou seja, pega o maior valor anterior do que o qual eu quero remover 

            Antecessor( INICIO, &( (*INICIO)->esquerda) );
            // pega o maior valor anterior do que eu quero remover 
            // a função faz o laço de percorrer até achar esse valor, pois só tem o caminho da direita para percorrer após ter andado 1 vez na esq
            return;
        }

    }else{
        printf("Erro, numero nao encontrado");
        return;
    }
}

void printar(Nodo **INICIO, int contadorEspaco){
    if( (*INICIO) != NULL){
                
        for(int i=0 ; i < contadorEspaco ; i++){
            printf(" ");
        }

        printf("%d", (*INICIO)->dado.valor );
        printf("\n");

        if( &( (*INICIO)->esquerda)  != NULL )
        printar( &( (*INICIO)->esquerda) , (contadorEspaco = contadorEspaco + 2) );
        if( &( (*INICIO)->direita)  != NULL )
        printar( &( (*INICIO)->direita), (contadorEspaco = contadorEspaco) );
    }
    
}

Nodo *buscar(Nodo **INICIO, int AUX){
    if( (*INICIO) == NULL){
        Nodo *NULLO = NULL;
        printf("\n Dado nao encontrado!\n");
        return (void *) NULLO;
    }


    if( (*INICIO)->dado.valor > AUX){
        buscar( &( (*INICIO)->esquerda), AUX );
        return;
    }

    if( (*INICIO)->dado.valor < AUX){
        buscar( &( (*INICIO)->direita), AUX );
        return;
    }

    if((*INICIO)->dado.valor == AUX){
        return (Nodo *) *INICIO;
    }

}   

void Antecessor(Nodo **INICIO, Nodo **AUX){
    Nodo *Reserva;

    if ( (*AUX)->direita != NULL){
    Antecessor(INICIO, &(*AUX)->direita);
        // apos ter recebido o nodo a esquerda do que eu vou remover lá do main
        // ele busca o mais a direita desse nodo, até que o próximo dele seja igual a NULL
    return;
    }

    // assim que achar esse valor, ele copia o dado do valor para a posição que vai ser removida
    // ou seja, pega o maior valor anterior do que o qual eu quero remover 
    (*INICIO)->dado.valor = (*AUX)->dado.valor;
    // reserva vai receber a posição desse dado que foi buscado, no caso o mais a direita
    Reserva = *AUX;
    // passo para o prox
    *AUX = (*AUX)->esquerda;
    // removo o nodo
    free(Reserva);
}

void LiberaArvore(Nodo **INICIO){

    // usando o mesmo método de printar em PREordem, porém agora para liberar todo o espaço
    if( (*INICIO) != NULL){

        if( &( (*INICIO)->esquerda)  != NULL )
        LiberaArvore( &( (*INICIO)->esquerda)  );

        if( &( (*INICIO)->direita)  != NULL )
        LiberaArvore( &( (*INICIO)->direita) );

    free(*INICIO);
    }
}