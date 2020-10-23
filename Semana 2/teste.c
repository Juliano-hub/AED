#include <stdio.h>

int main(){
int t,j=1, *p,*g;
t=5;
p=&t;
j=3;
g=&j;

*p = (*g + t) * 2;
*g = 4;

g = p;

for(j = 0 ; j < 2 ; j++){
    *g = t*j + 1;
}

*p = t + j + *g;

    return 0;
}