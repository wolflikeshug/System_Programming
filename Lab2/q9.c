#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// print how many byte, Mb or Gb of the Input number (round in int)
void print_size(int size) {
	if (size < 1024) {
		printf("%i byte\n", size);
	}
	else if (size < 1024 * 1024) {
		printf("%i Mb\n", size / 1024);
	}
	else {
		printf("%i Gb\n", size / 1024 / 1024);
	}
}

int main() {
	int size;
	printf("Input size: ");
	scanf("%i", &size);
	print_size(size);
	return 0;
}