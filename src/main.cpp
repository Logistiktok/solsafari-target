#include <Arduino.h>

#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

// An IR detector/demodulator is connected to GPIO pin 14(D5 on a NodeMCU
// board).
// Note: GPIO 16 won't work on the ESP8266 as it does not have interrupts.
const uint16_t kRecvPin = 5;

IRrecv irrecv(kRecvPin);

decode_results results;

int myIndex = 0;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();  // Start the receiver
  while (!Serial)  // Wait for the serial connection to be establised.
    delay(50);
  Serial.println();
  Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
  Serial.println(kRecvPin);
}

void loop() {
  if (irrecv.decode(&results)) {
    // print() & println() can't handle printing long longs. (uint64_t)
    uint32_t kommando = results.command;
    decode_type_t type = results.decode_type;
    if (kommando == 0x1D && type == RC5) {
      Serial.println(myIndex);
      myIndex++;
    }
    // How to print debug information
    //serialPrintUint64(results.command, HEX);
    irrecv.resume();  // Receive the next value
  }
}