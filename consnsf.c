#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define K 9

bool non_square_free(int num) {
	if (num == 2 || num == 3) return false;
	if (num % (2 * 2) == 0) return true;
	if (num % (3 * 3) == 0) return true;
	int d = 5;
	while (d * d <= num) {
		if (num % (d * d) == 0) return true;
		if (num % ((d + 2) * (d + 2)) == 0) return true;
		d += 6;
	}
	return false;
}


void print(int n) {
	printf("  %d = ", n);
	int d = 2;
	int num = n;
	while (n > 1) {
		while (n % d == 0) {
			if (n != num) printf("x");
			printf(" %d ", d);
			n /= d;
		}
		d++;
	}
	printf("\n");
}


int main(void) {
	int n = 2;
	bool find = false;
	int i;
	do {
		if (non_square_free(n)) {
			int num;
			for(i = 1; i!= K; i++) {
				num = n + K - i;
				if (!(non_square_free(num))) break;
			}
			if (i == K) find = true;
			else
				n += K - i + 1;
		} else {
			n++;
		}
	} while (!find);
	printf("For K = %d :\n", K);
	for (i = n; i < n + K; i++) {
		print(i);
	}
	printf("\n");
	return EXIT_SUCCESS;
}
