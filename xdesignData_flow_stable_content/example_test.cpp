// 67d7842dbbe25473c3c32b93c0da8047785f30d78e8a024de1b57352245f9689
#include <iostream>
#include <stdlib.h>
#include "example.h"

void example(stream_t &in1, stream_t &in2, stream_t &out);

int main()
{
  // Declare streams
  stream_t in1, in2, out;


	value_int valDataCtrl;
	valDataCtrl.data = 0;
	valDataCtrl.keep = 0xF;
	valDataCtrl.strb = 0;
	valDataCtrl.user = 0;
	valDataCtrl.last = 0;
	valDataCtrl.id   = 0;
	valDataCtrl.dest = 0;

  // Write data into a and b
  for (int i = 0; i < 10; i++)
  {
    valDataCtrl.data = rand() % 10;
    in1.write(valDataCtrl);
    valDataCtrl.data = rand() % 10;
    in2.write(valDataCtrl);
  }

  example(in1, in2, out);
  
  int sum = out.read().data;
  
  std::cout << "sum = " << sum << std::endl;
  
  return 0;
}
