// 67d7842dbbe25473c3c32b93c0da8047785f30d78e8a024de1b57352245f9689
#include "example.h"

// Structure for "dut":
// 1. "writemem" reads from a stream and fills up the tb buffer
//
// 2. "readmem"
//     Function implements DATAFLOW between "readmemA" and "readmemB".
//     1. "readmemA" reads a stream of indexes to tb and writes out the lookup
//        as a stream "req_strm"
//     2. "readmemB" reads the previous stream ("req_strm") as indexes to
//        another tb lookup and writes the sum of the looped up numbers
//     Problem: tb is read from both sub-functions and prevent DATAFLOW
//     Solution: Apply the new stable pragma

//-------------------------------------------------------
void readmemA(stream_t &in_strm, stream_t &req_strm, int *tb)
{
A: for (int i = 0; i < 10; i++) {
    #pragma HLS PIPELINE
        value_int in = in_strm.read();
        value_int valDataCtrl;
        valDataCtrl.data = 0;
        valDataCtrl.keep = 0xF;
        valDataCtrl.strb = 0;
        valDataCtrl.user = 0;
        valDataCtrl.last = 0;
        valDataCtrl.id   = 0;
        valDataCtrl.dest = 0;
        int b = tb[in.data];
        if (b < 10)
        {
            req_strm.write(in);
        }
        else
        {
            req_strm.write(valDataCtrl);
        }
    }
    return;
}

//--------------------------------------------------------
void readmemB(stream_t &req_strm, stream_t &out_strm, int *tb)
{

    int sum = 0;
B: for (int i = 0; i < 10; i++) {
    #pragma HLS PIPELINE
        int r = req_strm.read().data;
        if (r != 0)
        {
            int b = tb[r];
            sum += b;
        }
    }
    value_int valDataCtrl;
	valDataCtrl.data = sum;
	valDataCtrl.keep = 0xF;
	valDataCtrl.strb = 0;
	valDataCtrl.user = 0;
	valDataCtrl.last = 1;
	valDataCtrl.id   = 0;
	valDataCtrl.dest = 0;
    out_strm.write(valDataCtrl);
    return;
}

//------------------------------------------------------
void readmem(stream_t &in_strm, stream_t &out_strm, int *tb)
{
    stream_t req_strm;
#pragma HLS STREAM variable = req_strm depth = 4
#pragma HLS DATAFLOW
#pragma HLS stable variable = tb
    readmemA(in_strm, req_strm, tb);
    readmemB(req_strm, out_strm, tb);
    return;
}

//-------------------------------------
void writemem(stream_t &in_strm, int *tb)
{
load:
    for (int i = 0; i < 10; i++)
    {
#pragma HLS PIPELINE
        int in = in_strm.read().data;
        tb[i] = in;
    }
    return;
}

//-------------------------------
void example(stream_t &in1_strm, stream_t &in2_strm, stream_t &out_strm)
{
    // tb is read twice in "readmem"
    #pragma HLS INTERFACE axis register both port=in1_strm
    #pragma HLS INTERFACE axis register both port=in2_strm
    #pragma HLS INTERFACE axis register both port=out_strm
    #pragma HLS INTERFACE s_axilite port=return
    int tb[10];
    #pragma HLS RESOURCE core = RAM_2P_BRAM variable = tb
    writemem(in1_strm, tb);
    readmem(in2_strm, out_strm, tb);
    return;
}
