# AVR_AMBIQ1805_testing
AVR_AMBIQ1805_testing


### instresting to know
3V3 supply, no calibration, XT mode, RTC has less counts 16 seconds after one hour  
![3V3_slow_RTC.JPG](3V3_slow_RTC.JPG)  


5V supply, for sure that it was beyond manufacturer specification limit (max3.6V)  
no calibration, XT mode, RTC has extra counts 240 seconds about 20 minutes later, propotion to an hour, it would be 720 seconds roughly.
![5V_fast_RTC.JPG](5V_fast_RTC.JPG)  

### circuit
pdf [Schematic_ATmega328PB_AM1805_SX1276_2022-02-24.pdf](Schematic_ATmega328PB_AM1805_SX1276_2022-02-24.pdf)  
![Schematic_ATmega328PB_AM1805_SX1276_2022-02-24.png](Schematic_ATmega328PB_AM1805_SX1276_2022-02-24.png)  


### hostware  
![setRTC.exe](setRTC.exe)  
COM11 only, read PC host date, dump to MCU, MCU will set RTC, reset AM1805.  

or termnial program realterm [https://sourceforge.net/projects/realterm/](https://sourceforge.net/projects/realterm/)  
dump setting file for testing as following,   
[2022-06-22_235950.txt](2022-06-22_235950.txt)  
[2052-02-09_235950.txt](2052-02-09_235950.txt)  
[2099-12-31_235950.txt](2099-12-31_235950.txt)  

