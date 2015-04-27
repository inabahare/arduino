#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7, 8);

int button = 1;
int light = 2;
float state = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
}

void loop() {
  state = analogRead(button);
  analogWrite(2, 1000);  
  Serial.println(state * 0.038);
  lcd.write(state * 0.038);
  
  delay(100);
}
