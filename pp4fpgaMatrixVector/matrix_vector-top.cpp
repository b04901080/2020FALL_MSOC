/*
*/

#include<stdio.h>
#include <stdlib.h>
//#include<iostream>
#include <math.h>
//#include "dft.h"

#define SIZE 8
typedef int BaseType;

BaseType M[SIZE][SIZE];
BaseType V_In[SIZE];
BaseType V_Out[SIZE];
BaseType V_golden[SIZE];

extern void matrix_vector(BaseType M[SIZE][SIZE], BaseType V_In[SIZE], BaseType V_Out[SIZE]);

int main()
{
	for(int i=0; i<SIZE; i++)
	{
		V_In[i] = i;
		for(int j=0;j<SIZE; j++)
		  M[i][j] = i+j;
	}
	for (int i = 0; i < SIZE; ++i) {
		V_golden[i] = 0;
		for (int j = 0; j < SIZE; ++j) {
			V_golden[i] += V_In[j] * M[i][j];
		}
	}
	//Perform DFT
	matrix_vector(M,V_In,V_Out);

	bool diff = false;

	for (int i = 0; i < SIZE; ++i) {
		if (V_golden[i] != V_Out[i]) {
			diff = true;
		}
	}

	//Check against golden output.
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
