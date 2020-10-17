#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct cadastro
{
    char nome[20];
    int telefone;
    int id;
} agenda;

int *menu(void *buffer);
void *adicionar(void *buffer);
void listar(void *buffer);
void busca(void *buffer);
void *apaga(void *buffer);

#define escolha 0 * sizeof(int)
#define posicao 1 * sizeof(int)
#define contador_realloc 2 * sizeof(int)
#define ID_busca 3 * sizeof(int)
#define contador_i 4 * sizeof(int)
#define contador_dif 5 * sizeof(int)
#define todas_variaveis 6 * sizeof(int)
#define inicio_struct 7 * sizeof(int)

int *contador_de_realloc;
int *contador_da_posisao;

int main()
{
    void *pbuffer;
    int *opcao;

    pbuffer = (void *)malloc(sizeof(inicio_struct));
    if (pbuffer == NULL)
    {
        printf("Nao foi possivel fazer o malloc!");
        exit(0);
    }

    opcao = (int *)(&pbuffer + escolha);
    contador_de_realloc = (int *)(&pbuffer + contador_realloc);
    *contador_de_realloc = 0;

    contador_da_posisao = (int *)(&pbuffer + posicao);
    *contador_da_posisao = 0;

    for (;;)
    {
        opcao = (int *)menu(pbuffer);

        switch (*(int *)pbuffer)
        {
        case 1:

            *contador_de_realloc = *contador_de_realloc + 1;

            pbuffer = adicionar(pbuffer);

            break;

        case 2:
           pbuffer = apaga(pbuffer);


        if(*contador_de_realloc != 0 ){
           *contador_da_posisao = *contador_da_posisao - 1;
        }
            break;

        case 3:
            busca(pbuffer);
            break;

        case 4:
            listar(pbuffer);
            break;

        case 5:

            break;

        default:
            printf("Opcao invalida!");
            break;
        }

        if ((*opcao) == 5)
        {
            // printf("AQQ");
            free(pbuffer);
            break;
        }
    }

    return 0;
}

int *menu(void *buffer)
{
    int *aux;
    printf("1-incluir\n");
    printf("2-apagar\n");
    printf("3-buscar\n");
    printf("4-listar\n");
    printf("5-sair\n");

    aux = (int *)buffer;

    scanf("%d", aux);
    getchar();
    return (int *)aux;
}

void *adicionar(void *buffer)
{
    agenda *i;

    buffer = realloc(buffer, (inicio_struct + sizeof(agenda) * (*contador_de_realloc+1)));

    i = (agenda *)(buffer + (inicio_struct + sizeof(agenda) * (*contador_de_realloc)));

    printf("\nDigite um nome:");
    scanf("%s", i->nome);
    getchar();


    printf("\nDigite um telefone:");
    scanf("%d", &i->telefone);


    i->id = *contador_da_posisao;
    (*contador_da_posisao) = (*contador_da_posisao) + 1;


    return (void *)buffer;
}

void listar(void *buffer)
{
    if(*contador_de_realloc<=0){
    printf("\nlista vazia\n");
    return;
    }

    int *i;

    agenda *AUX;

    //*i= sizeof(agenda);

    i = (int *)(&buffer + contador_i);
    *i = 0;

    AUX = (agenda *)(buffer + (inicio_struct + sizeof(agenda)));

    //printf("valor de I:%d",*i);


    for (*i = 0; *i < *contador_de_realloc; (*i)++)
    {

        AUX = (agenda *)(buffer + (inicio_struct + sizeof(agenda)* (*i+1) ));
        printf("\nID:%d", (int )(AUX)->id);
        printf("\nnome:%s",  (AUX)->nome);
        printf("\ntelefone:%d\n", (int )(AUX)->telefone);
    }
}

void busca(void *buffer)
{
        if(*contador_de_realloc<=0){
    printf("\nlista vazia\n");
    return;
    }

    int *id_busca;
    agenda *AUX;
    int *i;

    i = (int *)(&buffer + contador_i);
    AUX = (agenda *)(buffer + (inicio_struct + sizeof(agenda)));

        (*i) = 0;

    id_busca = (int *)(&buffer + contador_dif);

    printf("Digite um ID para buscar:");
    scanf("%d", id_busca);

    if (( (*id_busca >= *contador_da_posisao) || *id_busca < 0  ))
    {
        printf("\nID nao encontrado\n");
        (*i) = 0;
        return;
    }



    while (*id_busca != (AUX + *i)->id)
    {

        (*i)++;
    }

    printf("\nID:%d", (AUX + *i)->id);
    printf("\nnome:%s", (AUX + *i)->nome);
    printf("\ntelefone:%d\n", (AUX + *i)->telefone);

    (*i) = 0;
}


void *apaga(void *buffer)
{

    if(*contador_de_realloc<=0){
    printf("\nlista vazia\n");
        return (void*)buffer;;
    }

int *id_busca;
int *contador;
agenda *AUX;
agenda *proximo;


AUX = (agenda *)(buffer + (inicio_struct + sizeof(agenda)));

contador = (int *)(&buffer + contador_dif);
id_busca = (int *)(buffer + ID_busca);


*contador=0;

printf("Digite o ID para remover:");
scanf("%d",id_busca);

    if ((*id_busca > (*contador_de_realloc) - 1 ) || *id_busca < 0)
    {                   
                        //anula  o de cima
                       *contador_da_posisao = *contador_da_posisao + 1;
        printf("\nID nao encontrado\n");
        (*contador) = 0;
            return (void*)buffer;;
    }


        while (*id_busca != (AUX + *contador)->id)
    {

        (*contador)++;
    }

    if((*contador_de_realloc) == 1){
        (*contador_de_realloc)= 0;
          *contador_da_posisao = *contador_da_posisao - 1;
        buffer = realloc(buffer, (inicio_struct + sizeof(agenda) * (*contador_de_realloc) ));
        return (void*) buffer;
    }


while ( ((*contador)  < (*contador_de_realloc) -1)){

    
   proximo = (agenda *)(buffer + (inicio_struct + sizeof(agenda)*(*contador+2)));
AUX = (agenda *)(buffer + (inicio_struct + sizeof(agenda)*(*contador+1)));

    *AUX = *proximo;

AUX->id = AUX->id - 1;

//(proximo+ *contador)->id  =   ( (proximo + *contador)->id )-1;


        (*contador)++;
}


 //*contador_da_posisao =  *contador_da_posisao - 1;

if(*contador_de_realloc != 1)
*contador_de_realloc = *contador_de_realloc -1;


*(contador) = 0;
buffer = realloc(buffer, (inicio_struct + sizeof(agenda) * ( (*contador_de_realloc) + 1)));
    return (void*)buffer;
}


