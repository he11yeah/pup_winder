// include the library code:
#include <LiquidCrystal.h>

// read RPM

volatile int rpmcount = 0;//see http://arduino.cc/en/Reference/Volatile
int rpm = 0;
unsigned long lastmillis = 0;
int turnscount = 0;
bool isStarted = false;
unsigned long startMillis = 0;

void setup(){
 Serial.begin(9600); 
 digitalWrite(2, HIGH);
 attachInterrupt(0, add_turn, FALLING);//interrupt zero (0) is on pin two(2).
}

void loop(){
 
 if (millis() - lastmillis == 1000){  /*Update every one second, this will be equal to reading frecuency (Hz).*/
 
 detachInterrupt(0);    //Disable interrupt when calculating
 
 
 rpm = rpmcount * 60;  /* Convert frecuency to RPM, note: this works for one interruption per full rotation. For two interrups per full rotation use rpmcount * 30.*/
 
 Serial.print("RPM =\t"); //print the word "RPM" and tab.
 Serial.print(rpm); // print the rpm value.
 Serial.print("\t Turns=\t"); //print the word "Hz".
 Serial.println(turnscount); /*print revolutions per second or Hz. And print new line or enter.*/
 if (isStarted){
  Serial.print("Time Elapsed: ");
  Serial.println((millis()-startMillis)/1000);
 }
 rpmcount = 0; // Restart the RPM counter
 lastmillis = millis(); // Uptade lasmillis
 attachInterrupt(0, add_turn, FALLING); //enable interrupt
  }
}


void add_turn(){/* this code will be executed every time the interrupt 0 (pin2) gets low.*/
  if (!isStarted){
    isStarted = true;
    startMillis = millis();
  }
  rpmcount++;
  turnscount++;
}
