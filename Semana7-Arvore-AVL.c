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
int adicionar(Nodo** INICIO,Nodo *x);
int menu();
void printarPreordem(Nodo **INICIO, int contadorEspaco);
Nodo *buscar(Nodo **INICIO, int AUX);
void Remover(Nodo **INICIO, Nodo *AUX);
void Antecessor(Nodo **INICIO, Nodo **AUX);
void LiberaArvore(Nodo **INICIO);
//-----
int FB (Nodo **INICIO);
int Altura(Nodo **INICIO);
void RSE(Nodo **INICIO);
void RSD(Nodo **INICIO);
int BalancaEsquerda(Nodo **INICIO);
int BalancaDireita(Nodo **INICIO);
int Balanceamento(Nodo **INICIO);


int main(){
    Nodo *INICIO, *AUX;
    int escolha, BUSCA, malloc_primeira_vez=1;
    INICIO = NULL;

    do{
        escolha = menu();

        switch(escolha){
            case 1:
                AUX = CriaNodo();
                if(AUX != NULL){
                    adicionar(&INICIO, AUX);
                }

                malloc_primeira_vez=0;
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
                printf("\n");
                printarPreordem(&INICIO, 0);
            break;

            case 5:
            break;

            default:
            printf("\n OP invalida\n");
            break;
        }
    }while(escolha != 5);

    if(malloc_primeira_vez == 0){
        LiberaArvore(&INICIO);
    }

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

int adicionar(Nodo** INICIO,Nodo *x){
    if (*INICIO == NULL){
        *INICIO = x;
        return 1;
    }
    else if ( (*INICIO)->dado.valor > x->dado.valor ){
        if ( adicionar( &( (*INICIO)->esquerda), x) )
        {
            if (Balanceamento(INICIO))
                return 0;
            else
                return 1;
        }
    }
    else if (  (*INICIO)->dado.valor < x->dado.valor  ){
        if ( adicionar(&(*INICIO)->direita, x) )
        {
            if (Balanceamento(INICIO))
                return 0;
            else
                return 1;
        }
        else
        return 0;
    }
    else{
        printf("\nTentou inserir um valor repitido!\n");
        free(x);
        return 0; /* valor jah presente */
    }
}

void Remover(Nodo **INICIO, Nodo *AUX){
    Nodo *Reserva;
    int BALANCEAMENTO;

    if( (*INICIO) != NULL){

        if( (*INICIO)->dado.valor > AUX->dado.valor){
            // se o valor digitado for menor que o atual
            Remover( &( (*INICIO)->esquerda), AUX );
            // ele vai para esquerda

            // return para quando for desempilhar

            BALANCEAMENTO = FB(INICIO);
            if(BALANCEAMENTO != 0){
                if( BALANCEAMENTO == -2 ){
                    RSE( & (*INICIO) );
                }if ( BALANCEAMENTO == 2 ){
                    RSD( & (*INICIO) );
                }
                if( BALANCEAMENTO == 2 && FB(&(*INICIO)->esquerda) == -1){
                    RSD( & (*INICIO) );
                    RSE( & (*INICIO) );
                }
                if( BALANCEAMENTO == -2 && FB(&(*INICIO)->direita) == +1){
                    RSD( & (*INICIO) );
                    RSE( & (*INICIO) );
                }
            }
            return;
        }

        if( (*INICIO)->dado.valor < AUX->dado.valor){
            // se o valor digitado for maior que o atual
            Remover( &( (*INICIO)->direita), AUX );
            // ele vai para direita

            BALANCEAMENTO = FB(INICIO);
            if(BALANCEAMENTO != 0){
                if( BALANCEAMENTO == -2 ){
                    RSD( & (*INICIO) );
                }if ( BALANCEAMENTO == 2 ){
                    RSE( & (*INICIO) );
                }
                if( BALANCEAMENTO == 2 && FB(&(*INICIO)->direita) == -1){
                    RSE( & (*INICIO) );
                    RSD( & (*INICIO) );
                }
                if( BALANCEAMENTO == -2 && FB(&(*INICIO)->esquerda) == +1){
                    RSE( & (*INICIO) );
                    RSD( & (*INICIO) );
                }
            }
            return;
        }

        //-----Achou o dado que vai remover

        // se for folha
        if( (*INICIO)->direita == NULL && (*INICIO)->direita == NULL ){
            Reserva = *INICIO;
            // pega a posição que vai ser deletada
            free(Reserva);

            *INICIO = NULL;
            return;
        }

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

void printarPreordem(Nodo **INICIO, int contadorEspaco){
    if( (*INICIO) != NULL){
                
        for(int i=0 ; i < contadorEspaco ; i++){
            printf(" ");
        }

        printf("%d", (*INICIO)->dado.valor );
        printf("\n");
        
        if( &( (*INICIO)->esquerda)  != NULL )
        printarPreordem( &( (*INICIO)->esquerda) , (contadorEspaco = contadorEspaco + 2) );
        if( &( (*INICIO)->direita)  != NULL )
        printarPreordem( &( (*INICIO)->direita), (contadorEspaco = contadorEspaco) );
    }
    
}

Nodo *buscar(Nodo **INICIO, int AUX){
    Nodo *Reserva = NULL;

    if( (*INICIO) == NULL){
        Reserva = NULL;
        printf("\n Dado nao encontrado!\n");
        return (void *) Reserva;
    }


    if( (*INICIO)->dado.valor > AUX){
        Reserva = buscar( &( (*INICIO)->esquerda), AUX );
        return (Nodo *) Reserva;
    }

    if( (*INICIO)->dado.valor < AUX){
        Reserva = buscar( &( (*INICIO)->direita), AUX );
        return (Nodo *) Reserva;
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

//--------- AVL

int FB (Nodo **INICIO){
    if (*INICIO == NULL){
        return 0;
    }

    return(  Altura( &( (*INICIO)->esquerda) ) - Altura( &( (*INICIO)->direita) ) );
}

int Altura(Nodo **INICIO){
    int iEsq,iDir;
    if ( (*INICIO) == NULL){
        return 0;
    }

    iEsq = Altura( &( (*INICIO)->esquerda) );
    iDir = Altura( &( (*INICIO)->direita) );
    if ( iEsq > iDir )
    return iEsq + 1;
    else
    return iDir + 1;
}

void RSE(Nodo **INICIO){
    Nodo *Aux;
    Aux = (*INICIO)->direita;
    (*INICIO)->direita = Aux->esquerda;
    Aux->esquerda = (*INICIO);
    (*INICIO) = Aux;
}

void RSD(Nodo **INICIO){
    Nodo *Aux;
    Aux = (*INICIO)->esquerda;
    (*INICIO)->esquerda = Aux->direita;
    Aux->direita = (*INICIO);
    (*INICIO) = Aux;
}

int BalancaEsquerda(Nodo **INICIO){
    int fbe;
    fbe =  FB ( &( (*INICIO)->esquerda) );

    if ( fbe > 0 ){
        RSD( &(*INICIO) );
    return 1;
    }

    else if (fbe < 0 ){
        // Rotação Dupla Direita

        RSE( &((*INICIO)->esquerda) );
        RSD( &(*INICIO) ); 
        return 1;
    }

    return 0;
}

int BalancaDireita(Nodo **INICIO){
    int fbd;
    fbd =  FB ( &( (*INICIO)->direita) );

    if ( fbd < 0 ){
        RSE( &(*INICIO) );
    return 1;
    }

    else if (fbd > 0 ){
        // Rotação Dupla esquerda

        RSD( &( (*INICIO)->direita) );
        RSE( &(*INICIO) ); 
        return 1;
    }

    return 0;
}

int Balanceamento(Nodo **INICIO){
    int fb; 
    fb = FB( &(*INICIO) );

    if ( fb > 1){
        return BalancaEsquerda( &(*INICIO) );
    }else if (fb < -1 ){
        return BalancaDireita( &(*INICIO) );
    }else{
        return 0;
    }
}