#include <stdio.h>
#include <stdlib.h>
#include "solve.h"

int main(void) {
	int nrid, nst, *dests;
	scanf("%d", &nrid);
	scanf("%d", &nst);
	dests = malloc(nrid *(sizeof(int)));
	if (dests == NULL) {
		printf("Sorry, cannot allocate memory\n");
		return -1;
	}
	for (int i = 0; i < nrid; i++) {
		int d;
		scanf("%d", &d);
		dests[i] = d; 
	}
	int mincost = solve (nrid, nst, dests);
	if (mincost == -1) {
		printf("Sorry, cannot allocate memory\n");
		return -1;
	}
	printf("Cost is: %d\n", mincost);

	free(dests);
	return 0;
}
