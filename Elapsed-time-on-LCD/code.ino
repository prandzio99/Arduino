// Libraries
#include <stdbool.h>
#include <LiquidCrystal.h>

// LCD object
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

unsigned long lastPush; 			// time of last push
unsigned long displayTime; 			// time elapsed since last push

void setup() {
  lcd.begin(16, 2); 				// LCD init
  pinMode(3, INPUT_PULLUP); 		// button pin
  attachInterrupt(digitalPinToInterrupt(3), resetTime, RISING); // interrupt on pin 2
  lcd.print("Time (s): ");			// write(...)
  while(digitalRead(3)!= LOW){}		// wait for input
}

void loop() {
  displayTime = (millis()-lastPush) / 1000;		// displayTime = (current time - lastPush time) / 1000
  lcd.setCursor(0,1);							// set cursor on second line
  if (displayTime < 1000) lcd.print(" ");		// if time < 1000s, insert blank space	} justifies to right
  if (displayTime < 100) lcd.print(" ");		// if time < 100s, insert blank space	} to delete "loose" chars
  if (displayTime < 10) lcd.print(" ");			// if time < 10s, insert blank space	} after reset
  lcd.print(displayTime);						// display time
}

void resetTime(){
  lastPush = millis();
}