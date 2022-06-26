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


### MCU setup and firmware burn  
connect usbtiny avr programmer, burn firmware to MCU,  
click and run the [burn.bat](burn.bat), job will be done   
firmware [AB1805.ino_atmega328pb_1000000L.hex](AB1805.ino_atmega328pb_1000000L.hex)  


### project folders
library, original copy, https://github.com/stevenlianyi/Arduino-AB1805-AM105  
library patched, 
[AB1805.cpp](AB1805.cpp), [AB1805.h](AB1805.h), [AM1805_reg_map.h](AM1805_reg_map.h)  
public\2022-06-19_LoRa\AB1805\release  
LoRa_328pb_dump_oringial  
LoRaDumpRegisters_test  
LoRaDuplex_test  
LoRaReceiver_test  
LoRaSimpleNode_test  
photo\schematic\
photo\pcba\
public\2022-06-22_RS232_C\setRTC\release  
public\2022-06-19_LoRa\CoolTermWin  

### hints, software reset AM1805B
5.15 Software Reset
Software may reset the AM18X5 by writing the special value of 0x3C to the Configuration Key register at offset 0x1F. This will provide the equivalent of a power on reset by initializing all of the AM18X5 registers. A software reset will not cause the nRST signal the be asserted.  

see datasheet throughtly.  
[Artasie-AM18X5-RTC-Datasheet_REV1.3_2019-FEB.pdf](Artasie-AM18X5-RTC-Datasheet_REV1.3_2019-FEB.pdf)  



### [AB1805.ino_atmega328pb_1000000L_115200BAUD_CAL.hex](AB1805.ino_atmega328pb_1000000L_115200BAUD_CAL.hex)
special firmware, dump OSCCAL to terminal, baud rate 115200 N81

