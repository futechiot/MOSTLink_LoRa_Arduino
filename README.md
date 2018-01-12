# MOSTLink LoRa library
=========
Getting Started Using the MOSTLink LoRa library


Requirements
----
* MOSTLink LoRa shield dock on arduino
* Arduino Uno connected to computer
* Arduino IDE 1.6.x installed in computer

LoRa Shield Switch(S1): occupied pins
---- 
* S1 on LinkIt: D0(RX), D1(TX), D7(P1), D6(P2), D5(BZ)
* S1 on Arduino: D10(RX), D11(TX), D7(P1), D6(P2), D5(BZ) 

Install MOSTLora to Arduino IDE
----
[MOSTLora]: https://github.com/viWavePublic/MOSTLink_LoRa_Arduino  "MOSTLora lib"
* here [GitHub][MOSTLora]: [Clone or download] -> [Download ZIP]
* Arduino IDE install library: [Sketch] -> [Include Library] -> [Add .ZIP Library] 

Crypto library to encrypt/decrypt, then support security transmission
----
* in "MOSTLora_def.h"
* USE_LIB_CRYPTO_AES128: AES/CBC/NoPadding encrypt/decrypt
* USE_LIB_CRYPTO_HMAC: Challenge-response to check HMAC result
* DEBUG_LORA: show debug log in serial monitor

Examples in Arduino IDE: [File] -> [Examples] -> [installed MOSTLora lib] folder
----
1.  Starter for MOSTLink_Doc/GettingStartedwithMOSTLinkLoRa.pdf  
  - **lora_01_starter**

2.  Humidity & Temperature Sensor: DHT22/DHT11  
  - **lora_02_DHT**
    
3.  Chat between gateway and node  
  - **lora_03_chat** 

4.  ThingSpeak project
  - **lora_04_thingspeak** 

5.  Vinduino project 
  - **lora_05_vinduino**      
        header file: MOSTLora_def.h, unmark "#define USE_VINDUINO", 
        Digit pin for RX/TX, and P1/P2 would be specified correctly.
        D0(RX), D1(TX), D3(P1), D4(P2), A7(BZ)          

6.  Challenge-Response by crypto lib
  - **lora_06_fake** as fake node simulate
        **lora_06_challenge** as challenge-response using HMAC, AES

7.  MediaTek Cloud Sandbox (MCS) as IOT server
  - **lora_07_mcs_starter** for starter
  - **lora_07_mcs_sharecourse** for Sharecourse
  - **lora_07_mcs_usg** for USG 

8.  myDevices Cayenne as IOT server
  - **lora_08_mydevices_usg**

9.  LoRaWAN module
  - **loraWAN_01** GlobalSAT LoRa module, and GTIoT network

10.  use LM-110H1 as 3 mode: LoRaWAN/MOST_p1p2/MOST_AT
  - **lora_aat** LM-110H1 (LM130) switch 3 mode
        LoRaWAN mode: connect to LoRaWAN
        MOST_p1p2 mode: set mode by p1/p2 pin
        MOST_AT: set mode by AT command

Reference
----
* Arduino: https://www.arduino.cc
* MOSTLink: http://www.mostlink.io
* ThingSpeak: https://thingspeak.com
* Vinduino: https://github.com/ReiniervdL/Vinduino
* Cryptographic Library: http://rweather.github.io/arduinolibs/crypto.html
* MCS: https://mcs.mediatek.com
