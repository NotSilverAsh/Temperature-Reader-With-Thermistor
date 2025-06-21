#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

int ThermistorPin = A0; // set the thermistor pin at Analog Pin A0
int Vo;
float R1 = 10000; // Resistor 10 Ohm
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

// LCD 16x2 I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  // Initialize the LCD Display (bla bla bla)
  lcd.init();
  lcd.backlight();
}

void loop() {
  Vo = analogRead(ThermistorPin); // Read the uncalibrated thermistor data
  R2 = R1 * (1023.0 / (float)Vo - 1.0); // Calibrating moment
  logR2 = log(R2); // Log the calibrated data into terminal
  T = 1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2); // Still calibrating but with math
  // CALIBRATED DATA //
  Tc = T - 273.15; // Temperature in ℃
  Tf = (Tc * 9.0) / 5.0 + 32.0; // Temperature in ℉

  // Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(Tf);
  Serial.print(" F; ");
  Serial.print(Tc);
  Serial.println(" C");

  // LCD Output
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(Tc, 1);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(Tf, 1);
  lcd.print(" F");

  delay(1000);
}