#include "Lab4.h"

void main(int argc, char* argv[]){
    int *values;
    values = malloc(5 * sizeof(int));
    for (int i = 0; i < 5; i++){
        values[i] = i;
    }
    int* max = maximum_p(values, 5);
    printf("The maximum value is %d\n", *max);
}
