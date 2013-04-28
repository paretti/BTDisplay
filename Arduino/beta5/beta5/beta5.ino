
#include <SoftwareSerial.h>

#define DIGITAL_OUT_PIN    4

SoftwareSerial Serial7Segment(7, 8); //RX pin, TX pin

int cycles = 0;

unsigned char buf[160] = {0};
unsigned char len = 0;

unsigned long currentMillis;        // store the current value from millis()
unsigned long previousMillis;       // for comparison with currentMillis
int samplingInterval = 250;          // how often to run the main loop (in ms)

void setup()
{  
  pinMode(DIGITAL_OUT_PIN, OUTPUT);
  
  //BLE Mini is connected to pin 0 and 1.
  Serial.begin(57600);

  Serial7Segment.begin(9600); //Talk to the Serial7Segment at 9600 bps
  Serial7Segment.write('v'); //Reset the display - this forces the cursor to return to the beginning of the display
  
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop()
{
  
  //Send number to display
  
  //char tempString[10]; //Used for sprintf
  //sprintf(tempString, "%4d", cycles); 
  
  
  
  
  static boolean analog_enabled = false;
  static byte old_state = LOW;
  
  // If data is ready
  while (Serial.available())
  {   
    unsigned char c = Serial.read();
    if (c != 0xD)
    {
      if (len < 160)
        buf[len++] = c;
    }
    else
    {
     Serial7Segment.write('v'); //Reset the display - this forces the cursor to return to the beginning of the display

      int padding = 4 - len;
      memcpy(buf + padding, buf, len);
      memset(buf, ' ', padding);
      
      Serial7Segment.print((const char*)buf); //Send serial string out the soft serial port to the S7S
      Serial.print((const char*)buf);
      //memset(buf, '\0', 150);
      len = 0;
    }
    
//    
//
//    byte data0 = Serial.read();
//    byte data1 = Serial.read();
//   // byte data3 = Serial.read();
//    Serial.println(data0);
//    Serial.println("test");
//    //sprintf(data0, "%4d", cycles); 
//
//    //byte data1 = Serial.read();
//    //byte data2 = Serial.read(); 
}
}
