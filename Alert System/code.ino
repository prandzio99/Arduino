#include <LiquidCrystal.h>

#define BUTTON 2            // button pin
#define SENSOR 3            // sensor pin
#define RED 8               // red LED pin
#define GREEN 9             // green LED pin
#define CALIBRATION_TIME 30 // time for sensor to calibrate, default 30s

//initializing LCD
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

bool buttonState = false;                // true - odd pushes, false - even pushes
long long lastButtonStateChangeTime = 0; // last push time for precision
long long lastMoveTime = 0;              // last detected movement time
bool armed = false;                      // flag if system is armed
bool intruder = false;                   // flag if intruder detected

/*
-----------------------------------------------------------
	Procedure:		initialMessage
	Input:			void
	Output:			void
	Description:	LCD displays initial message
-----------------------------------------------------------
*/
void initialMessage()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("# to arm the system, press the button ##");
}

/*
-----------------------------------------------------------
	Procedure:		changeButtonState
	Input:			void
	Output:			void
	Description:	Interrupt attached function.
    				Change button state if button pushed.
                    Precision guarded, 100ms check.
-----------------------------------------------------------
*/
void changeButtonState()
{
    Serial.print("> Button pushed!\n");
    if (millis() - lastButtonStateChangeTime > 100 || lastButtonStateChangeTime == 0)
    {
        buttonState = !buttonState;
        lastButtonStateChangeTime = millis();
    }
}

/*
-----------------------------------------------------------
	Procedure:		movementDetected
	Input:			void
	Output:			void
	Description:	Interrupt attached function.
    				Records last detected movement time.
                    If system is armed, sets intruder flag
                    to true.
-----------------------------------------------------------
*/
void movementDetected()
{
    Serial.print("> Movement detected!\n");
    lastMoveTime = millis();
    if (armed)
        intruder = true;
}

/*
-----------------------------------------------------------
	Procedure:		redBlinkSequence
	Input:			blink interval lenght in ms
	Output:			void
	Description:	Utility function.
    				Red LED blink sequence with given 
                    interval, best divisible by 2.
-----------------------------------------------------------
*/
void redBlinkSequence(int interval)
{
    digitalWrite(RED, HIGH);
    delay(interval / 2);
    digitalWrite(RED, LOW);
    delay(interval / 2);
}

/*
-----------------------------------------------------------
	Procedure:		greenBlinkSequence
	Input:			void
	Output:			void
	Description:	Utility function.
    				Pre-set green LED blink sequence.
-----------------------------------------------------------
*/
void greenBlinkSequence()
{
    for (int i = 0; i < 6; i++)
    {
        digitalWrite(GREEN, HIGH);
        delay(75);
        digitalWrite(GREEN, LOW);
        delay(75);
    }
    digitalWrite(GREEN, HIGH);
    delay(550);
    digitalWrite(GREEN, LOW);
}

/*
-----------------------------------------------------------
	Procedure:		calibration
	Input:			void
	Output:			void
	Description:	Waiting function.
    				Gives time to the PIR sensor 
                    to calibrate.
-----------------------------------------------------------
*/
void calibration()
{
    digitalWrite(GREEN, HIGH);
    Serial.print("Calibrating the system ...\n");
    Serial.print(">>> ");
    for (int i = 0; i < CALIBRATION_TIME; i++)
    {
        Serial.print("#");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Calibrating");
        lcd.setCursor(11, 0);
        if (i % 3 == 0)
            lcd.print(".");
        else if (i % 3 == 1)
            lcd.print("..");
        else
            lcd.print("...");
        lcd.setCursor(0, 1);
        lcd.print((i / (double)CALIBRATION_TIME) * 100);
        lcd.setCursor(5, 1);
        lcd.print("%");
        redBlinkSequence(1000);
    }
    Serial.print("|\nDONE!\nSYSTEM READY!\n\n");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DONE!");
    lcd.setCursor(0, 1);
    lcd.print("SYSTEM READY!");
    greenBlinkSequence();
}

/*
-----------------------------------------------------------
	Procedure:		arm
	Input:			void
	Output:			void
	Description:	System arming sequence.
    				Sets flag if system is armed to true.
-----------------------------------------------------------
*/
void arm()
{
    digitalWrite(GREEN, LOW);
    Serial.print("Arming...\n");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Arming: ");
    for (int i = 0; i < 20; i++)
    {
        if (i % 2)
        {
            digitalWrite(RED, LOW);
            Serial.print("]");
        }
        else
        {
            digitalWrite(RED, HIGH);
            Serial.print("[");
            lcd.setCursor(i / 2, 1);
            lcd.print("#");
        }
        lcd.setCursor(8, 0);
        lcd.print(i * 5);
        lcd.setCursor(11, 0);
        lcd.print("%");
        delay(500);
    }
    armed = true;
    digitalWrite(RED, HIGH);
    Serial.print("\nArmed!\n");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("System ARMED!");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("###");
}

/*
-----------------------------------------------------------
	Procedure:		disarm
	Input:			void
	Output:			void
	Description:	System disarming sequence.
    				Sets flag if system is armed to false.
-----------------------------------------------------------
*/
void disarm()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("System DISARMED!");
    digitalWrite(RED, LOW);
    Serial.print("\nDisarmed!\n");
    armed = false;
    delay(1000);
    initialMessage();
}

/*
-----------------------------------------------------------
	Procedure:		defaultState
	Input:			void
	Output:			void
	Description:	Represents system's default state.
    				If movement is detected, lights up
                    the green LED for 3s.
-----------------------------------------------------------
*/
void defaultState()
{
    if (millis() - lastMoveTime < 3000 && lastMoveTime != 0)
    {
        digitalWrite(GREEN, HIGH);
    }
    else
    {
        digitalWrite(GREEN, LOW);
    }
    delay(333);
    lcd.scrollDisplayLeft();
}

/*
-----------------------------------------------------------
	Procedure:		alert
	Input:			void
	Output:			void
	Description:	Alarm representation.
    				Function locks the system.
-----------------------------------------------------------
*/
void alert()
{
    digitalWrite(RED, HIGH);
    Serial.print("Intruder detected!\n");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ALARM!!!");
    exit(0);
}

void setup()
{
    // Serial output communication setup
    Serial.begin(9600);

    // Pins' setup
    pinMode(BUTTON, INPUT_PULLUP);
    pinMode(SENSOR, INPUT);
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);

    digitalWrite(RED, LOW);
    digitalWrite(GREEN, LOW);

    attachInterrupt(digitalPinToInterrupt(BUTTON), changeButtonState, FALLING);
    attachInterrupt(digitalPinToInterrupt(SENSOR), movementDetected, RISING);

    // LCD launch
    lcd.begin(16, 2);

    // initial function calls
    calibration();
    initialMessage();
}

void loop()
{
    // if button hasn't been clicked AND the system is unarmed
    if (!buttonState && !armed)
    {
        // show default state
        defaultState();
    }

    // otherwise
    else
    {
        // if system not armed - arm it
        if (!armed)
            arm();

        // otherwise
        else
        {
            // if movement detected - give the "intruder" 5 seconds
            // to push the  button, if pushed - disarm the system
            while (millis() - lastMoveTime < 5000 && intruder)
            {
                lcd.setCursor(3, 0);
                lcd.print("!");
                if (!buttonState)
                {
                    disarm();
                    break;
                }
                else
                {
                    redBlinkSequence(200);
                }
            }

            // if the button hasn't been pushed
            // launch the alert function
            if (millis() - lastMoveTime >= 5000 && intruder)
            {
                alert();
            }

            // if movement not detected but button clicked
            // disarm the system
            if (!buttonState)
                disarm();

            // if nothing is happening then do nothing:
            // await movement detection or push of the button
        }
    }
}
