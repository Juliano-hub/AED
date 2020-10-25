#include <stdio.h>
#include <stdlib.h>

char *marcador(char *aux,char *linha, int *contador);
void printar(char *aux, int *contador);
char *ler(char *linha, int *contador);

int main(){
  char *linha, *aux, c;
  int i=0, contador=0;

  linha = malloc(sizeof(char)*81);

  if(linha == NULL){
    printf("Nao foi possivel fazer o malloc");
    exit(0);
  }

  aux = malloc(sizeof(char)*81);

  if(aux == NULL){
    printf("Nao foi possivel fazer o malloc");
    exit(0);
  }

  linha = ler(linha,&contador);

  aux = realloc(aux,sizeof(char)*(contador+1));

  aux = marcador(aux, linha, &contador);

  printar(aux,&contador);

  free(linha);
  free(aux);
  return 0;
}


char *ler(char *linha, int *contador){
  char c;
  int contador_simbolos=0;

  printf("Digite a string:");

  while( ((c=getchar()) != '\n')  && (contador_simbolos < 80) ){
    *(linha + (*contador) ) = c;
    (*contador)++;

    linha = realloc(linha,sizeof(char)*( (*contador) + 1 ));

    contador_simbolos++;
  }

  *(linha + (*contador) ) = '\0';

  return (char*) linha;
}


char *marcador(char *aux,char *linha, int *contador){
  int i=0;

  for(i=0; i< (*contador) ;i++){
    *(aux+i) = *(linha+i);
    if( *(linha+i) == ' '){

        *(aux+i) = '*';
    }

  }

  return (char*) aux;
}


void printar(char *aux, int *contador){
int i=0;

 for(i=0; i< (*contador) ;i++){
    if(*(aux+i) != '*'){
      printf("%c", *(aux+i) );

        }else{
          printf("\n");
        }
  }

}