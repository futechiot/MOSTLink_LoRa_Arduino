//////////////////////////////////////////////////////
// This sample code is used for ShareCourse on MOSTLink protocol
//
//
//////////////////////////////////////////////////////

#include "MOSTLora.h"
#include "MLutility.h"

#if !defined(__LINKIT_ONE__)
#include <MemoryFree.h>
#endif // __LINKIT_ONE__

MOSTLora lora;
#include <Grove_LED_Bar.h>
Grove_LED_Bar bar(3, 2, false);

int szBuf = 0;
byte buf[100] = {0};


//char *strDevice = "DyoERH4D,VlnyAVKNL60CxZb1";
//char *strDevice = "DLKy51TU,VlnyAVKNL60CxZb1";
char *strDevice = "DLKy51TU,Z98z3UKrZR4tcEPX";
const char *token = "ANALOG_CONTROL";

// callback for rece data
void funcCustomRece(unsigned char *data, int szData)
{
#if !defined(__LINKIT_ONE__)
    Serial.print(F(" Free mem:"));
    Serial.println(freeMemory());
#endif // __LINKIT_ONE__
  
  debugSerial.print("funcCustomRece= ");
  MLutility::printBinary(data, szData);
}
void funcPacketReqData(unsigned char *data, int szData)
{
  memcpy(buf, data, szData);  
  buf[szData] = 0;
  debugSerial.print("ReqData= ");
  debugSerial.println((const char*)buf);
}

void funcPacketNotifyMcsCommand(unsigned char *data, int szData)
{
  memcpy(buf, data, szData);  
  buf[szData] = 0;
  debugSerial.print("NotifyMcsCommand= ");
  debugSerial.println((const char*)buf);

  if (strstr(buf, token) == buf) {
    char *strVal = buf + strlen(token) + 1;
    int nVal = atoi(strVal);
    bar.setLevel(nVal / 10);
  }
}

void setup() {
  Serial.begin(9600);  // use serial port for log monitor
  // bar-meter
  bar.begin();
  bar.setLevel(3);
    
  lora.begin();
  // custom LoRa config by your environment setting
//  lora.writeConfig(915555, 0, 0, 7, 5);
  lora.setMode(E_LORA_NORMAL);         // E_LORA_NORMAL

  delay(1000);
  lora.sendData("Hi, MCS.");

  // custom callback
  lora.setCallbackReceData(funcCustomRece);
  lora.setCallbackPacketReqData(funcPacketReqData);
  lora.setCallbackPacketNotifyMcsCommand(funcPacketNotifyMcsCommand);

  // login MCS
  lora.sendPacketReqLoginMCS(strDevice, strlen(strDevice));
}

void loop() {
  lora.run();

  delay(10);

  // command to send
  if (Serial.available())
    inputBySerial();
}

void inputBySerial()
{
  int countBuf = MLutility::readSerial((char*)buf);
  if (countBuf > 1) {
    String strCmd = strDevice;
    buf[countBuf] = 0;
    if (buf[0] == '/')
    {
      if (buf[1] == '1') {
        lora.sendPacketReqLoginMCS(strDevice, strlen(strDevice));
      }
      else if (buf[1] == '2') {
        strCmd += ",TEMPERATURE,,20.8";
        lora.sendPacketSendMCSCommand(strCmd.c_str(), strCmd.length());
      }
      else if (buf[1] == '3') {
        strCmd += ",TEMPERATURE,,23.9";
        lora.sendPacketSendMCSCommand(strCmd.c_str(), strCmd.length());
      }
     else if (buf[1] == '9') {
        lora.sendPacketSendMCSCommand(buf + 2, strlen(buf + 2));
      }
    }
  }  
}
