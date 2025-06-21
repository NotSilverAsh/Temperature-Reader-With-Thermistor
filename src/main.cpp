#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// read from the thermistor on analog pin A0
int thermistorPin = A0;
int vo; // store the raw analog value from the thermistor

// 10k ohm resistor as part of the voltage divider
float R1 = 10000;

// hold the calculated values later
float logR2, R2, T, Tc, Tf;

// convert resistance to temperature
float c1 = 1.009249522e-03;
float c2 = 2.378405444e-04;
float c3 = 2.019202697e-07;

// === LCD screen setup ===
// LCD uses I2C protocol
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  // Turn on and light up the LCD screen
  lcd.init();
  lcd.backlight();
}

void loop() {
  // === Read the thermistor value ===
  vo = analogRead(thermistorPin); // Get the analog value from A0

  // ===  Calculate resistance of the thermistor ===
  // uses the voltage divider formula
  R2 = R1 * (1023.0 / (float)vo - 1.0);
  logR2 = log(R2); // Natural logarithm of R2

  // === Convert resistance to temperature (Kelvin) using Steinhart-Hart equation ===
  T = 1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2);

  // === Convert to °C and °F ===
  Tc = T - 273.15;              // Kelvin to Celsius
  Tf = (Tc * 9.0) / 5.0 + 32.0; // Celsius to Fahrenheit

  // === Print results to the Serial Monitor ===
  Serial.print("Temperature: ");
  Serial.print(Tf);
  Serial.print(" F; ");
  Serial.print(Tc);
  Serial.println(" C");

  // === Display on the LCD screen ===
  lcd.clear();            // Wipe the screen
  lcd.setCursor(0, 0);    // Top row
  lcd.print("Temp: ");
  lcd.print(Tc, 1);       // Show 1 decimal place
  lcd.print(" C");

  lcd.setCursor(0, 1);    // Bottom row
  lcd.print("Temp: ");
  lcd.print(Tf, 1);
  lcd.print(" F");
  delay(1000);
}