#include <stdio.h>
#include <stdlib.h>

/* #define REC	*/
/* #define MEM	*/
/* #define DP  */

static  int fw(int a, double b,int nrid, int *dests) {
	int c = 0;
	for (int i = 0; i < nrid; i++) {
		int d = dests[i];
		if (a < d && d <= b) {
			if (d - a < b - d)
				c += d - a;
			else
				c += b - d;
		}
	}
	return c;
}

static int maxfl(int nrid, int *dests) {
	int max = dests[0];
	for (int i = 1; i < nrid; i++) {
		if (dests[i] > max)
			max = dests[i];
	}
	return max;
}


#ifdef REC
int Mcomp(int i, int j,int nrid, int *dests) {
	if (j == 0) {
		return fw(0, 1.0/0.0, nrid ,dests);
	}
	else {
		double min = 1.0/0.0;
		for (int k = 0; k <= i; k++) {
			int mij = Mcomp(k, j-1, nrid, dests);
			int c = mij - fw(k, 1.0/0.0, nrid, dests) + fw(k, i, nrid, dests) + fw(i, 1.0/0.0, nrid, dests);
			if (c < min)
				min = c;
		}
		return min;
	}
}

int solve(int nrid, int nst, int *dests) {
	int nfl = maxfl(nrid, dests);
	int min = Mcomp(0, nst, nrid, dests);
	int min_i = 0;
	for (int i = 1; i <= nfl; i++) {
		int c = Mcomp(i, nst, nrid, dests);
		if (c < min) {
			min = c;
			min_i = i;
		}
	}
	if (nst == 0)
		printf("No elevator stops\n");
    else
    	printf("Last stop at floor %d\n", min_i);
	return min;
}
#endif


#ifdef MEM
int Mcomp(int i, int j,int nrid, int *dests, int **m) {
	if (j == 0) {
		m[i][j] = fw(0, 1.0/0.0, nrid ,dests);
		return m[i][j];
	}
	else {
		int mink;
		double min = 1.0/0.0;
		for (int k = 0; k <= i; k++) {
			int mij;
			if (m[k][j-1] != -1) 
				mij = m[k][j-1];
			else 
				mij = Mcomp(k, j-1, nrid, dests, m);
			int c = mij - fw(k, 1.0/0.0, nrid, dests) + fw(k, i, nrid, dests) + fw(i, 1.0/0.0, nrid, dests);
			if (c < min) {
				min = c;
				mink = k;
			}
		}
		m[i][j] = min;
		return min;
	}
}

int solve(int nrid, int nst, int *dests) {
	int nfl = maxfl(nrid, dests);
	int N = nfl + 1;
	int M = nst + 1;
	int **m = malloc(N * sizeof(int *));
	if (m == NULL) {
		printf("Sorry, cannot allocate memory\n");
		return -1;
	}
	for (int i = 0; i < N; i++) {
		m[i] = malloc(M * sizeof(int));
		if (m[i] == NULL) {
			printf("Sorry, cannot allocate memory\n");
			return -1;
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			m[i][j] = -1;
	}
	int min = Mcomp(0, nst, nrid, dests, m);
	int min_i = 0;
	for (int i = 1; i <= nfl; i++) {
		int c = Mcomp(i, nst, nrid, dests, m); 
		if (c < min) {
			min = c;
			min_i = i;
		}
	}
	if (nst == 0)
		printf("No elevator stops\n");
    else
    	printf("Last stop at floor %d\n", min_i);
    
    for (int i = 0; i < N; i++) {
		free(m[i]);
	}
	free(m);

	return min;
}
#endif

#ifdef DP
int solve(int nrid, int nst, int *dests) {
	int nfl = maxfl(nrid, dests);
	int N = nfl + 1;
	int M = nst + 1;
	int **m = malloc(N * sizeof(int *));
	if (m == NULL) {
		printf("Sorry, cannot allocate memory\n");
		return -1;
	}
	for (int i = 0; i < N; i++) {
		m[i] = malloc(M * sizeof(int));
		if (m[i] == NULL) {
			printf("Sorry, cannot allocate memory\n");
			return -1;
		}
	}

	int **karray = malloc(N * sizeof(int *));
	if (karray == NULL) {
		printf("Sorry, cannot allocate memory\n");
		return -1;
	}
	for (int i = 0; i < N; i++) {
		karray[i] = malloc(M * sizeof(int));
		if (karray[i] == NULL) {
			printf("Sorry, cannot allocate memory\n");
			return -1;
		}
	}

	for (int j = 0; j < M; j++) {
		for (int i = 0; i < N; i++) {
			if (j == 0 )
				m[i][j] = fw(0, 1.0/0.0, nrid, dests);
			else {
				int find_k = 0;
				int min = m[0][j - 1] - fw(0, 1.0/0.0, nrid, dests) + fw(0, i, nrid, dests) + fw(i, 1.0/0.0, nrid, dests);
				for (int k = 0; k <= i; k++) {
					int c = m[k][j - 1] - fw(k, 1.0/0.0, nrid, dests) + fw(k, i, nrid, dests) + fw(i, 1.0/0.0, nrid, dests);
					if (c < min) {
						min = c;
						find_k = k;
					}
				}
				karray[i][j] = find_k;
				m[i][j] = min;
			}
		}
	}
	
	int mini = 0;
	int min = m[0][0];
	for (int j = 0; j < M; j++) {
		for (int i = 0; i < N; i++) {
			printf("%3d ", m[i][j]);
			if (m[i][j] < min) {
				min = m[i][j];
				mini = i;
			}
		}
		printf("\n");
	}
	if (nst == 0)
		printf("No elevator stops\n");
	else {
		int* stops = malloc(nst * sizeof(int));
		if (stops == NULL) {
			printf("Sorry, cannot allocate memory\n");
			return -1;
		}
		stops[nst - 1] = mini;
		for (int i = nst - 1; i > 0 ; --i)
		{
			stops[i - 1] = karray[stops[i]][i+1];
		}
		printf("Elevator stops are:");
		for (int i = 0; i < nst; i++) {
			if (stops[i] != 0)
				printf(" %d", stops[i]);
		}
		printf("\n");
		free(stops);
	}

    for (int i = 0; i < N; i++) {
		free(m[i]);
	}
	free(m);

	for (int i = 0; i < N; i++) {
		free(karray[i]);
	}
	free(karray);


	return min;
}

#endif
