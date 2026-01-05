#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int arr[1000];
    int sample[100];
    int i, j, temp;
    
    for (i = 0; i < 1000; i++) {
        arr[i] = i + 1;
    }
    srand(time(NULL));
    for (i = 999; i > 0; i--) {
        j = rand() % (i + 1);
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    for (i = 0; i < 100; i++) {
        sample[i] = arr[i];
    }
    printf("Array :\n");
    for (i = 0; i < 100; i++) {
        printf("%d ", arr[i]);
        if ((i + 1) % 10 == 0) printf("\n");
    }
    int maxDiff = 0, iIndex = 0, jIndex = 0;
    int loopCount1 = 0;
    for (int i = 0; i < 100 - 1; i++) {
        for (int j = i + 1; j < 100; j++) {
            int diff = abs(arr[i] - arr[j]);
            loopCount1++;
            if (diff > maxDiff) {
                maxDiff = diff;
                iIndex = i;
                jIndex = j;
            }
        }
    }
    printf("\nMin Value = %d ,in index %d\n", arr[iIndex], iIndex);
    printf("Max Value = %d ,in index %d\n", arr[jIndex], jIndex);
    printf("Max Difference = %d\n", abs(arr[jIndex] - arr[iIndex]));
    printf("Total Loop = %d\n", loopCount1);

    return 0;
}
