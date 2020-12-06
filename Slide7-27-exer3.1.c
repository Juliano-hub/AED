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
int adicionar(Nodo **INICIO, Nodo *x);
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
int EhArvoreArvl(Nodo **INICIO);

int main(){
    Nodo *INICIO, *AUX;
    int Total_nodos, i, resultado;
    INICIO = NULL;

    // altera os valores sempre que compilar novamente, para que não seja sempre os mesmo aleatórios 
    srand(time(NULL));


    do{
        printf("Digite uma quantidade de nodos para serem criados:");
        scanf("%d", &Total_nodos);
    }while(Total_nodos < 0);


    for(i=0 ; i< Total_nodos ; i++){
                        // passa um numero aleatório entre 250 e 0 para preencher
        AUX = CriaNodo( rand()% 250 - 0 );
        if(AUX != NULL){
            adicionar(&INICIO, AUX);
        }
    }

    printf("\nImprimindo em PREordem:\n");
    printarPreordem(&INICIO, 0);

    resultado = EhArvoreArvl(&INICIO);

    if(resultado){
        printf("\nEsta certo!\n");
    }else{
        printf("\nEsta errado!\n");
    }


    LiberaArvore(&INICIO);
    return 0;
}

Nodo *CriaNodo(int Valor){
    Nodo *AUX;

    AUX = (Nodo*) malloc(sizeof(Nodo));

    if(AUX == NULL){
        printf("\nNao foi possivel fazer o malloc!\n");
        return (Nodo*) NULL;
    }

    AUX->dado.valor = Valor;

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

int EhArvoreArvl(Nodo **INICIO){
    int fb;

    if (*INICIO == NULL)
        return 1;

    if ( !EhArvoreArvl( &((*INICIO)->esquerda) ) )
        return 0;

    if ( !EhArvoreArvl( &((*INICIO)->direita) ) )
    return 0;
                    
    fb = FB (INICIO);
    if ( ( fb > 1 ) || ( fb < -1) )
        return 0;
    else
        return 1;
}