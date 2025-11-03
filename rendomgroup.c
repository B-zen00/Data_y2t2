#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 103

int main(){
    int arr[N];
    int i, j, temp; 
    for (i = 0; i < N; i++) {
        arr[i] = i + 1;
    }
    srand(time(NULL));
    for (i = (N-1); i > 0; i--) {
        j = rand() % (i + 1);
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    printf("Rendom group : \n");
    int count = 0;
    for (int g = 1; g <= (N/4 +1); g++){
        if(g <10){
            printf("Group 0%d : ",g);
        }else{
        printf("Group %d : ",g);
        }
        if(g == 26){
            printf("%d %d %d\n",arr[count],arr[count+1],arr[count+2]);
            break;
        }
        printf("%d %d %d %d\n",arr[count],arr[count+1],arr[count+2],arr[count+3]);
        count += 4;
    }
    return 0;
}