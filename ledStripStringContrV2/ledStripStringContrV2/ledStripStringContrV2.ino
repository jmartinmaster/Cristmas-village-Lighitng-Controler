/*
 * Changelog
 * moved LED strip pins into an array
 * moved fade values into an array corisponding with LED strip pin array
 * made pinFader to manage LED fadeing value and output levels
 */

//power for led strip and led string
int power = 13;

//array test for pins and values
//green 12,0 blue 11,1 red 10,2 led 9,3
int pins[4] = {12, 11, 10, 9};
int pinV[4] = {0, 0, 0, 255};

//brightness and fade speed for vilage
int brightness = 0;
int fadeAmount = 1;


void setup() {
  // declare pin 9-13 to be an output:
  pinMode(power, OUTPUT);
  pinMode(pins[0], OUTPUT);
  pinMode(pins[1], OUTPUT);
  pinMode(pins[2], OUTPUT);
  pinMode(pins[3], OUTPUT);

  //provide power to led strip
  analogWrite(power, 255);
  Serial.begin(19200);
}

void pinFader(int pin, int value) {
  if (pinV[pin] < value) {
    do {
      pinV[pin] = pinV[pin] + 5;
      analogWrite(pins[pin], pinV[pin]);

       //for information on pin levels
        Serial.print(pinV[2]);
        Serial.print(" ");
        Serial.println(pinV[1]);
        Serial.print(" ");
        Serial.print(pinV[0]);
        Serial.print(" ");
      delay(50);
    } while (pinV[pin] < value);
  }
  if (pinV[pin] > value) {
    do {
      pinV[pin] = pinV[pin] - 5;
      analogWrite(pins[pin], pinV[pin]);
        //for information on pin levels
      Serial.print(pinV[2]);
      Serial.print(" ");
      Serial.println(pinV[1]);
      Serial.print(" ");
      Serial.print(pinV[0]);
      Serial.print(" ");
       delay(50);
    } while (pinV[pin] > value);
  }
}

void loop() {
  // set the brightness of pin 9 led string and change the strip color:
  analogWrite(pins[3], brightness);
  analogWrite(power, 255);

  // change the brightness and led strip color for next time through the loop:
  brightness = brightness + fadeAmount;
  
//green 12,1 blue 11,0 red 10,2 led 9,3
  pinFader(1, 255); //no green
  pinFader(2, 255); //no red
  pinFader(1, 0); //green on
  pinFader(0, 255); //no blue
  pinFader(2, 0);   //red on
  pinFader(1, 255); //no green
  pinFader(0, 0);   //blue on
  pinFader(1, 0);   //green on
    

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;

  }

  // wait for x milliseconds to see the dimming effect
  delay(40);

}
