
#include <stdio.h>

// print out all the combination of n elements from 1-10 use recursion
// for example for n = 2 print (1,2), (1,3), (1,4), (1,5), (1,6), (1,7), (1,8), (1,9), (1,10) etc
void printCombination(int n, int arr[], int index) {
    for (int i = 1 ; i < 11; i++) {
        arr[index] = i;
        system("clear");
        if (n == index){
            printf("( ");
            for (int j = 0; j < n; j++) {
                printf("%d ", arr[j]);
            }
            printf(")\n");
            return;
        }
        printCombination(n, arr, index+1);
    }
}

void main(int argc, char *argv[]){
    int n = 4;
    int arr[n];
    printCombination(n, arr, 0);
}