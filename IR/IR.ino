#include <pitches.h>
#include <EducationShield.h>

IRArray ir = IRArray(A0, A2, A3);

void setup()
{
  pinMode(A0, INPUT);
  ir.setThreshold(530);
  Serial.begin(9600);
}

void loop()
{
  int reading = ir.readBinary();
  Serial.println(reading);
}
