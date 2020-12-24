#include <iostream>
#include "fir.h"

int main() {
// 	int taps[] = {1, 2, 0, -3, 0, 4, -5, 0, 1, -2, 0, -3, 0, 4, -5, 0};

	bool fail = false;
	coef_t c[N] = {53, 0, -91, 0, 313, 500, 313, 0, -91, 0, 53};
	acc_t  result[SIZE];
	int shift_reg[N] = {};
	for (int i = 0; i < SIZE; i++) {
		acc_t acc = 0;
		for (int j = N - 1; j >= 0; --j) {
			if (j == 0) {
				shift_reg[0] = i;
				acc += shift_reg[0] * c[0];
			}
			else {
				shift_reg[j] = shift_reg[j - 1];
				acc += shift_reg[j] * c[j];
			}
		}
		result[i] = acc;
	}

	stream_t in, out;
	value_t valDataCtrl;
	valDataCtrl.data = 0;
	valDataCtrl.keep = 0xF;
	valDataCtrl.strb = 0;
	valDataCtrl.user = 0;
	valDataCtrl.last = 0;
	valDataCtrl.id   = 0;
	valDataCtrl.dest = 0;

	for (int i = 0; i < SIZE; ++i) {
		valDataCtrl.data = i;
		in.write(valDataCtrl);
	}

	fir(in, out);

	for (int i = 0; i < SIZE; ++i) {
		acc_t ans = out.read().data;
		// std::cout << ans << std::endl;
		if (ans != result[i]) {
			fail = true;
		}
	}

	if (!fail) {
		std::cout << "====================" << std::endl;
		std::cout << "pass!" << std::endl;
		std::cout << "====================" << std::endl;
		return 0;
	}
	else {
		std::cout << "====================" << std::endl;
		std::cout << "failed!" << std::endl;
		std::cout << "====================" << std::endl;
		return 1;
	}
	
}
