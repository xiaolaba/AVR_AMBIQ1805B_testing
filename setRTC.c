//--------------------------- setRTC.c
//JUN-22-2022, xiaolaba

// 2018-NOV-17, library has been update, https://www.teuniz.net/RS-232/
// November 22, 2017 new version

// all function named RS232_ as prefix
// fix the mian.c source code here, fucntion call add prefix "RS232_"
// MODE change from "N81" ro "8N1" 
// upload to Github, include library source code as original author license GNU GPL.

// how to compile
// install minGW, http://sourceforge.net/projects/mingw/files/
// Win10,
// run dosbox.bat,
// command line, set path=c:\MinGW\bin;%path%
// or command line, set_path.bat
// command line, compile.bat
// 
// Gcc, 沒有GDB 除錯資料的編譯 
//   gcc -static -o RS232.exe main.c RS232_xiaolaba.c
// 
//用G++, 包含GDB 除錯資料的編譯 g
//   ++ -g -static -o RS232.exe main.c RS232_xiaolaba.c

// 2021-SEP-21, test DTR / RTS pin control
 
#include <stdio.h> //wordpress 自動去除 < > 及內容, 解決辦法, 前後加空格
#include <stdlib.h>

#include <time.h>

unsigned char buf[]="set_RTC 2022-06-22 03 00:00:00_xiaolaba";
//unsigned char set_RTC[]="set_RTC";

/*

#define BST (+1)
#define CCT (+8)

struct tm {
   int tm_sec;         // second, 0-59
   int tm_min;         // minute - 0-59
   int tm_hour;        // hour 0 -23
   int tm_mday;        // day of month, 1 - 31
   int tm_mon;         // month, 0 - 11
   int tm_year;        // year, 0 = 1900
   int tm_wday;        // day of a week, 1-7
   int tm_yday;        // day of year, 0 - 365
   int tm_isdst;       // daylight saving
};


   time_t rawtime;
   struct tm *info;
 
   time(&rawtime);
   // get GMT time //
   info = gmtime(&rawtime );
   
   printf("GTM time\n");
   printf("Lodon?敦：%2d:%02d\n", (info->tm_hour+BST)%24, info->tm_min);
   printf("china：%2d:%02d\n", (info->tm_hour+CCT)%24, info->tm_min);
*/

#define TPE (+8)	//Taipei Time, GMT+8

void readtime () {
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  printf("now: %d-%02d-%02d %02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_wday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}


unsigned char hex2bcd (unsigned char x)
{
    unsigned char y;
    y = (x / 10) << 4;
    y = y | (x % 10);
    return (y);
}


unsigned int HexToBCD16bit(unsigned int number)
 {
    unsigned char i=0; // will count the 4 bit groups
    unsigned int k = 0; // the final result to be built up
    // while the number still has digits to go..
    while(number)
    {
        // shift the bottom digit into the right 4 bit group
        k = ( k ) | ((number%10) << i*4);
        // lose the lower digit
        number = number / 10;
        // move to the next 4 bit group
        i++;
    }
    return(k);
 }

 
#include "rs232.h" //wordpress 自動轉換雙引號為 半角符號, 無法解決
//原因參考以下
//http://farlee.info/archives/wordpress-format-quote-mark.html
 
//測試用, 打開 com port, 發送3byte資料, 關閉 com port
 
 
 
int main()
{
  // show predefine string only
  printf("%s\n", buf);


  //readtime ();
  time_t t = time(NULL);
//  struct tm tm = *localtime(&t);
  struct tm tm = *gmtime(&t);
  printf("now: %d-%02d-%02d %02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_wday, tm.tm_hour + TPE, tm.tm_min, tm.tm_sec);
  printf("now: %d-%02d-%02d %02d %02d:%02d:%02d\n", tm.tm_year -  100, tm.tm_mon + 1, tm.tm_mday, tm.tm_wday, tm.tm_hour + TPE, tm.tm_min, tm.tm_sec);

  printf("2022 bcd = 0x%x\n", HexToBCD16bit(2022));
	
//int RS232_OpenComport(int comport_number, int baudrate, const char * mode)

//RS232_OpenComport(4, 9600, "N81"); //win32/ win64 底下有問題, 需要改library

//** change com port number array with one the first dummy element, or write COM#-1
//** Windows COM PORT number is COM1,COM2, index is -1
//  RS232_OpenComport(6-1, 115200, "8N1"); //win32/ win64 底下有問題, 需要改library

  int comport=11;
  int c;

// 2021-SEP-21, test DTR / RTS pin control
// JUN-22-2022, xiaolaba, setRTC

  printf("read PC datetime, setRTC, wanna open COM%d 9600 N81\n", comport);
  //RS232_OpenComport(comport, 115200, "8N1"); //win32/ win64 底下有問題, 需要改library
//  if ( (RS232_OpenComport(comport, 115200, "8N1") ) == 1 ) {	
  if ( (RS232_OpenComport(comport, 9600, "8N1") ) == 1 ) {	
	  printf("Press ENTER to Continue\n"); getchar();
	  exit(-1);		// no comport or error, end the program
  }


//  RS232_SendBuf(comport, buf, sizeof buf); 
  unsigned char set_RTC[]="set_RTC";
  RS232_SendBuf(comport, set_RTC, sizeof set_RTC-1); //send "set_RTC" to serial port

  buf[0] = HexToBCD16bit(tm.tm_year+1900) >> 8;	//0x 2022, 0x20 0x99, year
  buf[1] = HexToBCD16bit(tm.tm_year+1900) & 0xff; //0x2022, 22
//  buf[2] = hex2bcd(tm.tm_year-100);	//0x00 - 0x99, year
  buf[2] = hex2bcd(tm.tm_mon + 1);	//0x01 - 0x12, for 12 months
  buf[3] = hex2bcd(tm.tm_mday);		//0x01 - 0x31 ,for days
  buf[4] = hex2bcd(tm.tm_wday);		//0x01 - 0x07, for monday to sunday
  buf[5] = hex2bcd(tm.tm_hour +  + TPE );	//GMT+8, hour
  buf[6] = hex2bcd(tm.tm_min);
  buf[7] = hex2bcd(tm.tm_sec);
  buf[8] = 0x0;  
  RS232_SendBuf(comport, buf, 9);	//send this buf of bcd RTC string to serial port,

  // send decoded bcd to serial port for eyes only
  printf("bcd string, %s", set_RTC);	//console diaplay the bcd of buf
  for (int i = 0; i < 8; i++)
  {
    RS232_SendByte(comport, (buf[i] >> 4) + 0x30);
    RS232_SendByte(comport, (buf[i] &  0xf) + 0x30);
	printf("%c%c", (buf[i] >> 4) + 0x30, (buf[i] &  0xf) + 0x30 );	//console diaplay the bcd of buf
  }
//  RS232_SendByte(comport, 0x0);
  RS232_SendByte(comport, '\n');	//new line for serial port

  printf("\n");

/*
  //// com port opened, send byte testing
  RS232_SendByte(comport, 'S');
  char i;
  for(i=0x30;i<0x40;i++){
    RS232_SendByte(comport, i);
  }
*/

 

/*
  //// control output pin, DTR and RTS
  RS232_enableDTR(comport);
  RS232_enableRTS(comport);
  
  printf("enabled DTR & RTS of COM%d\n", comport);
  printf("USB->COM (i.e. CP2102) usually the pin is 0V now, ");
  printf("Press ENTER to Continue\n"); getchar();


  
  RS232_disableDTR(comport);
  RS232_disableRTS(comport);
  
  printf("disabled DTR & RTS of COM%d\n", comport);
  printf("USB->COM (i.e. CP2102) usually the pin is 3.3V now, ");
*/

//  printf("Press ENTER to Continue\n"); getchar();




  
  printf("byebye, Press ENTER to close this window\n");  getchar();
  RS232_CloseComport(comport);
  

}



 
//--------------------------- setRTC.c