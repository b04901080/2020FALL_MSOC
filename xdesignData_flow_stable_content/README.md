# xdesign dataflow_stable_content

## About The Project
* 本design先傳10筆數字存入array，再傳10筆數字當作該array的index並把值相加回傳，若為out of boundary或0的index則不予累加。

**Directory structure**
* **./bit ./hwh** FPGA燒錄用
* **./ipynb** FPGA python host
* **./example_test.cpp** 軟體Testbench
* **./example.cpp** kernel
* **./example.h** 標頭檔

## Usage
* 用.cpp與.h進行軟體模擬
* 用.ipynb與.hwh .bit在FPGA上運作

## Algorithm
* 本design先傳10筆數字存入array，再傳10筆數字當作該array的index並把值相加回傳，若為out of boundary或0的index則不予累加。

## References
* ~Xilinx/Vivado/2019.2/examples/design

## Contributing
* 解決II violation

