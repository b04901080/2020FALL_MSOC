# pp4fpga CORDIC

## About The Project
* 本design實作了一個CORDIC，輸入為角度，輸出為對應角度的sin與cos。

**Directory structure**
* **./bit ./hwh** FPGA燒錄用
* **./ipynb** FPGA python host
* **./cordic-top.cpp** 軟體Testbench
* **./cordic.cpp** kernel
* **./cordic.h** 標頭檔

## Usage
* 用.cpp .h進行軟體模擬
* 用.ipynb .hwh .bit在FPGA上運作

## Algorithm
* CORDIC

## References
* https://github.com/KastnerRG/pp4fpgas/tree/master/examples

## Contribution
* 增加precision
* 減少誤差


