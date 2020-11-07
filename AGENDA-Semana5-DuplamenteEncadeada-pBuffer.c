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
    struct Nodo *pAnt;
}Nodo;

typedef struct inicio{
    Nodo *pLast;
    Nodo *pIni;
}inicio;

# define opcao sizeof(int)*1
# define opcao_AUX sizeof(int)*2 
# define ler_string_remover (sizeof(int)*2) + (sizeof(char)*20) 
# define dados_aux ( (sizeof(int)*2) + (sizeof(char)*20) )  + sizeof(dados) 
//# define INICIO_AGENDA ( ( (sizeof(int)*2) + (sizeof(char)*20) ) + sizeof(dados) ) + sizeof(inicio) 

Nodo *criaNodo();
inicio* criaLista();
int *menu(void *p);
int vazio(inicio *p);
void adicionar(inicio *p, Nodo *AUX);
void *buscar(inicio *p, inicio *INICIO);
void ordernar_nome(inicio *INICIO, inicio *p);
void ordernar_telefone(inicio *INICIO, inicio *p);
void remover(inicio *p, Nodo *AUX);
void printar(inicio *p);
void freeAgenda(inicio *p, inicio* INICIO);

int main(){
    void *pbuffer;
    Nodo *AUX;
    inicio *INICIO;
    int *escolha;
    int *escolha_AUX;

    pbuffer = (void*) malloc(sizeof(dados_aux + sizeof(inicio) ) );

    if(pbuffer == NULL){
        printf("\nNao foi possivel fazer o malloc!\n");
        exit(0);
    }
    escolha = (int *)(&pbuffer + opcao);
    escolha_AUX = (int *)(&pbuffer + opcao_AUX);
    
    
    INICIO = (inicio *) ( &pbuffer + dados_aux );
    INICIO->pIni = NULL;
    INICIO->pLast = NULL;
    for(;;){

        escolha = menu(pbuffer);

        switch( *escolha ){
            case 1:
                AUX = criaNodo();

                adicionar(INICIO, AUX);
            break;

            case 2:
                AUX = buscar(pbuffer, INICIO);
                if(AUX != NULL){
                    printf("\n-----Dado encontrado:");
                    printf("\nNome:%s", AUX->dado.nome);
                    printf("\nTelefone:%d\n", AUX->dado.telefone);
                }
            break;

            case 3:
                if(vazio(INICIO) == 1){
                    break;
                }

                *escolha_AUX = -1;

                while(*escolha_AUX < 1 || *escolha_AUX > 2){
                    printf("-----Ordernar por:\n");
                    printf("1-Nome\n");
                    printf("2-Telefone\n");
                    scanf("%d", escolha_AUX);
                }

                if(*escolha_AUX == 2){
                    ordernar_telefone(pbuffer, INICIO);
                }
                if(*escolha_AUX == 1){
                    ordernar_nome(pbuffer, INICIO);
                }
            break;

            case 4:
                AUX = buscar(pbuffer, INICIO);

                if(AUX != NULL){
                    remover(INICIO, AUX);
                }
            break;

            case 5:
                printar(INICIO);
            break;

            case 6:

            break;

            default:
                printf("\nOp nao encontrada!\n");
            break;
        }

    if( *escolha   == 6){
        freeAgenda(pbuffer, INICIO);
        break;
    }

    }

    return 0;
}

int vazio(inicio *p){

    if(p->pIni == NULL){
        printf("-----Lista Vazia!\n");
        return 1;
    }else{
        return 0;
    }

}

inicio* criaLista(){
    inicio *AUX;
    AUX = (inicio*) malloc(sizeof(inicio));

    if(AUX == NULL){
        printf("\nNao foi possivel fazer o malloc!\n");
    }
    
    AUX->pIni = NULL;
    AUX->pLast = NULL;

    return (inicio*) AUX;
}

Nodo* criaNodo(){
    Nodo *AUX;

    AUX = (Nodo*) malloc( sizeof(Nodo) );

    if(AUX == NULL){
        printf("\nNao foi possivel fazer o malloc!\n");
        exit(0);
    }

    printf("Digite um nome:");
    scanf("%20s", &AUX->dado.nome);
    printf("Digite uma telefone:");
    scanf("%d", &AUX->dado.telefone);

    AUX->pProx = NULL;
    AUX->pAnt = NULL;
    return (Nodo*) AUX;
}

int *menu(void *p){
    int *escolha;
    printf("1-Adicionar\n");
    printf("2-Buscar\n");
    printf("3-Ordernar\n");
    printf("4-Apagar\n");
    printf("5-Listar\n");
    printf("6-Sair\n");

    escolha =  (int *)(p + opcao);
    scanf("%d", escolha);

    return (int*) escolha;
}

void adicionar(inicio *p, Nodo *AUX){
    Nodo *inicio_AUX;
    Nodo *anterior_AUX;

    // adiciona no inicio caso for vazio a primeira vez
    if(p->pIni == NULL){
        p->pIni = AUX;

        p->pIni->pAnt = NULL;
        p->pIni->pProx = NULL;

        p->pLast = p->pIni;
        
        return;
    }

    // seta o ponteiro final como inicial
    p->pLast = p->pIni;

    inicio_AUX = p->pIni;
    anterior_AUX = inicio_AUX;

    // inicio_AUX aponta para o primeiro elemento

    // enquanto o próximo conteudo n for NULL para ADD no fim, ele passa para o próximo conteúdo
    while(inicio_AUX->pProx != NULL){
        inicio_AUX = inicio_AUX->pProx;
        inicio_AUX->pAnt = anterior_AUX;

        anterior_AUX = anterior_AUX->pProx;
        p->pLast = p->pLast->pProx;
    }

    // ADD o conteudo do nodo AUX no próximo elemento

    inicio_AUX->pProx = AUX;
    inicio_AUX = inicio_AUX->pProx;
    inicio_AUX->pAnt = anterior_AUX;

    p->pLast = p->pLast->pProx;

    return;
}

// TROQUEI O P QUERA O PBUFFER COM O INICIO, PARA N PRECISAR MUDAR OS OUTROS P POR INICIO NA FUNCAO, ASSIM O PBUFFER QUE É O INICIO FICA COM O 
// ponteiro NO INICIO DAS ALOCAÇÕES

void *buscar(inicio *INICIO, inicio *p){
    Nodo *Vazio;
    Vazio = NULL;

    if (vazio(p) == 1 ){
        return (Nodo*) Vazio;
    }
    
    Nodo *inicio_AUX;
    char *c;

    c = (char *)(INICIO + ( opcao + 1*(sizeof(char)) ) );

    inicio_AUX = p->pIni;
    // inicio_AUX aponta para o primeiro elemento

    printf("\nDigite um nome:");
    scanf("%20s", c);

    while(strcmp(c, inicio_AUX->dado.nome) != 0){

        inicio_AUX = inicio_AUX->pProx;

        if(inicio_AUX == NULL){
            printf("-----Nome nao encontrado!\n");
        return (Nodo*) Vazio;
        }

    }

    return (Nodo*) inicio_AUX;
}

void ordernar_nome(inicio *INICIO, inicio *p){

     if (vazio(p) == 1 ){
        return;
    }

    Nodo *inicio_AUX;
    Nodo *AUX;
    dados *AUX_AUX;

    AUX_AUX = (dados *)(INICIO + dados_aux );

    for(inicio_AUX = p->pIni->pProx ; inicio_AUX != NULL ; inicio_AUX = inicio_AUX->pProx){
       for(AUX = p->pIni ; AUX != p->pLast ; AUX = AUX->pProx ){
           if( strcmp(AUX->dado.nome, AUX->pProx->dado.nome) > 0 ){
               *AUX_AUX = AUX->dado;
               AUX->dado = AUX->pProx->dado;
               AUX->pProx->dado = *AUX_AUX;
           }
       }

    }

    printar(p);

}

// TROQUEI O P QUERA O PBUFFER COM O INICIO, PARA N PRECISAR MUDAR OS OUTROS P POR INICIO NA FUNCAO, ASSIM O PBUFFER QUE É O INICIO FICA COM O 
// ponteiro NO INICIO DAS ALOCAÇÕES
void ordernar_telefone(inicio *INICIO, inicio *p){

    if (vazio(p) == 1 ){
        return;
    }

    Nodo *inicio_AUX;
    Nodo *AUX;
    dados *AUX_AUX;

    AUX_AUX = (dados *)(INICIO + dados_aux );

    for(inicio_AUX = p->pIni->pProx ; inicio_AUX != NULL ; inicio_AUX = inicio_AUX->pProx){
       for(AUX = p->pIni ; AUX != p->pLast ; AUX = AUX->pProx ){
           if(AUX->dado.telefone > AUX->pProx->dado.telefone){
               *AUX_AUX  =  AUX->dado;
               AUX->dado = AUX->pProx->dado;
               AUX->pProx->dado = *AUX_AUX;
           }
       }

    }

    printar(p);
}

void remover(inicio *p, Nodo *AUX){
    Nodo *Remover;
    Nodo *inicio_AUX;

    // caso for o inicio
    if(AUX->pAnt == NULL && AUX->pProx == NULL){

        p->pIni->pProx = NULL;
        p->pIni->pAnt = NULL;
        p->pLast = NULL;
        p->pIni = NULL;
        free(AUX);
        return;
    }

    // caso for no inicio, mas tiver algo depois
    if(AUX->pAnt == NULL && AUX->pProx != NULL){
        p->pIni = p->pIni->pProx;
        p->pIni->pAnt = NULL;
        AUX->pProx = NULL;
        AUX->pAnt = NULL;
        free(AUX);
        return;
    }

    inicio_AUX = p->pIni;
    
    while(strcmp(inicio_AUX->dado.nome, AUX->dado.nome) != 0){
        inicio_AUX = inicio_AUX->pProx;
    }

    // caso for o final
    if(AUX->pProx == NULL){

        // seta o ponteiro do último sendo o penúltimo
        p->pLast = p->pLast->pAnt;

        Remover = AUX->pAnt;
        Remover->pProx = NULL;

        free(AUX);

        return;
    }

    // caso for o meio
    // seta o ponteiro do último sendo o penúltimo


    //p->pLast = p->pLast->pAnt;
    Remover = AUX->pAnt;
    Remover->pProx = AUX->pProx;
 
    Remover->pProx->pAnt = Remover;


    free(AUX);
    return;
}


void printar(inicio *p){

    if (vazio(p) == 1 ){
        return;
    }

    Nodo *inicio_AUX;

    inicio_AUX = p->pIni;
    // inicio_AUX aponta para o primeiro elemento

    printf("\n-----Lista\n");

    // enquanto o conteúdo não for NULL
    while(inicio_AUX != p->pLast){
        printf("nome: %s\n", inicio_AUX->dado.nome);
        printf("telefone: %d\n", inicio_AUX->dado.telefone);

        // ele passa para o próximo conteúdo
        inicio_AUX = inicio_AUX->pProx;
    }

    if(inicio_AUX != NULL){
        printf("nome: %s\n", inicio_AUX->dado.nome);
        printf("telefone: %d\n", inicio_AUX->dado.telefone);
    }
}


void freeAgenda(inicio *p, inicio* INICIO){
	inicio *aux;

    aux = INICIO;

    // se não tiver alocado nada
	if(aux->pIni == NULL  ){
        free(p);
        return;
    }
    
    // se tiver 1 Nodo só alocado
	if(aux->pIni->pProx == NULL){		
		free(aux->pIni);
        free(p);
		return;
	}

    // se tiver mais de um Nodo alocado
    aux->pIni = aux->pIni->pProx;

	for(aux ; aux->pIni != p->pLast; aux->pIni = aux->pIni->pProx){
        free(aux->pIni->pAnt);
        if(aux->pIni->pProx == NULL){
            break;
        }
    }
	free(aux->pIni);
    free(p);
    
}


