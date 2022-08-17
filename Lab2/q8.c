#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Ackermann function
int ack(int m, int n) {
    if (m == 0) {
        return n + 1;
    }
    else if (m > 0 && n == 0) {
        return ack(m - 1, 1);
    }
    else {
        return ack(m - 1, ack(m, n - 1));
    }
}

int main() {
    int m, n;
    m = 9;
    n = 8;
    printf("%d\n", ack(m, n));
    return 0;
}