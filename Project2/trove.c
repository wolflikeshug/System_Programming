#define _POSIX_C_SOURCE 200809L

# include "trove.h"

int main (void)
{
    printf("%li\n", strlen('\0'));
    return 0;
}