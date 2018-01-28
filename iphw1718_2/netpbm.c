/* File: netpbm.c */
#include <stdlib.h>
#include <stdio.h>
#define EN 0

static int white_space(void) {
	int ch = getchar();
	while (ch == '\n' || ch == '\t' || ch == 32){
		ch = getchar();
	}
	return ch;
}

static int computation_and_putchar(int ch, char flag) {
	if (ch < '0' || ch > '9' || ch == EOF)
		return -1;
	if (flag)	putchar(ch);
	int num = 0;
	num = ch - 48 + num * 10;
	ch = getchar();
	while (ch != '\n' && ch != '\t' && ch != 32) {
		if (ch < '0' || ch > '9' || ch == EOF) {
			return -1;
		}
		if (flag)	putchar(ch);
		num = ch - 48 + num * 10;
		ch = getchar();
	}
	if (flag) putchar(ch);
	return num;
}


static int p6_p5(int max, int R) {
	int G, B, new, s = 0;
	while(R != EOF & R <= max) {
		s++;	/* +1 for R */

		G = getchar();
		s++;
		if (G == EOF || G > max)	return s;

		B = getchar();
		s++;
		if (B == EOF || B > max)	return s;

		new = (299 * R + 587 * G + 114 * B) / 1000;
		putchar(new);

		R = getchar();
	}
	return s;
}

static int p5_p4(int N, int M, int max, int ch) {
	int i, j;
	int px;
	for(i = 0; i < M; i ++) {
		px = 0;
		int byte = 0;
		int bits = 8;
		while (px != N && ch != EOF) {
			if (ch <= ((max + 1) / 2)) {
				int new = 1;
				new <<= bits - 1;
				byte |= new; 
			}
			px ++;
			ch = getchar();	
			if (ch > max)	return px * (i + 1);
			bits--;
			if (bits == 0) {
				putchar(byte);
				byte = 0;
				bits = 8;
			}
		}
		if (N % 8 != 0) {
			while (bits) {
				int new = 1;
				new <<= bits - 1;
				byte |= new;
				bits--;
			}
			putchar(byte);
		}
		if (ch == EOF) { 
			if (i != (M - 1)) return -1;
			else if (px != N) return -1;
		}

	}
	return N * M ;
}

static int p2_p1(int max, int ch) {
	int s = 0;

	if (ch > max) return s;

	while (ch != EOF && ch <= max) {
		s++;
		int byte = computation_and_putchar(ch, 0);
		if (byte <= (max+1) /2 ) printf("1 ");
		else printf("0 ");
		ch = white_space();
	}
	return s;
}

static int p3_p2(int max, int ch) {
	int s = 0;
	int R = computation_and_putchar(ch, 0);
	while (R != -1) {
			s++;// for R
			ch = white_space();
			int G = computation_and_putchar(ch, 0);
			s++;
			if (G == -1) return s;

			ch = white_space();
			int B = computation_and_putchar(ch, 0);
			s++;
			if (B == -1) return s;

			int new = (299 * R + 587 * G + 114 * B) / 1000;
			if (new != 0) {
				int n = new /100;
				printf("%d", n);
				new %= 100;
				n = new / 10;
				printf("%d", n);
				printf("%d",new % 10);
			} else 
				printf("%d", new);
			putchar(' ');
			ch = white_space();
			R = computation_and_putchar(ch, 0);
	}
	return s;
}

static int p3p2_p6p5(int max, int ch) { 
	int s = 0; 
	while (ch != EOF && ch <= max) {
		s++;
		ch = computation_and_putchar(ch, 0);
		putchar(ch);
		ch = white_space();
	}
	return s;
}

static int p6p5_p3p2(int max, int ch) {
	int s = 0;
	while (ch != EOF) {
		s++;
		if (ch != 0) {
			int n = ch / 100; 
			printf("%d", n);
			ch %= 100;
			n = ch / 10;
			printf("%d", n);
			printf("%d", ch % 10);
			putchar(' ');
		} else {
			printf("%d\n", 0);
		}
		ch = getchar();
	}
	return s;
}

static int p4_p1(int N, int ch) {
	int k, s = 0, px = 0;
	while (ch != EOF) {
		s += 8;
		if (s > N) {
			k = 8 -(s - N);
			s = 0;
			px += N;
		} else k = 8;
		int i;
		for (i = 0; i < k; i++) {
			int new = 128;
			new >>= i;
			new &= ch;
			if (new == 0) printf("0");
			else printf("1");
			putchar(' ');
		}
		ch = getchar();
	}
	return px;
}

static int p1_p4(int N, int ch) {
	int byte, k, px = 0, s = 0;
	if (ch == EOF) return s;
	do
	 {
	 	s += 8;
	 	if (s > N) {
	 		k = s - N;
	 		s = 0;
	 		px += N; 
	 	} else k = 0;
	 	byte = 0;
	 	int i;
	 	for (i = 8; i > k; i--) {
	 		if (i != 8) ch = white_space();
	 		if (ch == '1') {
	 			int new = 1;
	 			new <<= i - 1;
	 			byte |= new;
	 		}
	 	}
	 	for (i = k; i > 0; i--) {
	 		int new = 1;
	 		new <<= i - 1;
	 		byte |= new;
	 	}
	 	putchar(byte);
	 } while ((ch = white_space()) != EOF);
	 return px; 
}


int main(void) {
	int rt,N, M, max, magicn, new_magicn1, new_magicn2, new_magicn;
	char flag = 1;
	
	int ch = getchar();
	if (ch != 'P') {
		printf("Input error !\n");
		return EXIT_FAILURE;
	}
	putchar(ch);
	ch = getchar();
	new_magicn1 = 0;
	if (ch == '1') {
		magicn = '1';
		new_magicn2 = '4';
	} else if (ch == '2') {
		magicn = '2';
		new_magicn1 = '1';
		new_magicn2 = '5';
	} else if (ch == '3') {
		magicn = '3';
		new_magicn1 = '2';
		new_magicn2 = '6';
	} else if (ch == '4') {
		magicn = '4';
		new_magicn2 = '1';
	} else if (ch == '5') {
		magicn = '5';
		new_magicn1 = '4';
		new_magicn2 = '2';
	} else if (ch == '6') {
		magicn = '6';
		new_magicn1 = '5';
		new_magicn2 = '3';
	} else {
		printf("Input error !\n");
		return EXIT_FAILURE;
	}
	if (EN) {
		new_magicn = new_magicn2;
	} else {
		new_magicn = new_magicn1;
		if (new_magicn == 0) {
			printf("Input error !\n");
			return EXIT_FAILURE;
		}
	}
	putchar(new_magicn); 
	putchar('\n');

	ch = getchar();
	if (ch != '\n' && ch != '\t' && ch != 32 ) {
		printf("Input error !\n");
		return EXIT_FAILURE;
	}
	ch = white_space();
	while (ch == '#') {	/*we have message */
		do {
			ch = getchar();
			if (ch == EOF) {
				printf("Input error !\n");
				return EXIT_FAILURE;
			}
		} while (ch != '\n');
		ch = getchar();
	}
	
	N = computation_and_putchar(ch, flag);
	if (N < 0) {
		printf("Input error\n");
		return EXIT_FAILURE;
	}

	ch = white_space();
	M = computation_and_putchar(ch, flag);
	if (M < 0) {
		printf("Input error\n");
		return EXIT_FAILURE;
	}
	if (magicn != '1' && magicn != '4') {
		ch = white_space();
		if ( new_magicn == '1' || new_magicn == '4') flag = 0;
		max = computation_and_putchar(ch, flag); 
		if (max < 0) {
			printf("Input error\n");
			return EXIT_FAILURE;
		}
	}
	
	if (magicn == '6' || magicn == '5' || magicn == '4') {
		ch = getchar();
		if (ch == '\n' || ch == '\t' || ch == 32) {
			printf("Input error\n");
			return EXIT_FAILURE;	
		}
	} else {
		ch = white_space();
	}
	/* function call */
	if (magicn == '6') {
		if (EN)
			rt = p6p5_p3p2(max, ch);
		else
			rt = p6_p5(max, ch);

		if (rt != N * M * 3) {
			printf("Input error\n");
			return EXIT_FAILURE;
		}
	} else if (magicn == '5') {
		if (EN)
			rt = p6p5_p3p2(max, ch);
		else 
			rt = p5_p4(N, M, max, ch);
		if(rt != N * M) {
			printf("%d Input error\n", rt);
			return EXIT_FAILURE;
		}
	}else if (magicn == '4'){
		if ( p4_p1(N, ch) != N * M) {
			printf("Input error\n");
			return EXIT_FAILURE;
		}
	}else if (magicn == '3') {
		if (EN)
			rt = p3p2_p6p5(max, ch);
		else
			rt = p3_p2(max, ch);
		if (rt != N * M * 3) {
			printf("Input error\n");
			return EXIT_FAILURE;
		}
	} else if (magicn == '2') {	
		if (EN)
			rt = p3p2_p6p5(max, ch);
		else
			rt = p2_p1(max, ch);
		if (rt != N * M) {
			printf("Input error\n");
			return EXIT_FAILURE;
		}
	}else if (magicn == '1') {
		if (p1_p4(N, ch) != N * M) {
			printf("Input error\n");
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}
