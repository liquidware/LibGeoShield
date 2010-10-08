/*
  LibGeoShield.cpp - Liquidware GeoShield Sensor library for Arduino

  GeoShield - The Liquidware GeoShield is an integrated Arduino module with built-in
              GPS, 3-Axis Accelerometer, and Digital Compass sensors
              Learn more at http://www.liquidware.com/category/Sensors

  Copyright (c) 2010 Christopher Ladden All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/******************************************************************************
 * Includes
 ******************************************************************************/

#include <string.h>
#include <SoftwareSerial_NB.h>
#include <LibCompass.h>
#include "WConstants.h"
#include "LibGeoShield.h"


/******************************************************************************
 * Definitions
 ******************************************************************************/

#define GPS_RX_PIN 4
#define GPS_TX_PIN 5
#define GPS_BUFF_SIZE 528
#define G_SLOPE_5V	10.18
#define G_OFFSET_5V	3437 

LibCompass compass = LibCompass(COMPASS_HW_GEOSHIELD);
SoftwareSerial_NB gps = SoftwareSerial_NB(GPS_RX_PIN, GPS_TX_PIN);
static char GPS_buff[GPS_BUFF_SIZE];

/******************************************************************************
 * Constructors
 ******************************************************************************/

LibGeoShield::LibGeoShield(uint8_t GeoShieldType) {
  gps.begin(9600);

  _AccelGSlope = G_SLOPE_5V;  //If different supply, please calibrate
  _AccelGOffset = G_OFFSET_5V; 
}

/******************************************************************************
 * Global Functions
 ******************************************************************************/

/**********************************************************
 * readGPS
 *  Used to read the entire GPS sensor output into a local buffer
 *
 * @return char* - A pointer to the GPS data
 **********************************************************/
char* LibGeoShield::readGPS(void) {
  char c;

  GPS_buffIndex = 0;
  memset(GPS_buff,0,GPS_BUFF_SIZE);
  while (1) {
    c = gps.read();
    if (c == -1) {
      break;
    }
    GPS_buff[GPS_buffIndex] = (char)c;
    GPS_buffIndex++;
  }

  return &GPS_buff[0]; //pass back a pointer to the entire buffer
}

/**********************************************************
 * readCompass
 *  Reads the GeoShield's on-board compass
 *
 * @return int - The compass heading in degrees (0-360)
 **********************************************************/
int LibGeoShield::readCompass(void) {
  return (int)compass.GetHeading();
}

/**********************************************************
 * setSupply
 *  Set the Arduino's voltage supply. Used 
 *  for accelerometer volts to mg's conversion accuracy
 *
 * float supplyVolts - The measured voltage of 
 *                     the AREF pin, eg. 4.97
 **********************************************************/
void LibGeoShield::setSupply(float supplyVolts) {
  _AccelGSlope = (supplyVolts / 5.00) * G_SLOPE_5V;
}

/**********************************************************
 * readAccelX
 *  Reads the GeoShield's on-board accelerometer
 *
 * @return int - The accelerometer position data 
 *			 in mg (thousands of a g)
 **********************************************************/
int LibGeoShield::readAccelX(void) {
  float val;

  val = _AccelGSlope * analogRead(0) - _AccelGOffset;
  return (int)val;
}

/**********************************************************
 * readAccelY
 *  Reads the GeoShield's on-board accelerometer
 *
 * @return int - The accelerometer position data 
 *			 in mg (thousands of a g)
 **********************************************************/
int LibGeoShield::readAccelY(void) {
  float val;

  val = _AccelGSlope * analogRead(1) - _AccelGOffset;
  return (int)val;
}

/**********************************************************
 * readAccelZ
 *  Reads the GeoShield's on-board accelerometer
 *
 * @return int - The accelerometer position data 
 *			 in mg (thousands of a g)
 **********************************************************/
int LibGeoShield::readAccelZ(void) {
  float val;

  val = _AccelGSlope * analogRead(2) - _AccelGOffset;
  return (int)val;
}

//Export the compass functions
bool LibGeoShield::CalibrateCompass(void) {
  return compass.Calibrate();
}

void LibGeoShield::SleepCompass(void) {
  compass.Sleep();
}

void LibGeoShield::WakeCompass(void) {
  compass.Wake();
}
