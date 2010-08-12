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

LibCompass compass = LibCompass(COMPASS_HW_GEOSHIELD);
SoftwareSerial_NB gps = SoftwareSerial_NB(GPS_RX_PIN, GPS_TX_PIN);
static char GPS_buff[GPS_BUFF_SIZE];

/******************************************************************************
 * Constructors
 ******************************************************************************/

LibGeoShield::LibGeoShield(uint8_t GeoShieldType) {
  gps.begin(9600);
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
 * readAccelX
 *  Reads the GeoShield's on-board accelerometer
 *
 * @return int - The accelerometer position data
 **********************************************************/
int LibGeoShield::readAccelX(void) {
  return analogRead(0);
}

/**********************************************************
 * readAccelY
 *  Reads the GeoShield's on-board accelerometer
 *
 * @return int - The accelerometer position data
 **********************************************************/
int LibGeoShield::readAccelY(void) {
  return analogRead(1);
}

/**********************************************************
 * readAccelX
 *  Reads the GeoShield's on-board accelerometer
 *
 * @return int - The accelerometer position data
 **********************************************************/
int LibGeoShield::readAccelZ(void) {
  return analogRead(2);
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
