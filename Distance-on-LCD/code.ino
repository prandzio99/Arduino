// Libraries
#include <LiquidCrystal.h>

// LCD object
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// some custom chars to make display in Polish
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

// ł
byte l2[] = {
	0b01100,
	0b00100,
	0b00100,
	0b00110,
	0b01100,
	0b00100,
	0b01110,
	0b00000
};

// ć
byte c3[] = {
  	0b00010,
	0b00100,
	0b01110,
	0b10001,
	0b10000,
	0b10001,
	0b01110,
	0b00000
};

const int trig = 7;		// trigger pin
const int echo = 6;		// echo pin

long dur;		// signal duration time
int dist;		// distance
int crude[5];	// measurements (5) array

void setup() {
  lcd.begin(16, 2);			// LCD init
  lcd.createChar(0, s1);	// create custom char 'ś'
  lcd.createChar(1, l2);	// 'ł'
  lcd.createChar(2, c3);	// 'ć'
  pinMode(trig, OUTPUT); 	// ustawienie pinu do trig jako output
  pinMode(echo, INPUT); 	// ustawienie pinu do echo jako input
}

void loop() {
  dist = getDist();				// get distance value
  lcd.setCursor(0,0); 			// set cursor on 1st line, 1st column
  lcd.print("Odleg");			// write (...)
  lcd.setCursor(5,0);			// set cursor on 1st line, 6th column
  lcd.write(byte(1));			// write 'ł'
  lcd.setCursor(6,0);			// set cursor on 1st line, 7th column
  lcd.print("o");				// write (...)
  lcd.setCursor(7,0);			// set cursor on 1st line, 8th column
  lcd.write(byte(0));			// write 'ś'
  lcd.setCursor(8,0);			// set cursor on 1st line, 9th column
  lcd.write(byte(2));			// write 'ć'
  lcd.setCursor(9,0);			// set cursor on 1st line, 10th column
  lcd.print(": ");				// write (...)
  lcd.print(dist); 				// print distance value
  lcd.print("cm   ");			// write (...)
  delay(10);					// 10ms delay (for stability)
}

int getDist(){
  for(int i = 0; i < 5; i++){		// loop getting 5 measurements
    digitalWrite(trig, LOW);		// trigger LOW
  	delayMicroseconds(2);			// 2 microseconds delay
  	digitalWrite(trig, HIGH); 		// trigger HIGH
  	delayMicroseconds(10);			// 10 microseconds delay
  	digitalWrite(trig, LOW);		// trigger LOW
  	dur = pulseIn(echo, HIGH);		// echo wait time
  	crude[i] = dur / 58;			// put into array the echo wait time converted to distance
  }
  return (crude[0]+crude[1]+crude[2]+crude[3]+crude[4]-findMax(crude,5))/4; // return average measurment excluding the largest measurment
}

int findMax(int arr[], int n) { 	// returns largest array element
    int max = arr[0];   			// initially first element is largest pierwszy element jest największy
    for (int i = 1; i < n; i++) 		// iterate over the whole array
        if (arr[i] > max) 			// if element is larger than current max
            max = arr[i]; 			// max = element
    return max;						// return max
}