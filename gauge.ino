#include <LiquidCrystal.h>
#include <LcdBarGraph.h>

const byte lcdNumCols = 16;
double rawSendingUnitValue;
int rawPercentage;
int smoothedPercentage;

//SMOOTHING VARIABLES
// Define the number of samples to keep track of. The higher the number, the
// more the readings will be smoothed, but the slower the output will respond to
// the input. Using a constant rather than a normal variable lets us use this
// value to determine the size of the readings array.

// 20 is solid for testing...in production this will likely be much higher, 100 or more perhaps
const int numReadings = 20;

int readings[numReadings]; // the readings from the analog input
int readIndex = 0;         // the index of the current reading
int total = 0;             // the running total
int average = 0;           // the average

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);   // -- creating LCD instance
LcdBarGraph lbg(&lcd, lcdNumCols, 0, 1); // -- creating bargraph instance, format is (&lcd, lcdNumCols, start X, start Y). So (&lcd, 16, 0, 1) would set the bargraph length to 16 columns and start the bargraph at column 0 on row 1.

void setup()
{
    Serial.begin(9600);

    // initializing the LCD
    lcd.begin(0, lcdNumCols);
    lcd.clear();

    // clear smoothing array
    for (int thisReading = 0; thisReading < numReadings; thisReading++)
    {
        readings[thisReading] = 0;
    }
}

double retrieveSendingUnitValue()
{
    // here's where the sending unit analog input will be read
    return analogRead(2);
}

int derivePercentage(double rawValue)
{
    // say min value is 100 and max value is 2000 (TODO: UPDATE WITH ACTUAL VALUES FROM THE SENDING UNIT)
    const double lowestRawValue = 50;
    const double highestRawValue = 2000;
    const double zeroPercent = 0;
    const double oneHundredPercent = 100;
    return map(rawValue, lowestRawValue, highestRawValue, zeroPercent, oneHundredPercent);
}

int smoothPercentage(int rawPercentage)
{
    // subtract the last reading:
    total = total - readings[readIndex];
    // add new reading input to array:
    readings[readIndex] = rawPercentage;
    // add the reading to the total:
    total = total + readings[readIndex];
    // advance to the next position in the array:
    readIndex = readIndex + 1;

    // if we're at the end of the array...
    if (readIndex >= numReadings)
    {
        // ...wrap around to the beginning:
        readIndex = 0;
    }

    // calculate the average:
    average = total / numReadings;

    return average;
}

void loop()
{
    rawSendingUnitValue = retrieveSendingUnitValue();
    rawPercentage = derivePercentage(rawSendingUnitValue);
    smoothedPercentage = smoothPercentage(rawPercentage);

    // numeric display option
    lcd.setCursor(0, 0);
    lcd.print("Percentage: ");
    lcd.print(smoothedPercentage);
    lcd.print("%");

    // bar chart option
    lbg.drawValue(smoothedPercentage, 100);

    delay(100);
}