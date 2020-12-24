// The file cordic.h holds definitions for the data types and constant values
#include "cordic.h"

// The cordic_phase array holds the angle for the current rotation
// cordic_phase[0] =~ 0.785
// cordic_phase[1] =~ 0.463

// void cordic(THETA_TYPE theta, COS_SIN_TYPE &s, COS_SIN_TYPE &c)
void cordic(stream_t& in, stream_t& sin, stream_t& cos)
{
  #pragma HLS INTERFACE axis register both port=in
  #pragma HLS INTERFACE axis register both port=sin
  #pragma HLS INTERFACE axis register both port=cos
  #pragma HLS INTERFACE s_axilite port=return
  // Set the initial vector that we will rotate
  // current_cos = I; current_sin = Q
  value_t valDataCtrl;
	valDataCtrl.data = 0;
	valDataCtrl.keep = 0xF;
	valDataCtrl.strb = 0;
	valDataCtrl.user = 0;
	valDataCtrl.last = 0;
	valDataCtrl.id   = 0;
	valDataCtrl.dest = 0;
  for (int i = 1; i < NUM_DEGREE; ++i) {
    THETA_TYPE theta;
    theta.range() = in.read().data.range();

    COS_SIN_TYPE current_cos = 0.60735;
    COS_SIN_TYPE current_sin = 0.0;

    // This loop iteratively rotates the initial vector to find the
    // sine and cosine values corresponding to the input theta angle
    for (int j = 0; j < NUM_ITERATIONS; j++) {
        // Multiply previous iteration by 2^(-j).  This is equivalent to
        // a right shift by j on a fixed-point number.
        COS_SIN_TYPE cos_shift = current_cos >> j;
        COS_SIN_TYPE sin_shift = current_sin >> j;

      // Determine if we are rotating by a positive or negative angle
      if(theta >= 0) {
          // Perform the rotation
          current_cos = current_cos - sin_shift;
          current_sin = current_sin + cos_shift;

          // Determine the new theta
          theta = theta - cordic_phase[j];
      } else {
          // Perform the rotation
          current_cos = current_cos + sin_shift;
          current_sin = current_sin - cos_shift;

          // Determine the new theta
          theta = theta + cordic_phase[j];
      }
    }

    // Set the final sine and cosine values
    if (i == NUM_DEGREE - 1) {
      valDataCtrl.last = 1;
    }
    valDataCtrl.data.range() = current_sin.range();
    sin.write(valDataCtrl);
    valDataCtrl.data.range() = current_cos.range();
    cos.write(valDataCtrl);
  }
}
