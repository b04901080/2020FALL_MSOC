# pp4fpga FIR

## About The Project
* 本design實作了一個11 taps的FIR。

**Directory structure**
* **./bit ./hwh** FPGA燒錄用
* **./ipynb** FPGA python host
* **./fir_tb.cpp** 軟體Testbench
* **./fir.cpp** kernel
* **./fir.h** 標頭檔

## Usage
* 用.cpp與.h進行軟體模擬
* 用.ipynb與.hwh .bit在FPGA上運作

## Algorithm
* 11 taps FIR

## References
* https://github.com/KastnerRG/pp4fpgas/tree/master/examples

## Contributing
* 使其可以運行tb及FPGA
* 減少latency


