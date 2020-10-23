#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
char nome[30];
int idade;
int altura;
}pessoa;


int main(){
  pessoa *pessoas;
  char escolha,escolhaAUX, c;
  int i=0,quantidade=0;

  pessoas = (pessoa*) malloc(sizeof(pessoa));

  if(pessoas == NULL){
    printf("Nao foi possivel fazer o malloc");
    exit(0);
  }

  printf("Deseja  adicionar dados?[S/N]");
  scanf("%c", &escolhaAUX);
  c = getchar();

  escolha = escolhaAUX;

  while(escolha == 'S' || escolha == 's'){
    printf("Digite um nome:");

    c = getchar();


    // escreve o nome
    while ( (c != '\n') && (i <30) ){
      pessoas[quantidade].nome[i] = c;
      c= getchar();
      i++;
    }

    pessoas[quantidade].nome[i] = '\0';

    i=0;

    //escreve os outros dados
    printf("Digite uma idade:");
    scanf("%d", &pessoas[quantidade].idade);
    getchar();
    printf("Digite uma altura:");
    scanf("%d", &pessoas[quantidade].altura);
    getchar();


    //se quiser continuar a adicionar
    printf("Deseja continuar adicionando dados?[S/N]");
    scanf("%c", &escolha);
    c = getchar();


    //se sim aloca mais espaço
    if(escolha == 'S' || escolha == 's'){
      quantidade = quantidade + 1;
      pessoas = (pessoa*) realloc(pessoas,(1 + quantidade)*sizeof(pessoa));

    }else{

      //se não sai 
      break;
    }

  }

  //verifica caso a pessoa não queira alocar uma primeira vez
  if(escolhaAUX == 'S' || escolhaAUX == 's'){

    printf("------Lista\n");

    for(i=0;i <= quantidade;i++){
      printf("nome:%s\n", pessoas[i].nome);
      printf("idade:%d\n", pessoas[i].idade);
      printf("altura:%d\n", pessoas[i].altura);
      printf("------\n");
    }

  }

  free(pessoas);
  return 0;
}