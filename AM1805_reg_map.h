// xiaolaba 2022-06-20
// https://github.com/xiaolaba


const char * AM1805_REGISTER_MAP[] = {   // array stored in RAM

  "HUNDRETH_REGISTER",
  "SECOND_REGISTER",
  "MINUTE_REGISTER",
  "HOUR_REGISTER",
  "DATE_REGISTER",
  "MONTH_REGISTER",
  "YEAR_REGISTER",
  "DAY_REGISTER",
  "HUNDRETH_ALARM_REGISTER",
  "SECOND_ALARM_REGISTER",
  "MINUTE_ALARM_REGISTER",
  "HOUR_ALARM_REGISTER",
  "DATE_ALARM_REGISTER",
  "MONTH_ALARM_REGISTER",
  "DAY_ALARM_REGISTER",
  "STATU_REGISTER",
  
  "CONTROL1_REGISTER",
  "CONTROL2_REGISTER",
  "INT_MASK_REGISTER",
  "SQW_REGISTER",
  "CAL_XT_REGISTER",
  "CAL_RC_HI_REGISTER",
  "CAL_RC_LOW_REGISTER",
  "INT_POLARITY_REGISTER",
  "RTC_AM1805_CONTROL_REGISTER",
  "RTC_AM1805_REGISTER",
  "RTC_AM1805_INITIAL_REGISTER",
  "WDT_REGISTER",
  "OSC_CONTROL_REGISTER",
  "OSC_STATUS_REGISTER",
  
  "RESERVED",
  
  "CONFIG_KEY_REGISTER",
  "TRICKLE_REGISTER",
  "BREF_CONTROL_REGISTER",
  
  "RESERVED",
  "RESERVED",
  "RESERVED",
  "RESERVED",
  
  "AFCTRL_REGISTER",
  "BATMODE_REGISTER",
  
  "ID0_REGISTER",
  "ID1_REGISTER",
  "ID2_REGISTER",
  "ID3_REGISTER",
  "ID4_REGISTER",
  "ID5_REGISTER",
  "ID6_REGISTER",
  "ASTAT_REGISTER",
  
  "OCTRL_REGISTER",
  
  "UNKNOWN_REGISTER",
  "UNKNOWN_REGISTER",
  "UNKNOWN_REGISTER",
  "UNKNOWN_REGISTER",
  "UNKNOWN_REGISTER",
  "UNKNOWN_REGISTER",
  "UNKNOWN_REGISTER",
  "UNKNOWN_REGISTER",
  "UNKNOWN_REGISTER",
  "UNKNOWN_REGISTER",
  "UNKNOWN_REGISTER",
  "UNKNOWN_REGISTER",
  "UNKNOWN_REGISTER",
  "UNKNOWN_REGISTER",
  
  "EXTENSION_ADDRESS_REGISTER"
  
} ;




uint8_t dump_AM1805_register (uint8_t register_index)
{
    uint8_t value = RTC_AM1805.read_rtc_register(register_index);
    Serial.println(String(AM1805_REGISTER_MAP[register_index]) + " = 0x" + String(value, HEX));
    return value;
}

void write_AM1805_register (uint8_t register_index, uint8_t input_value)
{
    // dump register before write for visual
    uint8_t value = dump_AM1805_register(register_index);

    // write the register
    RTC_AM1805.write_rtc_register(register_index, input_value);

    //read back for validation
    Serial.print("writed & read back ");
    value = dump_AM1805_register (register_index);
}


void dump_AM1805_ID ()
{
  Serial.println("\ndump AM1805 ID\n");
  for (int i=ID0_REGISTER; i<=ID0_REGISTER+6; i++) {
    Serial.print("REG " + String(i, HEX) + " ");    
    uint8_t value = dump_AM1805_register(i);   
  }
}

void dump_AM1805_ALL_REGISTERS ()
{
  Serial.println("\ndump AM1805 register 0x00-0x3F\n");
  for (int i=0; i<=0x3f; i++) {
    Serial.print("REG " + String(i, HEX) + " ");
    uint8_t value = dump_AM1805_register(i);   
  }
}
