#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int menu(void);
int** criaMatriz(int m, int n);
void leiaMatriz(int**mat, int m, int n);
int somaMatriz(int**mat, int m, int n);
int* colunaMatriz(int** mat, int m, int n, int ncoluna);
void liberaMatriz(int**mat, int ncoluna);
void imprimeMatriz(int**mat, int m, int n);
void imprimeVetor(int*vet, int n);

int main(){
    int escolha=0,LINHA=0,COLUNA=0,numero_coluna_printar=0;
    int **matriz, *vetor_retorno, SOMA=0, malocado=1;

    for(;;){
        escolha = menu();

        switch(escolha){
            case 1:
                printf("Digite o valor de m(linha):");
                scanf("%d", &LINHA);
                printf("Digite o valor de n(coluna):");
                scanf("%d", &COLUNA);

                matriz = criaMatriz(LINHA,COLUNA);

            if(malocado == 1){
                malocado = 0;
            }

            break;

            case 2:
                leiaMatriz(matriz,LINHA,COLUNA);
            break;

            case 3:
                SOMA = somaMatriz(matriz,LINHA,COLUNA);

                printf("\n-----SOMA total eh: %d\n",SOMA);
                SOMA = 0;

            break;
                
            case 4:
                printf("Digite o numero da coluna para retornar:");
                scanf("%d",&numero_coluna_printar);

                //numero_coluna_printar = numero_coluna_printar-1;
                //if(numero_coluna_printar < 0){
                //numero_coluna_printar = 0;
                //}

                if((numero_coluna_printar < COLUNA) && (numero_coluna_printar >= 0)){
                    vetor_retorno = colunaMatriz(matriz,LINHA,COLUNA,numero_coluna_printar);

                    imprimeVetor(vetor_retorno,LINHA);

                    free(vetor_retorno);

                }else{
                    printf("\nnumero de coluna invalida!\n");
                    break;
                }
            break;

            case 5:
                imprimeMatriz(matriz,LINHA,COLUNA);
            break;

            case 6:

                // malocado == 0 somente caso fez o malloc no case 1
                if(malocado == 0){
                liberaMatriz(matriz,LINHA);
                }

            break;

            default:
                printf("\nopcao invalida!\n");
            break;
        }
        //para sair do for infinito
        if(escolha == 6){
        break;
        }
    }

    return 0;
}


int menu(){
    int A=0;
    printf("1) Criar e redimencionar uma matriz m(linha) x n(coluna)\n");
    printf("2) Realizar a leitura dos elementos da matriz\n");
    printf("3) Fornecer a soma dos elementos da matriz\n");
    printf("4) Retornar os elementos de uma determinada coluna da matriz\n");
    printf("5) Imprimir a matriz\n");
    printf("6) Sair do programa\n");
    scanf("%d",&A);
    getchar();
return A;
}

int** criaMatriz(int m, int n){
    int **A,i=0;

    //aloca as linhas
    A = (int**) malloc((m)*sizeof(int*));

    if(A == NULL){
        printf("\nNao foi possivel fazer o malloc\n");
        exit(0);
    }

    //aloca as colunas
    for(i=0;i < m;i++){
        A[i] = (int *)malloc((n)*sizeof(int));
    }

    return (int**) A;
}

void leiaMatriz(int**mat, int m, int n){
    int linha=0,coluna=0;

    for(linha=0;linha < m;linha++){
        for(coluna=0;coluna < n;coluna++){
            printf("Digite um valor:");
            scanf("%d",&mat[linha][coluna]);
        }
    }

}


int somaMatriz(int**mat, int m, int n){
    int linha=0,coluna=0,somaTOTAL=0,somaLINHA=0;

    for(linha=0;linha < m;linha++){
        for(coluna=0;coluna < n;coluna++){
            somaLINHA = somaLINHA + mat[linha][coluna];
        }
        somaTOTAL = somaTOTAL + somaLINHA;
        somaLINHA=0;
    }

    //printf("-----A soma total eh: %d\n", somaTOTAL);

    return somaTOTAL;
}

int* colunaMatriz(int** mat, int m, int n, int ncoluna){
    int *aux,linha=0,coluna=0,contadorAUX=0;

    aux = (int*) malloc(sizeof(int)*m);

    for(linha=0;linha < m;linha++){
        for(coluna=0;coluna < n;coluna++){

            if(coluna == ncoluna){
                aux[contadorAUX] = mat[linha][coluna];

                contadorAUX++;
            }

        }
    }

    return (int*) aux;
}

void imprimeVetor(int*vet, int n){
    int i=0;

    printf("-----Valores da coluna:\n");

    for(i=0;i < n;i++){
        printf("%d \n", vet[i]);
    }
    printf("\n");
}

void imprimeMatriz(int**mat, int m, int n){
    int linha=0,coluna=0;

    printf("-----Matriz:\n");

    for(linha=0;linha < m;linha++){
        for(coluna=0;coluna < n;coluna++){
         printf("%d ", mat[linha][coluna]);
        }
    printf("\n");
    }
    printf("\n");
}

void liberaMatriz(int**mat, int ncoluna){
    int i=0;
    for(i=0;i < (ncoluna);i++){
        free(mat[i]);
    }
    free(mat);
}