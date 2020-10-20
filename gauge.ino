#include <LiquidCrystal.h>
#include <LcdBarGraph.h>
 
const byte lcdNumCols = 16; // -- number of columns in the LCD
const byte sensorPin = 1; // -- this will be the input from the sending unit
double rawSendingUnitValue;
int percentage;
 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // -- creating LCD instance
LcdBarGraph lbg(&lcd, lcdNumCols, 0, 1);// -- creating bargraph instance, format is (&lcd, lcdNumCols, start X, start Y). So (&lcd, 16, 0, 1) would set the bargraph length to 16 columns and start the bargraph at column 0 on row 1.
 
void setup(){
  Serial.begin(9600);
  // -- initializing the LCD
  lcd.begin(0, lcdNumCols);
  lcd.clear();
  // -- do some delay
  delay(100);
}

double retrieveSendingUnitValue(){
  //here's where the analog input will be read
  return analogRead(2); 
}

int derivePercentage(double rawValue){
  //say min value is 100 and max value is 2000 (TODO: UPDATE WITH ACTUAL VALUES FROM THE SENDING UNIT)
  const double lowestRawValue = 50;
  const double highestRawValue = 2000;
  const double zeroPercent = 0;
  const double oneHundredPercent = 100;
  return map(rawValue, lowestRawValue, highestRawValue, zeroPercent, oneHundredPercent); 
}
 
void loop()
{
  rawSendingUnitValue = retrieveSendingUnitValue();
  //Serial.print("RAW SENDING UNIT VALUE: " + rawSendingUnitValue);

  percentage = derivePercentage(rawSendingUnitValue);
  // Numeric option
  lcd.setCursor(0,0);
  lcd.print("Percentage: ");
  lcd.print(percentage);
  lcd.print("%");

  // Bar chart option
  lbg.drawValue(percentage, 100);

  delay(100);
}