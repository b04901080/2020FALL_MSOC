#define SIZE 8
typedef int BaseType;

void matrix_vector(BaseType M[SIZE][SIZE], BaseType V_In[SIZE], BaseType V_Out[SIZE]) {
#pragma HLS ARRAY_PARTITION variable=V_Out complete dim=1
#pragma HLS ARRAY_PARTITION variable=V_In complete dim=1
#pragma HLS ARRAY_PARTITION variable=M complete dim=2
	BaseType i, j;
data_loop:
	for (i = 0; i < SIZE; i++) {
		BaseType sum = 0;
#pragma HLS PIPELINE
	dot_product_loop:
		for (j = 0; j < SIZE; j++) {

			sum += V_In[j] * M[i][j];
		}
		V_Out[i] = sum;
	}
}
