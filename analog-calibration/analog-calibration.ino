const int sensorPin = A0;
const int ledPin = 9;

int sensorValue = 0;
// These values seem swapped but it's done on purpose.
// If we find a minimum lower than 1023, we'll assume that as our new minimum.
// The same reasoning applies to the maximum.
int sensorMin = 1023;
int sensorMax = 0;

void setup() {
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);

    // Calibration time: 5 seconds
    while (millis() < 5000) {
        sensorValue = analogRead(sensorPin);

        if (sensorValue > sensorMax) {
            sensorMax = sensorValue;
        }

        if (sensorValue < sensorMin) {
            sensorMin = sensorValue;
        }
    }

    digitalWrite(13, LOW);
}

void loop() {
    sensorValue = analogRead(sensorPin);
    sensorValue = constrain(sensorValue, sensorMin, sensorMax);
    sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 255);
    analogWrite(ledPin, sensorValue);
}
