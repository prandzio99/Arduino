void setup() {
  pinMode(0, OUTPUT);		// R-LED
  digitalWrite(0, LOW);		// off
  pinMode(1, OUTPUT);		// B-LED
  digitalWrite(1, LOW);		// off
  pinMode(2, OUTPUT);		// G-LED
  digitalWrite(2, LOW);		// off
  
  pinMode(3, INPUT);		// movement detector
  
  pinMode(4, OUTPUT);		// buzzer
}

void loop() {
  if(digitalRead(3)==HIGH) {	// if movement detected
    digitalWrite(0, HIGH);		// R on
    digitalWrite(2, LOW);		// G off
    digitalWrite(4, HIGH);		// buzzer on
  } else {						// otherwise
    digitalWrite(0, LOW);		// R off
    digitalWrite(2, HIGH);		// G on
    digitalWrite(4, LOW);		// buzzer off
  }
}

