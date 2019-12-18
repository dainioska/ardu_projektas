// ultrasonic movement counter(project 2019-12-15_v01

#include <NewPing.h>
#include <TM1637Display.h>

// ultrasonic sensor 0
#define TRIGGER_PIN_0  8
#define ECHO_PIN_0     8
#define MAX_DISTANCE 400

// Define the TM1637Display connections pins:
#define CLK_1 2
#define DIO_1 3

NewPing sensor0(TRIGGER_PIN_0, ECHO_PIN_0, MAX_DISTANCE);
float distance0;

// Create display object of type TM1637Display:
TM1637Display display1 = TM1637Display(CLK_1, DIO_1);

// Create array that turns all segments on:
const uint8_t data[] = {0xff, 0xff, 0xff, 0xff};

// Create array that turns all segments off:
const uint8_t blank[] = {0x00, 0x00, 0x00, 0x00};

const int resetPin =12; //use to reset TM1637Display
int count=0;

void setup() {  
   pinMode(12, INPUT);
   Serial.begin (9600);  

   // Set the brightness:
  display1.setBrightness(7);
   // All segments on:
  display1.setSegments(data);
  delay(2000);
  display1.clear();
  display1.showNumberDec(0);
}
void loop() {
   
  distance0 = sensor0.ping_cm();
  delay(50);

  if(distance0 < 70 & distance0 > 50)
  {
    count++;
    display1.setSegments(blank);
    display1.showNumberDec(count);
    delay(1000);
  }

  if(digitalRead(12) ==LOW)
  {
    count =0;
    display1.setSegments(blank);
    display1.showNumberDec(count);
  }
 
  // Send results to Serial Monitor
  // Sensor 0
  Serial.print("Distance 0 = ");
  if (distance0 >= 400 || distance0 <= 2) {
    Serial.println("Out of range");
  }
  else {
   
    Serial.print(distance0);
    Serial.println(" cm");
    delay(200);
  } 
}
