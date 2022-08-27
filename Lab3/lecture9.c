#include  <stdio.h>
#include  <unistd.h>
#include  <stdlib.h>

void main(void)
{
int g = 3;
switch (g%2)
{
case 1:
    printf("%d\n", g);;
case 0:
    printf("%d\n", g);

}
}
