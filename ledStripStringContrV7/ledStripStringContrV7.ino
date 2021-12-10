/*
 * 
 * ****Obsolete****
 * 
*/
/* current version is not funtional
*/
// LED pins, pinVALUE, pinFADEvalue
// green 3 1,blue 4 0,red 2 3,power 5 4
int pins[7] = {3, 5, 6, 4, 9, 10, 11};
int ground = 12;
int pinV[7] = {0, 0, 0, 255, 255, 255, 255};
int pinFV[7] = {random(2, 15), random(2, 15), random(2, 15), random(2, 15), random(2, 15), random(2, 15), random(2, 15)};
int pinDelay[7] = {random(10, 60), random(10, 60), random(10, 60), random(10, 60), random(20, 70), random(20, 70), random(20, 70)};
int setColor[] = {7, 8, 12, 13};
int interpin = 2;

void setup() {
  // declare pin 2-5 and 11-13 to be an output:
  //LEDstrip
  pinMode(pins[0], OUTPUT);
  pinMode(pins[1], OUTPUT);
  pinMode(pins[2], OUTPUT);
  pinMode(pins[3], OUTPUT);//power pin LED
  pinMode(pins[4], OUTPUT);
  pinMode(pins[5], OUTPUT);
  pinMode(pins[6], OUTPUT);
  pinMode( ground , INPUT); //ground pin
  pinMode(setColor[0], INPUT);
  pinMode(setColor[1], INPUT);
  pinMode(setColor[2], INPUT);
  pinMode(setColor[3], INPUT);




  //provide power to led strip
  analogWrite(pins[3], 255);
  analogWrite(pins[4], 255);
  analogWrite(pins[5], 255);
  analogWrite(pins[6], 255);

  pinMode(interpin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interpin), interFunction, LOW);
}
void interFunction() {
  Serial.println(" Interupt ");
  Serial.print(digitalRead(A2));
  analogWrite(11, 255);
  analogWrite(3, 255);
  analogWrite(10, 255);
  analogWrite(5, 255);
  analogWrite(9, 255);
  analogWrite(6, 255);
  analogWrite(4, 0);
}
void pinFader(int pin, int value) {

  if (pinV[pin] < value) {
    do {
      pinV[pin] = pinV[pin] + pinFV[pin];
      analogWrite(pins[pin], pinV[pin]);
      if (pinV[pin] > 255) {
        pinV[pin] = 255;
      }
      delay(pinDelay[pin]);
    } while (pinV[pin] < value);
  }
  if (pinV[pin] > value) {
    do {
      pinV[pin] = pinV[pin] - pinFV[pin];
      analogWrite(pins[pin], pinV[pin]);
      if (pinV[pin] < 0 ) {
        pinV[pin] = 0;
      }
      delay(pinDelay[pin]);
    } while (pinV[pin] > value);
  }
}

void setColorS(int x) {

}

void loop() {
  // set the brightness of pin 9 led string and change the strip color:
  //green 2-1, blue 3-0, red 4-2, power 5-3
  //Village LEDS on 13-4, 12-5, 11-6
  int x = 0;
  do {
    if (setColor[x]) {
      setColorS(x);
      x++;
    }
  } while (x < 4);
  pinFader(1, 255); //no green.
  for (x; in 4) {
    if (setColor[x]) {
      setColorS(x);
    }
  }
  pinFader(4, 0);
  for (x; in 4) {
    if (setColor[x]) {
      setColorS(x);
    }
  }
  pinFader(4, 255);
  for (x; in 4) {
    if (setColor[x]) {
      setColorS(x);
    }
  }
  pinFader(2, 255); //no red
  for (x; in 4) {
    if (setColor[x]) {
      setColorS(x);
    }
  }
  pinFader(5, 0);
  for (x; in 4) {
    if (setColor[x]) {
      setColorS(x);
    }
  }
  pinFader(5, 255);
  for (x; in 4) {
    if (setColor[x]) {
      setColorS(x);
    }
  }
  pinFader(1, 0); //green on
  for (x; in 4) {
    if (setColor[x]) {
      setColorS(x);
    }
  }
  pinFader(6, 0);
for x; in 4 :
  if (setColor[x]) {
      setColorS(x);
    }
  pinFader(6, 255);
  for (x; in 4) {
    if (setColor[x]) {
      setColorS(x);
    }
  }
  pinFader(0, 255); //no blue
  for (x; in 4) {
    if (setColor[x]) {
      setColorS(x);
    }
  }
  pinFader(4, 0);
  for (x; in 4) {
    if (setColor[x]) {
      setColorS(x);
    }
  }
  pinFader(4, 255);
  for (x; in 4) {
    if (setColor[x]) {
      setColorS(x);
    }
  }
  pinFader(2, 0);   //red on
  for (x; in 4) {
    if (setColor[x]) {
      setColorS(x);
    }
  }
  pinFader(5, 0);
  for (x; in 4) {
    if (setColor[x]) {
      setColorS(x);
    }
  }
  pinFader(5, 255);
  for (x; in 4) {
    if (setColor[x]) {
      setColorS(x);
    }
  }
  pinFader(1, 255); //no green
  for (x; in 4) {
    if (setColor[x]) {
      setColorS(x);
    }
  }
  pinFader(6, 0);
  for (x in 4) {
    if (setColor[x]) {
      setColorS(x);
    }
  }
  pinFader(6, 255);
  for (x; in 4) {
    if (setColor[x]) {
      setColorS(x);
    }
  }
  pinFader(0, 0);   //blue on
  for (x ;in 4) {
    if (setColor[x]) {
      setColorS(x);
    }
  }
  pinFader(1, 0);   //green
  for (x; in 4) {
    if (setColor[x]) {
      setColorS(x);
    }
  }
}
