#include "MLPacketGen3.h"
#include "MLutility.h"

////////////////////////////////////////////////////////////////////////////

MLReqLocationPayloadGen::MLReqLocationPayloadGen(uint8_t reportType, uint8_t action, uint16_t ansTypeEx_ResInterval, uint16_t ansTypeEx_DelayTime) :  MLPayloadGen(CMD_REQ_LOCATION, 0, NULL, 0x0C)
{
    _reportType = reportType;
    _action = action;
    _resInterval = ansTypeEx_ResInterval;
    _delayTime = ansTypeEx_DelayTime;
}

int MLReqLocationPayloadGen::getPayload(uint8_t *payload)
{
    // prefix
    int pos = getPayloadPrefix(payload);
    
    payload[pos++] = _reportType;
    payload[pos++] = _action;
    
    // bit1, bit5, add optional extend data field
    if ((_reportType & 0x02) || (_reportType & 0x20))
    {
        uint16_t optResInterval = 0;
        uint16_t optDelayTime = 0;
        if (_reportType & 0x02)
            optResInterval = _resInterval;

        if (_reportType & 0x20)
            optDelayTime = _delayTime;
        
        payload[pos++] = optResInterval & 0xFF;
        payload[pos++] = optResInterval >> 8;

        payload[pos++] = optDelayTime & 0xFF;
        payload[pos++] = optDelayTime >> 8;
    }
    
    // postfix
    pos = getPayloadPostfix(payload, pos);
    return pos;
}

////////////////////////////////////////////////////////////////////////////

MLAnsAlarmPayloadGen::MLAnsAlarmPayloadGen(uint8_t *idAnswerer, uint8_t conditionFlag)
: MLPayloadGen(CMD_ANS_ALARM, 0, NULL, 0x0C)
{
    if (idAnswerer != NULL) {
        memcpy(_idAnswerer, idAnswerer, ML_PK_ID_SIZE);
    }
    _conditionFlag = conditionFlag;
}

int MLAnsAlarmPayloadGen::getPayload(uint8_t *payload)
{
    // prefix
    int pos = getPayloadPrefix(payload);
    
    memcpy(payload + pos, _idAnswerer, ML_PK_ID_SIZE);
    pos += 8;
    
    payload[pos++] = _conditionFlag;
   
    // postfix
    pos = getPayloadPostfix(payload, pos);
    return pos;
}

////////////////////////////////////////////////////////////////////////////
// set member variable by decode payload
void MLReportLocationPayloadGen::setPayload(const uint8_t *payload, int szPayload)
{
    int pos = 3;
  
    long lng = payload[pos+3] << 24 | payload[pos+2] << 16 | payload[pos+1] << 8 | payload[pos];
    _loc.longtitude = payload[pos+3] << 24 | payload[pos+2] << 16 | payload[pos+1] << 8 | payload[pos];
    pos += 4;
    
    _loc.latitude = payload[pos+3] << 24 | payload[pos+2] << 16 | payload[pos+1] << 8 | payload[pos];
    pos += 4;

    _statusGPS = payload[pos];
    pos ++;

    _batteryLevel = payload[pos];
    pos ++;
    
    _dateTime = payload[pos+3] << 24 | payload[pos+2] << 16 | payload[pos+1] << 8 | payload[pos];
    pos += 4;

    char strFmt[128], strInt[16], strLat[16], strLng[16];
    ltoa(_loc.longtitude, strLat, 10);
    ltoa(_loc.latitude, strLng, 10);
    ltoa(_dateTime, strInt, 10);

    Serial.println((long)lng);
    Serial.println((long)_loc.longtitude);

//    debugSerial.print("payload=");
//    MLutility::printBinary(payload, szPayload);
    sprintf(strFmt, "(%ld, %ld), GPS=%d, battery=%d, datetime:%ld %s ======", _loc.latitude, _loc.longtitude, (int)_statusGPS, (int)_batteryLevel, _dateTime, strInt);
    Serial.println(strFmt);
}


////////////////////////////////////////////////////////////////////////////
// set member variable by decode payload
void MLReportBeaconPayloadGen::setPayload(const uint8_t *payload, int szPayload)
{
    int pos = 3;
    memcpy(_uuid, payload + pos, 20);
    pos += 20;
    
    _type = payload[pos];
    pos++;
    
    _rssi = payload[pos];
    pos++;

    _txPower = payload[pos];
    pos++;
    
    _batteryLevel = payload[pos];
    pos++;

    ///////////////////////////
    // output for debug string
    char strFmt[100];
    debugSerial.print("UUID=");
    MLutility::printBinary(_uuid, 20);
    sprintf(strFmt, "typeReport=%d, typeBeacon=%d, rssi=%d, tx=%d, battery=%d", _typeReport,  _typeBeacon, _rssi, _txPower, _batteryLevel);
    debugSerial.println(strFmt);
}
