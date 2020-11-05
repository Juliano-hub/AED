#include <stdio.h>

void insertionsort(int data[], int n);

int main(){
    int data[5] = {5,4,3,2,1};
    int n=5;

    insertionsort(data, n);
    printf("%d %d %d %d %d", data[0], data[1],data[2], data[3], data[4]);

    return 0;
}


void insertionsort(int data[], int n){

    int tmp=0,i=0,j=0;

    for(i=0; j<n; j++){
        i=j-1;
        tmp = data[j];
        while( (i>=0) && (tmp <data[i]) ){
            data[i+1] = data[i];
            i--;
        } // while

        data[i+1] = tmp;
    } // for

} // insertionsort