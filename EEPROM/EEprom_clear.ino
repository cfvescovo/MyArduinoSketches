#include <EEPROM.h>

void setup()
{
  // We initialize the LED pin as an output.
  // We will set this pin to HIGH when we will be done.
  pinMode(13, OUTPUT);

  digitalWrite(13, LOW);

  // Iterate through each byte of the EEPROM storage.
  // Instead of setting the size manually, we use the value provided by EEPROM.length()
  // as every Arduino board has its own EEPROM size.
  for (int i = 0; i < EEPROM.length(); i++)
  {
    // We set each byte to 0.
    EEPROM.write(i, 0);
  }

  // We turn the LED on when we're done.
  digitalWrite(13, HIGH);
}

void loop()
{
  // Nothing here
}
