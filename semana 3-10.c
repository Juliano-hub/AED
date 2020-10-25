#include <stdio.h>

int F1( unsigned int n);

int main(){
unsigned int A;

printf("Digite o valor:");
scanf("%u",&A);

A = F1(A);

printf("%u",A);

    return 0;
}



int F1 ( unsigned int n){
int i=0,j=0,k=0,aux=0;

if(n == 0){
return i;
}


for(k=0;k<n;k++){
    for(j=0;j<n;j++){
      aux=aux+1;
    }
    i=j+i;
    j=0;
    aux=0;
}


return i;
}