//TX
 
#include <VirtualWire.h>

void setup()
{
    Serial.begin(9600);   // Debugging only
    Serial.println("setup");

    // Initialise the IO and ISR
    vw_set_tx_pin(2);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000); // Bits per sec
}

void loop()
{
  if(Serial.available() > 0) {
    String txt = String(Serial.read());
    int i = (txt.length() + 1);
    char msg[i] = {};
    txt.toCharArray(msg, i);
    Serial.println(msg);
    digitalWrite(13, true); // Flash a light to show transmitting
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13, false); 
    }
}

