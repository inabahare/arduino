//  Our temperature thing

// Load display
#include "LiquidCrystal.h"

// Initialize display
LiquidCrystal lcd(10,11,12,13,14,15,16);

// Inputs
int button = 8;
int adjuster = 3;
int tempFeeler = 4;
int led = 9;

// Variable values
int buttonState = LOW;
int currentScreen = 1;
int adjusterDataMin = 18;
int adjusterDataMax = 20;
int minVal = 0;
int maxVal = 40;
float tempVal;
int ledState = LOW;

// Custom characters
byte degreeChar[8] = {
  B01000,
  B10100,
  B01000,
  B00000,
  B00000,
  B00000,
  B00000,
};

// Screen where temperature is shown
void tempScreen() {
	// Read from the temperature feeler
	tempVal = analogRead(tempFeeler) / 26;

	lcd.print("Temperaturen er:");
	lcd.setCursor(0,1); // Move cursor to other row
	lcd.print(tempVal);
	lcd.write(byte(0));
}

// Minimum emperature changer screen
void minTempScreen(){

	// Get the data from the temperature feeler
	adjusterDataMin = analogRead(adjuster) / 26;
	
	lcd.print("Set den mindste temperatur:");
	lcd.setCursor(0,1);

	// Fixing a bug where it would print 90.00 instead of 9.00
	// It now prints 09.00
	if(adjusterDataMin < 10){
		lcd.print(0);
	}

	lcd.print(adjusterDataMin);

	minVal = adjusterDataMin;


}

// Maximum temperature screen
void maxTempScreen(){

	// Get the data from the temperature feeler
	adjusterDataMax = analogRead(adjuster) / 26;
	

	lcd.print("Set den hojeste temperatur:");
	lcd.setCursor(0,1);

	// Fixing a bug where it would print 90.00 instead of 9.00
	// It now prints 09.00
	if(adjusterDataMax < 10){
		lcd.print(0);
	}

	lcd.print(adjusterDataMax);

	maxVal = adjusterDataMax;
}

// Get the LED to light up
void heatAdjust(){
	// The LED is on if it's colder than the minimum temperature
	if(tempVal < minVal){
	    digitalWrite(led, HIGH);
	}

	// It's off if it's hotter than the max temperature
	if(tempVal > maxVal){
	    digitalWrite(led, LOW);
	}
	
}

// setup
void setup() {
	lcd.createChar(0,degreeChar);

	// Initialize LCD display
	lcd.begin(16,2);
	lcd.setCursor(0,0);

	// Initialize the LED pin
	pinMode(led, OUTPUT);
}

// The main loop
void loop() {


	switch (currentScreen) {
	    case 1:
	      tempScreen();
	      break;
	    case 2:
	      minTempScreen();
	      break;
	    case 3:
	      maxTempScreen();
	      break;
	}

	// Call the heat adjust function
	heatAdjust();

	// Move cursor back
	lcd.setCursor(0,0);

	// Get weather or not the button has been pressed scrubs
	buttonState = digitalRead(button);

	// Check the button
	if(buttonState == HIGH){
		currentScreen++;
	}

	// Change current screen
	if(currentScreen == 4){
		currentScreen = 1;
	}

	// Ducktape for the code
	// The screen isn't as rapid in changing, quack
	while(buttonState == HIGH){
		buttonState = digitalRead(button);
	}

    delay(100);
}
