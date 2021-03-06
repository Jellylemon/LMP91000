/*
 * FILENAME:    LMP91000.h
 * AUTHOR:      Orlando S. Hoilett
 * EMAIL:       ohoilett@purdue.edu
 * VERSION:     0.3
 
 
 * DESCRIPTION
 
 
 
 * A FEW INSTRUCTIONS
 * All methods are defined and coded according to the instructions given in the
 * LMP91000 datsheet, December 2014 Revision, from Texas Instruments. All
 * references to the "datahseet" refer to this specific revision. The datasheet
 * is referenced in the code so that the user can have further consult if he/she
 * needs more information. A copy of the datasheet is included in the software
 * download.
 *
 * All references to "the device" refer to the LMP91000 Sensor AFE System:
 * Configurable AFE Potentiostat for Low-Power Chemical-Sensing Applications
 * Impedance Analyzer from Texas Instruments.
 *
 * TIA - Transimpedance Amplifier
 * TIACN - Transimpedance Amplifier Control Register (0x10)
 * REFCN - Reference Control Register (0x11)
 
 
 * UPDATES
 * Version 0.0
 * 2015/09/18:1200>
 *			Initialization of code development.
 * 2015/10/12:1010>
 *          Testing methods.
 * 2015/10/12:1041>
 *          Noticed that objects cannot be instantiated in the "setup()" method.
 *          No idea why that is.
 
 * SOURCES
 * Some code snippets were taken from
 * vicatcu. "LMP91000." Authored: Oct 27, 2014. Accessed:
 *      September 18, 2015. GitHub. <https://github.com/WickedDevice/LMP91000>
 * jorgenro1. "lmp91000." Authord: Jan 26, 2015. Acccessed:
 *      September 18, 2015. GitHub. <https://github.com/dgnest/lmp91000>
 
 * A couple of other useful links from TI's forum
 * https://e2e.ti.com/support/interface/etc_interface/f/146/t/258263
 * https://e2e.ti.com/support/amplifiers/precision_amplifiers/f/14/t/189399
 * https://e2e.ti.com/support/interface/etc_interface/f/146/t/195448
 * https://e2e.ti.com/support/amplifiers/precision_amplifiers/f/14/t/317192
 
 
 * DISCLAIMER
 * Copyright (C) Linnes Lab 2016, Purdue University, All rights reserved
 *
 */


#ifndef LMP91000_H
#define LMP91000_H

#include "Arduino.h"
#include "Wire.h"

const double TEMP_INTERCEPT = 1555;
const double TEMPSLOPE = -8;
const uint8_t LMP91000_I2C_ADDRESS = 0X48;

const uint8_t LMP91000_STATUS_REG = 0x00;    /* Read only status register */
const uint8_t LMP91000_LOCK_REG=0x01;    /* Protection Register */
const uint8_t LMP91000_TIACN_REG=0x10;    /* TIA Control Register */
const uint8_t LMP91000_REFCN_REG=0x11;    /* Reference Control Register*/
const uint8_t LMP91000_MODECN_REG=0x12;    /* Mode Control Register */

const uint8_t LMP91000_READY=0x01;
const uint8_t LMP91000_NOT_READY=0x00;

const uint8_t LMP91000_TIA_GAIN_EXT=0x00; //default
const uint8_t LMP91000_TIA_GAIN_2P75K=0x04;
const uint8_t LMP91000_TIA_GAIN_3P5K=0x08;
const uint8_t LMP91000_TIA_GAIN_7K=0x0C;
const uint8_t LMP91000_TIA_GAIN_14K=0x10;
const uint8_t LMP91000_TIA_GAIN_35K=0x14;
const uint8_t LMP91000_TIA_GAIN_120K=0x18;
const uint8_t LMP91000_TIA_GAIN_350K=0x1C;

const uint8_t LMP91000_RLOAD_10OHM=0X00;
const uint8_t LMP91000_RLOAD_33OHM=0X01;
const uint8_t LMP91000_RLOAD_50OHM=0X02;
const uint8_t LMP91000_RLOAD_100OHM=0X03; //default

const uint8_t LMP91000_REF_SOURCE_INT=0x00; //default
const uint8_t LMP91000_REF_SOURCE_EXT=0x80;

const uint8_t LMP91000_INT_Z_20PCT=0x00;
const uint8_t LMP91000_INT_Z_50PCT=0x20; //default
const uint8_t LMP91000_INT_Z_67PCT=0x40;
const uint8_t LMP91000_INT_Z_BYPASS=0x60;

const uint8_t LMP91000_BIAS_SIGN_NEG=0x00; //default
const uint8_t LMP91000_BIAS_SIGN_POS=0x10;

const uint8_t LMP91000_BIAS_0PCT=0x00; //default
const uint8_t LMP91000_BIAS_1PCT=0x01;
const uint8_t LMP91000_BIAS_2PCT=0x02;
const uint8_t LMP91000_BIAS_4PCT=0x03;
const uint8_t LMP91000_BIAS_6PCT=0x04;
const uint8_t LMP91000_BIAS_8PCT=0x05;
const uint8_t LMP91000_BIAS_10PCT=0x06;
const uint8_t LMP91000_BIAS_12PCT=0x07;
const uint8_t LMP91000_BIAS_14PCT=0x08;
const uint8_t LMP91000_BIAS_16PCT=0x09;
const uint8_t LMP91000_BIAS_18PCT=0x0A;
const uint8_t LMP91000_BIAS_20PCT=0x0B;
const uint8_t LMP91000_BIAS_22PCT=0x0C;
const uint8_t LMP91000_BIAS_24PCT=0x0D;

const uint8_t LMP91000_FET_SHORT_DISABLED=0x00; //default
const uint8_t LMP91000_FET_SHORT_ENABLED=0x80;
const uint8_t LMP91000_OP_MODE_DEEP_SLEEP=0x00; //default
const uint8_t LMP91000_OP_MODE_GALVANIC=0x01;
const uint8_t LMP91000_OP_MODE_STANDBY=0x02;
const uint8_t LMP91000_OP_MODE_AMPEROMETRIC=0x03;
const uint8_t LMP91000_OP_MODE_TIA_OFF=0x06;
const uint8_t LMP91000_OP_MODE_TIA_ON=0x07;

const uint8_t LMP91000_WRITE_LOCK=0x01; //default
const uint8_t LMP91000_WRITE_UNLOCK=0x00;

const uint8_t LMP91000_NOT_PRESENT=0xA8;    // arbitrary library status code

const double TIA_GAIN[] = {2750,3500,7000,14000,35000,120000,350000};
const double TIA_BIAS[] = {0, 0.01, 0.02, 0.04, 0.06, 0.08, 0.1, 0.12, 0.14,
    0.16, 0.18, 0.2, 0.22, 0.24};
const double TIA_ZERO[] = {0.2, 0.5, 0.67};


class LMP91000 {
    
private:
    
    uint8_t MENB; //IO pin for enabling and disabling I2C commands
    uint8_t gain;
    uint8_t zero;
    
    
public:
    
    //CONSTRUCTORS
    LMP91000(); //tested
    
    //sets and gets MENB pin for enabling and disabling I2C commands
    void setMENB(uint8_t pin); //tested
    uint8_t getMENB() const; //tested
    
    //sets and gets pin for reading output of temperature sensor
    void setTempSensor(uint8_t pin); //tested
    uint8_t getTempSensor() const; //tested
    
    //reads and writes to LMP91000 via I2C
    void write(uint8_t reg, uint8_t data) const; //tested
    uint8_t read(uint8_t reg) const; //tested
    
    //enables and disables LMP91000 for I2C commands
    //default state is not ready
    void enable() const; //tested
    void disable() const; //tested
    boolean isReady() const; //not working correctly with Eval board
    
    //locks and unlocks the transimpedance amplifier
    //and reference control registers for editing
    //default state is locked (read-only)
    void lock() const;
    void unlock() const;
    boolean isLocked() const;
    
    //sets the gain of the transimpedance amplifier
    void setGain(uint8_t gain); //tested
    double getGain() const;
    
    //sets the load for compensating voltage differences
    //between working and reference electrodes
    void setRLoad(uint8_t load) const; //tested
    
    //sets the source for the bias voltage for the
    //electrochemical cell
    void setRefSource(uint8_t source) const; //tested
    void setIntRefSource() const; //tested
    void setExtRefSource() const; //tested
    
    //sets reference voltage for transimpedance amplifier
    void setIntZ(uint8_t intZ); //tested
    double getIntZ() const;
    
    //sets bias voltage for electrochemical cell
    void setBiasSign(uint8_t sign) const; //tested
    void setNegBias() const; //tested
    void setPosBias() const; //tested
    void setBias(uint8_t bias) const; //tested
    
    //enable and disable FET for deep sleep mode
    void setFET(uint8_t selection) const; //tested
    void disableFET() const; //tested
    void enableFET() const; //tested
    
    //set operating modes for the LMP91000
    void setMode(uint8_t mode) const; //tested
    void sleep() const; //tested
    void setTwoLead() const; //tested
    void standby() const; //tested
    void setThreeLead() const; //tested
    void measureCell() const; //tested
    void getTemp() const;
    double getTemp(uint8_t sensor, double adc_ref, uint8_t adc_bits) const;
    
    //reading the output of the LMP91000
    uint16_t getOutput(uint8_t sensor) const;
    double getVoltage(uint16_t adcVal, double adc_ref, uint8_t adc_bits) const;
    double getCurrent(uint16_t adcVal, double adc_ref, uint8_t adc_bits) const;
    double getCurrent(uint16_t adcVal, double adc_ref, uint8_t adc_bits,
                      double extGain) const;
    
    /*
    double getVoltage(uint8_t sensor, double adc_ref, uint8_t adc_bits) const;
    double getCurrent(uint8_t sensor, double adc_ref, uint8_t adc_bits) const;
    double getCurrent(uint8_t sensor, double adc_ref, uint8_t adc_bits,
                      double extGain) const;
    */
    
};

#endif