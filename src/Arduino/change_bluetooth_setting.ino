#include <SoftwareSerial.h>

#define bluetoothRx 6
#define bluetoothTx 7

SoftwareSerial bluetooth(bluetoothRx, bluetoothTx);

void setup() {
  Serial.begin(9600);
  bluetooth.begin(115200);
  
}

void loop() {

}
