// LCD library
#include <LiquidCrystal.h>

// LCD object
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

double scaledTempRead; 	// scaled thermal sensor read
double tempWrite; 		// temperature for display


void setup() {
  lcd.begin(16, 2);			// LCD init
  }
void loop() {
  scaledTempRead = 5 * analogRead(A0) / 1024.0;
  tempWrite = (scaledTempRead-0.5)*100;
  lcd.setCursor(0,0);
  lcd.print("Temperature:");
  lcd.setCursor(0,1);
  lcd.print(tempWrite);
  lcd.setCursor(5,1);
  lcd.print(" deg. Cels.");
}
