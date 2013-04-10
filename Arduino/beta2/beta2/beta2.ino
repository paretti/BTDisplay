
#include <Arduino.h>
#include <SPI.h>
#include "ble.h"
#include <SoftwareSerial.h>

const int softwareTx = 8;
const int softwareRx = 7;

SoftwareSerial s7s(softwareRx, softwareTx);

unsigned int counter = 0;  // This variable will count up to 65k
char tempString[10];  // Will be used with sprintf to create strings

void setup()
{
  s7s.begin(9600);
  setBrightness(0);
  clearDisplay();
  s7s.print("-HI-");
  
  
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(LSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  SPI.begin();
  
  //ble_begin();
  
  Serial.begin(57600);
}

unsigned char buf[16] = {0};
unsigned char len = 0;

void loop()
{
  
   sprintf(tempString, "%4d", counter);
   s7s.print(tempString);
   setDecimals(0b00000100);
   counter++;
   delay(100);
  
  while ( ble_available() )
    Serial.write(ble_read());

  while ( Serial.available() )
  {
    unsigned char c = Serial.read();
    if (c != 0xD)
    {
      if (len < 16)
        buf[len++] = c;
    }
    else
    {
      for (int i = 0; i < len; i++)
        ble_write(buf[i]);
      len = 0;
    }
  }
  
  ble_do_events();
}



void setBrightness(byte value)
{
  s7s.write(0x7A);  // Set brightness command byte
  s7s.write(value);  // brightness data byte
}

void clearDisplay()
{
  s7s.write(0x76);  // Clear display command
}

void setDecimals(byte decimals)
{
  s7s.write(0x77);
  s7s.write(decimals);
}

