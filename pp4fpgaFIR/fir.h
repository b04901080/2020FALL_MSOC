#include <hls_stream.h>
#include <ap_axi_sdata.h>

#define N 11
const int SIZE = 256;

typedef int coef_t;
typedef int data_t;
typedef int acc_t;

typedef ap_axiu<32,1,1,1> value_t;
typedef hls::stream<value_t> stream_t;


// void fir(int input, int *output, int taps[NUM_TAPS]);
// void fir(data_t input, acc_t *output);
void fir(stream_t& input, stream_t& output);