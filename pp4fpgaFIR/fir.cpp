#include "fir.h"

#define mac

// void fir(data_t *y, data_t x) {
// void fir(data_t x, acc_t* y) {
void fir(stream_t& input, stream_t& output) {
    #pragma HLS INTERFACE axis register both port=input
    #pragma HLS INTERFACE axis register both port=ouput
    #pragma HLS INTERFACE s_axilite port=return

    // coef_t c[N] = {1, 2, 0, -3, 0, 4, -5, 0, 1, -2, 0, -3, 0, 4, -5, 0};
    coef_t c[N] = {53, 0, -91, 0, 313, 500, 313, 0, -91, 0, 53};

    static data_t shift_reg[N];

    value_t valDataCtrl;
    valDataCtrl.data = 0;
    valDataCtrl.keep = 0xF;
    valDataCtrl.strb = 0;
    valDataCtrl.user = 0;
    valDataCtrl.last = 0;
    valDataCtrl.id   = 0;
    valDataCtrl.dest = 0;

    All_Data_Loop: 
    for (int j = 0; j < SIZE; ++j) {
        acc_t acc = 0;
        data_t x = input.read().data;
        #ifdef mac
        Shift_Accum_Loop: 
        for (int i = N - 1; i > 0; i--) {
            #pragma hls pipeline
            shift_reg[i] = shift_reg[i - 1];
        }
        shift_reg[0] = x;
        Accum_Loop: 
        for (int i = N - 1; i > 0; i--) {
            #pragma hls pipeline
            acc += shift_reg[i] * c[i];
        }
        acc += x * c[0];
        #else
        Shift_Accum_Loop: 
        for (int i = N - 1; i > 0; i--) {
            #pragma hls pipeline
            shift_reg[i] = shift_reg[i - 1];
            acc += shift_reg[i] * c[i];
        }
        acc += x * c[0];
        shift_reg[0] = x;
        #endif
        valDataCtrl.data = acc;
        if (j == SIZE - 1) {
            valDataCtrl.last = 1;
        }
        output.write(valDataCtrl);
    }

    // *y = acc;
    return;
}
