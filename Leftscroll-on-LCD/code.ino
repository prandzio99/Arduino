// LCD library
#include <LiquidCrystal.h>

// LCD object
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// custom chars for Polish display
// ś
byte s1[] = {
	0b00010,
	0b00100,
	0b01110,
	0b10001,
	0b01110,
	0b10001,
	0b01110,
	0b00000
};

// ż
byte z2[] = {
	0b00100,
	0b00000,
	0b11111,
	0b00010,
	0b00100,
	0b01000,
	0b11111,
	0b00000
};

// ł
byte l3[] = {
	0b01100,
	0b00100,
	0b00100,
	0b00110,
	0b01100,
	0b00100,
	0b01110,
	0b00000
};

void setup() {
  lcd.begin(16, 2);			// LCD init
  lcd.createChar(0, s1);	// create custom char 'ś'
  lcd.createChar(1, z2);	// 'ż'
  lcd.createChar(2, l3);	// 'ł'
  lcd.setCursor(0,0);		// set cursor 1st line 1st column
  lcd.write(byte(0));		// write 'ś'
  lcd.setCursor(1,0);		// set cursor 1st line 2nd column
  lcd.print("wie");			// write "wie"
  lcd.setCursor(4,0);		// set cursor 1st line 5th column
  lcd.write(byte(1));		// write 'ż'
  lcd.setCursor(5,0);		// set cursor 1st line 6th column
  lcd.print("e jab");		// write "e jab"
  lcd.setCursor(10,0);		// set cursor 1st line 11th column
  lcd.write(byte(2));		// write'ł'
  lcd.setCursor(11,0);		// set cursor 1st line 12th column
  lcd.print("ka idared");	// write "ka idared"
  lcd.setCursor(0,1);		// set cursor 2nd line 1st column
  lcd.print("# TYLKO 3,49 za kg #");	// write (...)
  }
void loop() {
  delay(200);				// 200ms delay
  lcd.scrollDisplayLeft();	// scroll display by one column to the left
  delay(50);				// 50ms delay
}
