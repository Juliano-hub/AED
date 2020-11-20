#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Dados{
    int valor;
}Dados;

typedef struct Nodo{
    Dados dado;
    struct Nodo *esquerda;
    struct Nodo *direita;
}Nodo;

Nodo *CriaNodo(int Valor);
void adicionar(Nodo **INICIO, Nodo *AUX);
void printarPreordem(Nodo **INICIO, int contadorEspaco);
void LiberaArvore(Nodo **INICIO);
//-----
int FB (Nodo **INICIO);
int Altura(Nodo **INICIO);
void RSE(Nodo **INICIO);
void RSD(Nodo **INICIO);
int BalancaEsquerda(Nodo **INICIO);
int BalancaDireita(Nodo **INICIO);
int Balanceamento(Nodo **INICIO);
void Remover(Nodo **INICIO, int AUX);
void Antecessor(Nodo **INICIO, Nodo **AUX);
//-----
void add_caso1a();
void add_caso2a();
void add_caso3a();
void add_caso1b();
void add_caso2b();
void add_caso3b();
void remove_caso1();

int main(){

    add_caso1a();
    add_caso2a();
    add_caso3a();
    add_caso1b();
    add_caso2b();
    add_caso3b();
    remove_caso1();

    return 0;
}

Nodo *CriaNodo(int Valor){
    Nodo *AUX;
    int num;

    AUX = (Nodo*) malloc(sizeof(Nodo));

    if(AUX == NULL){
        printf("\nNao foi possivel fazer o malloc!\n");
    }

    AUX->dado.valor = Valor;

    AUX->esquerda = NULL;
    AUX->direita = NULL;

    return (Nodo*) AUX;
}

void adicionar(Nodo **INICIO, Nodo *AUX){

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
    int fb = FB( &(*INICIO) );

    if ( fb > 1)
        return BalancaEsquerda( &(*INICIO) );
    else if (fb < -1 )
        return BalancaDireita( &(*INICIO) );
    else
        return 0;
    
}

//--------- CASOS --------------

void add_caso1a(){
        printf("\n--Caso 1a\n");
    Nodo *INICIO, *AUX;
        INICIO = NULL;

    AUX = CriaNodo(20);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(4);
    adicionar(&INICIO, AUX);

    printarPreordem(&INICIO, 0);
    printf("\nDepois de adicionar o 15:\n");

    AUX = CriaNodo(15);
    adicionar(&INICIO, AUX);

    printarPreordem(&INICIO, 0);
    LiberaArvore(&INICIO);
}

void add_caso2a(){
        printf("\n--Caso 2a\n");
    Nodo *INICIO, *AUX;
        INICIO = NULL;
    AUX = CriaNodo(20);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(4);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(3);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(9);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(26);
    adicionar(&INICIO, AUX);

    printarPreordem(&INICIO, 0);
    printf("\nDepois de adicionar o 15:\n");

    AUX = CriaNodo(15);
    adicionar(&INICIO, AUX);

    printarPreordem(&INICIO, 0);
    LiberaArvore(&INICIO);
}
void add_caso3a(){
        printf("\n--Caso 3a\n");
    Nodo *INICIO, *AUX;
        INICIO = NULL;
    AUX = CriaNodo(20);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(4);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(3);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(9);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(2);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(7);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(26);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(11);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(21);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(30);
    adicionar(&INICIO, AUX);

    printarPreordem(&INICIO, 0);
    printf("\nDepois de adicionar o 15:\n");

    AUX = CriaNodo(15);
    adicionar(&INICIO, AUX);

    printarPreordem(&INICIO, 0);
    LiberaArvore(&INICIO);
}

void add_caso1b(){
        printf("\n--Caso 1b\n");
    Nodo *INICIO, *AUX;
        INICIO = NULL;
    AUX = CriaNodo(20);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(4);
    adicionar(&INICIO, AUX);

    printarPreordem(&INICIO, 0);
    printf("\nDepois de adicionar o 8:\n");

    AUX = CriaNodo(8);
    adicionar(&INICIO, AUX);

    printarPreordem(&INICIO, 0);
    LiberaArvore(&INICIO);
}

void add_caso2b(){
        printf("\n--Caso 2b\n");
    Nodo *INICIO, *AUX;
        INICIO = NULL;
    AUX = CriaNodo(20);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(4);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(3);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(9);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(26);
    adicionar(&INICIO, AUX);

    printarPreordem(&INICIO, 0);
    printf("\nDepois de adicionar o 8:\n");

    AUX = CriaNodo(8);
    adicionar(&INICIO, AUX);

    printarPreordem(&INICIO, 0);
    LiberaArvore(&INICIO);
}

void add_caso3b(){
        printf("\n--Caso 3b\n");
    Nodo *INICIO, *AUX;
        INICIO = NULL;
    AUX = CriaNodo(20);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(4);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(3);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(9);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(2);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(7);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(11);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(26);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(21);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(30);
    adicionar(&INICIO, AUX);

    printarPreordem(&INICIO, 0);
    printf("\nDepois de adicionar o 8:\n");

    AUX = CriaNodo(8);
    adicionar(&INICIO, AUX);

    printarPreordem(&INICIO, 0);
    LiberaArvore(&INICIO);
}
void remove_caso1(){
        printf("\n-- remove Caso 1\n");
    Nodo *INICIO, *AUX;
        INICIO = NULL;
    AUX = CriaNodo(2);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(1);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(4);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(3);
    adicionar(&INICIO, AUX);
    AUX = CriaNodo(5);
    adicionar(&INICIO, AUX);

    printarPreordem(&INICIO, 0);


    Remover(&INICIO, 1);
    printf("\n-- Depois de remover o 1 - Caso 1\n");

    printarPreordem(&INICIO, 0);
    LiberaArvore(&INICIO);
}

void Remover(Nodo **INICIO, int AUX){
    Nodo *Reserva;

    if( (*INICIO) != NULL){

        if( (*INICIO)->dado.valor > AUX){
            // se o valor digitado for menor que o atual
            Remover( &( (*INICIO)->esquerda), AUX );
            // ele vai para esquerda

            // return para quando for desempilhar
            return;
        }

        if( (*INICIO)->dado.valor < AUX){
            // se o valor digitado for maior que o atual
            Remover( &( (*INICIO)->direita), AUX );
            // ele vai para direita
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