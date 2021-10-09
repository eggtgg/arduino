#include <SoftwareSerial.h>

#define MYPORT_TX 12
#define MYPORT_RX 13

SoftwareSerial myPort;

[...]

Serial.begin(115200); // Standard hardware serial port

myPort.begin(38400, SWSERIAL_8N1, MYPORT_RX, MYPORT_TX, false);
if (!myPort) { // If the object did not initialize, then its configuration is invalid
  Serial.println("Invalid SoftwareSerial pin configuration, check config"); 
  while (1) { // Don't continue with invalid configuration
    delay (1000);
  }
} 

[...]
