
#include <SoftwareSerial.h>

#define DIGITAL_OUT_PIN    4

SoftwareSerial Serial7Segment(7, 8); //RX pin, TX pin

int cycles = 0;

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
  
  char tempString[10]; //Used for sprintf
  sprintf(tempString, "%4d", cycles); 
  
  Serial7Segment.print(tempString); //Send serial string out the soft serial port to the S7S
  
  
  static boolean analog_enabled = false;
  static byte old_state = LOW;
  
  // If data is ready
  while (Serial.available())
  {    
    //delay(10);
    
    // read out command and data
    byte data0 = Serial.read();
    byte data1 = Serial.read();
    //byte data2 = Serial.read();
    
    if (data0 == 0x01)  // Command is to control digital out pin
    {
      if (data1 == 0x01) {
       cycles++;
       //Serial.println(data0);
//      digitalWrite(DIGITAL_OUT_PIN, HIGH);
//      else
//        digitalWrite(DIGITAL_OUT_PIN, LOW);
        
    }
  }  
}
}
