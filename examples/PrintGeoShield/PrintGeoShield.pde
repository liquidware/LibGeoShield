/****************************
 * PrintGeoShield
 *  An example sketch for the Liquidware GeoShield
 *  that demonstrates how to forward GPS, Compass,
 *  and 3-axis accelerometer data to the PC via serial @ 57600 baud
 *
 *  Learn more at: http://www.liquidware.com/category/Sensors
 *****************************/
#include <Wire.h>
#include <LibCompass.h>
#include <SoftwareSerial_NB.h>
#include <LibGeoShield.h>

LibGeoShield geo = LibGeoShield(0);
char out[100];

void setup() {
   Serial.begin(57600);  //Open a serial connection to the PC @ 57600 baud
}

void loop() {

   /* Print the GPS data */
   Serial.print(geo.readGPS());

   /* Print the Compass heading, Accel X, Accel Y, Accel Z data */
   sprintf(out, "$GEO,H%d,X%d,Y%d,Z%d\n",
                geo.readCompass(),
                geo.readAccelX(),
                geo.readAccelY(),
                geo.readAccelZ());

   Serial.print(out);
}


