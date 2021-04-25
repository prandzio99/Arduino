// Libraries
#include <LiquidCrystal.h>
#include <Keypad.h>
#include <string.h>
#include <stdbool.h>

// key map
char keys[4][4] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

// keypad pins
byte pin_rows[4] = {9,8,7,6};
byte pin_column[4] = {5,4,3,2};


// keypad objects
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, 4, 4);

const String passwd = "2137";	// password constant
String input_passwd;			// input password variable
bool logged_in = false;			// lock's state: false - locked, true - open
char key;						// last input key variable

// LCD object
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

void setup() {
  lcd.begin(16, 2);			// LCD init
  Serial.begin(9600);		// communication init
  input_passwd.reserve(4);	// reserve 4 chars for input
}

void loop() {
  lcd.setCursor(0,0);			// set cursor 1st line 1st column
  lcd.print("Press \'#\'");		// Write (...)
  key = keypad.getKey();		// get 'key' input from keypad
  if(key == '#') log();			// if input '#' then 'log()'
}

void log(){
  lcd.setCursor(0,0);			// set cursor 1st line 1st column
  lcd.print("Password: ");		// Write (...)
  lcd.setCursor(0,1);			// set cursor 2nd line 1st column
  delay(100);					// pause 0.1s
  for(int i = 0; i < 4; i++) {				// do 4 times:
    input_passwd += keypad.waitForKey();	//		wait for key and append it to input password variable
    lcd.print("*");							//		write '*'
    delay(100);								// pause 0.1s
  }
  lcd.clear();						// clear screen
  lcd.setCursor(0,0);				// set cursor 1st line 1st column
  if(input_passwd == passwd){		// if password is correct
    if(!logged_in) {					// if lock is locked
      lcd.print("Unlocked!");				// "unlock"
    } else {							// otherwise
      lcd.print("Locked!");					// "lock"
    }
    logged_in = !logged_in;				// alter lock's state
  } else {
    lcd.print("Wrong password!");	// otherwise print (...)
  }
  input_passwd = "";			// clear input password
  delay(1000);					// pause 1s
  lcd.clear();					// clear screen
}
 