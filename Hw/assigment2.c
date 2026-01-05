#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
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
    printf("Random numbers:\n");
    for (i = 0; i < 100; i++) {
        printf("%d ", sample[i]);
        if ((i + 1) % 10 == 0) printf("\n");
    }
    int min = sample[0];
    int max = sample[0];
    int minIndex = 0;
    int maxIndex = 0;
    int loopCount = 0;
    for (i = 1; i < 100; i++) {
        loopCount++;
        if (sample[i] < min) {
            min = sample[i];
            minIndex = i;
        }
        if (sample[i] > max) {
            max = sample[i];
            maxIndex = i;
        }
    }
    int diff = abs(max - min);
    printf("\nMin Value = %d ,in index %d\n", min, minIndex);
    printf("Max Value = %d ,in index %d\n", max, maxIndex);
    printf("Max Difference = %d\n", diff);
    printf("Total loop count = %d\n", loopCount);

    return 0;
}
