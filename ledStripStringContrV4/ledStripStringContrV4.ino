/*
 * Change log
 * Seperated houses onto three differant pins
 * added new pins into sequance
 * moved Village LEDs to pins GND,13,12,11
 * added pinFadeValue
 * added print() function
 */

// current version is funtional as 0f 1910 10/7/19

// LED pins, pinVALUE, pinFADEvalue green 3 1,blue 4 0,red 2 3,power 5 4
int pins[7] = {4, 3, 2, 5, 13, 12, 11};
int pinV[7] = {0, 0, 0, 255, 255, 255, 255};
int pinFV[7] = {3, 3, 4, 0, 5, 5, 5};

void setup() {
  // declare pin 2-5 and 11-13 to be an output:
  //LEDstrip
  pinMode(pins[0], OUTPUT);
  pinMode(pins[1], OUTPUT);
  pinMode(pins[2], OUTPUT);
  pinMode(pins[3], OUTPUT);
  pinMode(pins[4], OUTPUT);
  pinMode(pins[5], OUTPUT);
  pinMode(pins[6], OUTPUT);
  
  //provide power to led strip
  analogWrite(pins[3], 255);
  analogWrite(pins[4], 255);
  analogWrite(pins[5], 255);
  analogWrite(pins[6], 255);
  Serial.begin(19200);
}

void print() {
  Serial.print(pinV[1]);
  Serial.print(" green ");
  Serial.print(pinV[2]);
  Serial.print(" red ");
  Serial.print(pinV[3]);
  Serial.print(" power ");
  Serial.print(pinV[0]);
  Serial.println(" Blue ");
  Serial.print(pinV[4]);
  Serial.print(" Village LED one ");
  Serial.print(pinV[5]);
  Serial.print(" Village LED two ");
  Serial.print(pinV[6]);
  Serial.println(" Village LED three ");
}
void pinFader(int pin, int value) {
  if (pinV[pin] < value) {
    do {
      pinV[pin] = pinV[pin] + pinFV[pin];
      analogWrite(pins[pin], pinV[pin]);
      //for information on pin levels
      print();
      delay(70);
    } while (pinV[pin] < value);
  }
  if (pinV[pin] > value) {
    do {
      pinV[pin] = pinV[pin] - pinFV[pin];
      analogWrite(pins[pin], pinV[pin]);
      //for information on pin levels
      print();
      delay(70);
    } while (pinV[pin] > value);
  }
}

void loop() {
  // set the brightness of pin 9 led string and change the strip color:
  analogWrite(pins[3], 255);
  //green 12-1, blue 11-0, red 10-2 
  //Village LEDS on 13-4, 12-5, 11-6 
  pinFader(1, 255); //no green
  pinFader(4, 0);
  pinFader(4, 255);
  pinFader(2, 255); //no red
  pinFader(5, 0);
  pinFader(5, 255);
  pinFader(1, 0); //green on
  pinFader(6, 0);
  pinFader(6, 255);
  pinFader(0, 255); //no blue
  pinFader(4, 0);
  pinFader(4, 255);
  pinFader(2, 0);   //red on
  pinFader(5, 0);
  pinFader(5, 255);
  pinFader(1, 255); //no green
  pinFader(6, 0);
  pinFader(6, 255);
  pinFader(0, 0);   //blue on
  pinFader(1, 0);   //green on
}
