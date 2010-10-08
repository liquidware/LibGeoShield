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

#ifndef LibGeoShield_h
#define LibGeoShield_h

#include <inttypes.h>

//GeoShield Hardware Types - used for configuring the device
typedef enum {
   GEOSHIELD_HW_STD          = 0,
   GEOSHIELD_HW_WITH_COMPASS = 1,
} GEOSHIELD_HW_T;

class LibGeoShield
{
  private:
    int  GPS_buffIndex;
    float _AccelGSlope;
    int   _AccelGOffset;

  public:
    LibGeoShield(uint8_t GeoShieldType);

    bool CalibrateCompass(void);
    void SleepCompass(void);
    void WakeCompass(void);

    char* readGPS(void);
    int readCompass(void);
    int readAccelX();
    int readAccelY();
    int readAccelZ();
    void setSupply(float supplyVolts);
};

#endif
