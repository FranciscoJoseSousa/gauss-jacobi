#include <stdio.h>
#include <stdlib.h>



int main(){
    srand(1);
    for(int i = 0;i<11;i++){
        printf("%d ",rand()%1000);
    }
    printf("\n");
    return 0;
}