// xiaolaba 2022-06-20
// https://github.com/xiaolaba

// copy from, https://github.com/stevenlianyi/Arduino-AB1805-AM105 


#ifndef AB1850_h
#define AB1850_h
#include <Arduino.h>
//#include <I2C.h>
#include <Wire.h>

#include "stdint.h"


// xiaolaba, add comment
#define AM1805 0x69 //I2C address of AM1805, 7bit address, 1011001
#define I2CreadAM1805 0xd2 // see data sheet, 7bit address, 1011001 + read bit 0 = 8bit 10110010 = 0xd2
#define I2CwriteAM1805 0xd3 // see data sheet 1011001 + read bit 1 = 8bit 10110011 = 0xd3




#define HUNDRETH_REGISTER           0x00
#define SECOND_REGISTER             0x01
#define MINUTE_REGISTER             0x02
#define HOUR_REGISTER               0x03
#define DATE_REGISTER               0x04
#define MONTH_REGISTER              0x05
#define YEAR_REGISTER               0x06
#define WEEKDAY_REGISTER            0x07
#define HUNDRETH_ALARM_REGISTER     0x08
#define SECOND_ALARM_REGISTER       0x09
#define MINUTE_ALARM_REGISTER       0x0A
#define HOUR_ALARM_REGISTER         0x0B
#define DATE_ALARM_REGISTER         0x0C
#define MONTH_ALARM_REGISTER        0x0D
#define WEEKDAY_ALARM_REGISTER      0x0E
#define STATU_REGISTER              0x0F

#define CONTROL1_REGISTER           0x10
#define CONTROL2_REGISTER           0x11
#define INT_MASK_REGISTER           0x12
#define SQW_REGISTER                0x13
#define CAL_XT_REGISTER             0x14
#define CAL_RC_HI_REGISTER          0x15
#define CAL_RC_LOW_REGISTER         0x16
#define INT_POLARITY_REGISTER       0x17
#define TIMER_CONTROL_REGISTER      0x18
#define TIMER_REGISTER              0x19
#define TIMER_INITIAL_REGISTER      0x1A
#define WDT_REGISTER                0x1B
#define OSC_CONTROL_REGISTER        0x1C
#define OSC_STATUS_REGISTER         0x1D

#define RESERVED                    0x1E

#define CONFIG_KEY_REGISTER         0x1F
#define TRICKLE_REGISTER            0x20
#define BREF_CONTROL_REGISTER       0x21

#define RESERVED                    0x22
#define RESERVED                    0x23
#define RESERVED                    0x24
#define RESERVED                    0x25

#define AFCTRL_REGISTER             0x26
#define BATMODE_REGISTER            0x27  //bit 7 only, bit6:0 RESERVED

#define ID0_REGISTER                0x28  //bcd 0x18 for AM1805
#define ID1_REGISTER                0x29  //bcd 0x5
#define ID2_REGISTER                0x2A
#define ID3_REGISTER                0x2B  // lot7:0
#define ID4_REGISTER                0x2C
#define ID5_REGISTER                0x2D
#define ID6_REGISTER                0x2E
#define ASTAT_REGISTER              0X2F

#define OCTRL_REGISTER              0x30

#define UNKNOWN_REGISTER            0x31
#define UNKNOWN_REGISTER            0x32
#define UNKNOWN_REGISTER            0x33
#define UNKNOWN_REGISTER            0x34
#define UNKNOWN_REGISTER            0x35
#define UNKNOWN_REGISTER            0x36
#define UNKNOWN_REGISTER            0x37
#define UNKNOWN_REGISTER            0x38
#define UNKNOWN_REGISTER            0x39
#define UNKNOWN_REGISTER            0x3A
#define UNKNOWN_REGISTER            0x3B
#define UNKNOWN_REGISTER            0x3C
#define UNKNOWN_REGISTER            0x3D
#define UNKNOWN_REGISTER            0x3E

#define EXTENSION_ADDRESS_REGISTER  0x3F



#define TENTH_MASK                  0xF0
#define HUNDRETH_MASK               0x0F
#define SECOND_MASK                 0x7F
#define MINUTE_MASK                 0x7F
#define HOUR_24_MASK                0x3F
#define HOUR_12_MASK                0x1F
#define AM_PM_MASK                  0x20
#define DATE_MASK                   0x3F
#define MONTH_MASK                  0x1F
#define YEAR_MASK                   0xFF
#define WEEKDAY_MASK                0x07



#define TENTH_ALARM_MASK            0xF0
#define HUNDRETH_ALARM_MASK         0xF0
#define SECOND_ALARM_MASK           0x7F
#define MINUTE_ALARM_MASK           0x7F
#define HOUR_24_ALARM_MASK          0x3F
#define HOUR_12_ALARM_MASK          0x1F
#define DATE_ALARM_MASK             0x3F
#define MONTH_ALARM_MASK            0x1F
#define WEEKDAY_ALARM_MASK          0x07
//#define STATUS_MASK                 0x


#define MONDAY                      0
#define TUESDAY                     1
#define WEDNESDAY                   2
#define THURSDAY                    3
#define FRIDAY                      4
#define SATURDAY                    5
#define SUNDAY                      6

#define MIN_HUNDREDTHS              0
#define MAX_HUNDREDTHS              0x99
#define MIN_SECOND                  0
#define MAX_SECOND                  0x60
#define MIN_MINUTE                  0
#define MAX_MINUTE                  0x60
#define MIN_HOURS                   0
#define MAX_HOURS                   0x24        
#define MIN_WEEKDAY                 1
#define MAX_WEEKDAY                 0x08  
#define MIN_DATE                    0
#define MAX_DATE                    0x32  
#define MIN_MONTH                   0
#define MAX_MONTH                   0x13
#define MIN_YEAR                    0
#define MAX_YEAR                    0x100

class AB1805 {
    public:
        AB1805();
		void begin();
		
        uint8_t read_rtc_register(const uint8_t rtc_register);
        uint8_t write_rtc_register(const uint8_t rtc_register, const uint8_t data);
        
		uint8_t get_rtc_data(const uint8_t rtc_register, const uint8_t register_mask);

        uint8_t get_second_Hundredths(void);
        uint8_t get_second(void);
        uint8_t get_minute(void);
        uint8_t get_hour(void);
        uint8_t get_weekday(void);
        uint8_t get_date(void);
        uint8_t get_month(void);
        uint8_t get_year(void);

        void get_datetime(void);

        uint8_t get_seconds_alarm(void);
        uint8_t get_minutes_alarm(void);
        uint8_t get_hour_alarm(void);
        uint8_t get_weekday_alarm(void);
        uint8_t get_date_alarm(void);
        uint8_t get_month_alarm(void);
        //uint8_t get_year_alarm(void);

        void set_second_Hundredths(const uint8_t value);
        void set_second(const uint8_t value);
        void set_minute(const uint8_t value);
        void set_hour(const uint8_t value);
        void set_weekday(const uint8_t value);
        void set_date(const uint8_t value);
        void set_month(const uint8_t value);
        void set_year(const uint8_t value);

        void set_datetime(uint8_t year, uint8_t month, uint8_t date, 
        uint8_t day, uint8_t hour, uint8_t minutes, uint8_t seconds);

        bool set_seconds_alarm(uint8_t value);
        bool set_minutes_alarm(uint8_t value);
        bool set_hour_alarm(uint8_t value);
        bool set_weekday_alarm(uint8_t value);
        bool set_date_alarm(uint8_t value);
        bool set_month_alarm(uint8_t value);
        bool set_year_alarm(uint8_t value);

       
		String get_date_string(void);
		
		
    private:
        uint8_t _ss_pin;
        volatile uint8_t _year;
        volatile uint8_t _month;
        volatile uint8_t _date;
        volatile uint8_t _weekday;
        volatile uint8_t _hour;
        volatile uint8_t _minutes;
        volatile uint8_t _seconds;
        volatile uint8_t _second_Hundredths;
        
        volatile uint8_t _alarm_year;
        volatile uint8_t _alarm_month;
        volatile uint8_t _alarm_date;
        volatile uint8_t _alarm_weekday;
        volatile uint8_t _alarm_hour;
        volatile uint8_t _alarm_minutes;
        volatile uint8_t _alarm_seconds;
};

#endif
