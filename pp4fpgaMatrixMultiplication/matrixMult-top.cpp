/*
*/

#include<stdio.h>
#include <stdlib.h>
//#include<iostream>
#include <math.h>
#include "matrixMult.h"

BaseType A[N][M];
BaseType B[M][P];
BaseType AB[N][P];
BaseType AB_golden[N][P];

int main()
{
	for(int i=0; i<N; i++) {
		for(int j=0;j<M; j++) {
			A[i][j] = i+j;
		}
	}
	for(int i=0; i<M; i++) {
		for(int j=0;j<P; j++) {
			B[i][j] = i+j;
		}
	}
	matrixmul(A,B,AB);

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < P; ++j) {
			AB_golden[i][j] = 0;
			for (int k = 0; k < M; ++k) {
				AB_golden[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	bool diff = false;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < P; ++j) {
			if (AB[i][j] != AB_golden[i][j]) {
				diff = true;
			}
		}
	}

	if (diff) {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "FAIL: Output DOES NOT match the golden output\n");
		fprintf(stdout, "*******************************************\n");
		 return 1;
	} else {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "PASS: The output matches the golden output!\n");
		fprintf(stdout, "*******************************************\n");
		 return 0;
	}

}
