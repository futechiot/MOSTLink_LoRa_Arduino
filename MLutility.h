/*
  __MLutility_h - Library for MOST Link Lora
  MOST-Link utility

  Created by Macbear Chen, September 26, 2016.
  Released into the public domain.
*/

#ifndef __MLutility_h
#define __MLutility_h

#include <Arduino.h>

// common utility
class MLutility {
public:
    static boolean parseGPGGA(const char *GPGGAstr, double &dbLat, double &dbLng);
    
    static int readSerial(char *buf);
};


#endif // __MLutility_h
