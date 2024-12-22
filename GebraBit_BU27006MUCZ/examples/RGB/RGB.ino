#include "GebraBit_BU27006MUCZ.h"

GebraBit_BU27006MUCZ BU27006MUCZ;

void setup() {
    Wire.begin();           // Initialize the I2C bus
    Serial.begin(9600);     // Initialize serial communication for debugging

    GB_BU27006MUCZ_initialize(&BU27006MUCZ); // Initialize the BU27006MUCZ sensor
    GB_BU27006MUCZ_Configuration(&BU27006MUCZ); // Configure the BU27006MUCZ sensor
}

void loop() {
    GB_BU27006MUCZ_Get_Data(&BU27006MUCZ); // Read data from the sensor
    
    Serial.print("RED:   ");
    Serial.print(BU27006MUCZ.RED_LUX);
    Serial.println(" lx");

    Serial.print("GREEN: ");
    Serial.print(BU27006MUCZ.GREEN_LUX);
    Serial.println(" lx");

    Serial.print("BLUE:  ");
    Serial.print(BU27006MUCZ.BLUE_LUX);
    Serial.println(" lx");

    delay(2000); // Delay between readings
}
