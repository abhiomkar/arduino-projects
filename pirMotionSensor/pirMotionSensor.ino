/*
   //////////////////////////////////////////////////
   // Making sense of the Parallax PIR sensor's output
   //////////////////////////////////////////////////

   Switches a Relay Board based on the motion sensor from PIR sensor out.

   @author: Abhinay Omkar / abhiomkar (_) gmail (_) com / http://abhiomkar.in
   @date:   19. January 2017
*/

/////////////////////////////

// the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 30;

int pirPin = 2;    // The digital pin connected to the PIR sensor's output
int lightPin = 12;

long unsigned int debounceDelay = 300000; // 5 min
long unsigned int lastMovedTime;

boolean motionState;
boolean lastLightState = LOW;
boolean lightState = HIGH;

void setup() {
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  digitalWrite(pirPin, LOW);
  
  pinMode(lightPin, OUTPUT);
  digitalWrite(lightPin, HIGH);

  // Give the sensor some time to calibrate
  Serial.print("Calibrating sensor ");
  for (int i = 0; i < calibrationTime; i++) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println(" done");
  Serial.println("SENSOR ACTIVE");
  delay(50);
}

void loop() {  
  motionState = digitalRead(pirPin);

  // If motion detected reset lastMovedTime to current time.
  if (motionState == HIGH) {
    lastMovedTime = millis();
  }

  // If last moved time is more than debounce delay turn off the light.
  if ((millis() - lastMovedTime) > debounceDelay) {
    Serial.print("No motion detected for past ");
    Serial.print((int) (debounceDelay / ((long unsigned int) 1000*60)));
    Serial.println(" minutes.");
    lightState = LOW;
  } else {
    lightState = HIGH;
  }

  if (lightState != lastLightState) {
    digitalWrite(lightPin, lightState);
    lastLightState = lightState;
  }
  
  delay(50);
}
