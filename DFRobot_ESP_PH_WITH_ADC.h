/*
 * file DFRobot_ESP_PH_WITH_ADC.h * @ https://github.com/GreenPonik/DFRobot_ESP_PH_WITH_ADC_BY_GREENPONIK
 *
 * Arduino library for Gravity: Analog pH Sensor / Meter Kit V2, SKU: SEN0161-V2 + ADC Adafruit ADS1115
 * 
 * Based on the @ https://github.com/DFRobot/DFRobot_PH
 * Copyright   [DFRobot](http://www.dfrobot.com), 2018
 * Copyright   GNU Lesser General Public License
 *
 * ##################################################
 * ##################################################
 * ########## Fork on github by GreenPonik ##########
 * ############# ONLY ESP COMPATIBLE ################
 * ##################################################
 * ##################################################
 * 
 * version  V1.0
 * date  2019-05
 */

#ifndef _DFROBOT_ESP_PH_WITH_ADC_H_
#define _DFROBOT_ESP_PH_WITH_ADC_H_

#include "Arduino.h"

//first you need to define the raw voltage for your circuit
//the raw voltage for neutral pH 7.0 and acid pH 4.0 at 25 °c
//for the actual circuit => ESP32 + ADC (ADS1115)
#define PH_4_AT_25 1521
#define PH_7_AT_25 1134

/*new ranges when read value behind adc*/
#define PH_8_VOLTAGE 900
#define PH_6_VOLTAGE 1250
#define PH_5_VOLTAGE 1400
#define PH_3_VOLTAGE 1700

#define ReceivedBufferLength 10 //length of the Serial CMD buffer

class DFRobot_ESP_PH_WITH_ADC
{
public:
    DFRobot_ESP_PH_WITH_ADC();
    ~DFRobot_ESP_PH_WITH_ADC();
    void calibration(float voltage, float temperature, char *cmd); //calibration by Serial CMD
    void calibration(float voltage, float temperature);
    float readPH(float voltage, float temperature); // voltage to pH value, with temperature compensation
    void begin();                                   //initialization

private:
    float _phValue;
    float _acidVoltage;
    float _neutralVoltage;
    float _voltage;
    float _temperature;

    char _cmdReceivedBuffer[ReceivedBufferLength]; //store the Serial CMD
    byte _cmdReceivedBufferIndex;

private:
    boolean cmdSerialDataAvailable();
    void phCalibration(byte mode); // calibration process, wirte key parameters to EEPROM
    byte cmdParse(const char *cmd);
    byte cmdParse();
};

#endif
