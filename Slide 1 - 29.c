#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menu(void);
char *adicionar(char *p, int *i);
char *deletar(char *p, int *i);
void listar(char *p);

int main(){
  int escolha=0, total_simbolos=0;
  char *lista;

  lista = (char*) malloc(sizeof(char));

  if(lista == NULL){
    printf("Nao foi possivel fazer o malloc");
    exit(0);
  }


  for (;;) {
    escolha = menu();

    switch(escolha){
      case 1:

        lista = adicionar(lista, &total_simbolos);

      break;

      case 2:
   
        lista =  deletar(lista, &total_simbolos);

      break;

      case 3:

        listar(lista);

      break;

      case 4:
       
        free(lista);
        
      break;

      default:
        printf("opcao invalida!\n");
      break;
    }

    //para sair do for infinito
    if(escolha == 4){
      break;
    }

  } 

  return 0;
}

int menu(void){
  int c=0;
  printf("1-Adicionar nome\n");
  printf("2-Remover nome\n");
  printf("3-Listar\n");
  printf("4-Sair\n");
  scanf("%d",&c);
  return c;
}


char *adicionar(char *p,int *i){
  char c;

  printf("Digite um nome:");
  c = getchar();

  while ((c=getchar( )) != '\n'){
    p[*i] = c;

    (*i) ++;

    p = (char*) realloc(p, (1 + (*i) )*sizeof(char) );

  } 

  p[*i] = '\0';

  return  (char *) p;
}

char *deletar(char *p, int *i){
  int n=0, tamanho=0;
  char c, *busca, *ini;

  // aloca o vetor auxiliar que vai armazenar o nome a ser deletado
  busca = (char*) malloc(sizeof(char));

  if(busca == NULL){
    printf("Nao foi possivel fazer o malloc");
    exit(0);
  }
     
  getchar();
  printf("Digite um nome para excluir:");

  while ((c=getchar( )) != '\n'){
    busca[n] = c;

    n++;

    busca = (char*) realloc(busca, (1+n)*sizeof(char) );
  }

  busca[n] = '\0';

  // tamanho da palavra para deletar
  tamanho = strlen(busca);

  // ponteiro que pega o inicio da primeira ocorrencia dos nomes iguais
  ini = strstr(p,busca);

  // conforme forem iguais ele vai apagar o nome desejado no ponteiro
  if (ini = strstr(p, busca)) {
    *ini = '\0';
  // copia para o vetor principal
    strcat(p, ini +tamanho);
  } else {
    printf("\nNome nao encontrado!\n\n");
    free(busca);
    return (char *) p;
  }

  // remove do tamanho total de simbolos o tamanho da palavra que foi removida (buscada)
  (*i) =  (*i)  - tamanho;

  // da o realloc para esse valor menor
  p = (char*) realloc(p, ( (*i) + 1)*sizeof(char) );

  free(busca);

  return (char *) p;
}


void listar(char *p){
  int i=0;
  int tam = 0;

  tam = strlen(p);
  printf("Lista:\n");
  
  for(i=0; i< tam; i++){
    printf("%c",  p[i]);
  }

  printf("\n");
}