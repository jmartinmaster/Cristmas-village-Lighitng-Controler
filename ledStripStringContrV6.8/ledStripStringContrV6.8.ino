/*
   Change log
   added serial printer
   changed delays to be larger/ fade values smaller
   decreaseing max values
   increased for Village min values
   left power for LEDStrip at 255
   changed position of
      if (pinV[pin] > 255) {
        pinV[pin] = 255;
      }
    so it can catch properly
   6.5 ->6.6
    setup for new arduino for Will and Jordan
   `removed serial printer
    fine tuned fade values
*/
/* current version is funtional as of
    10/19/19 1414
*/
// LED pins, pinVALUE, pinFADEvalue
// green p11 0,blue p10 1,red p6 3,power p8 4
int pins[7] = {9, 10, 11, 4, 3, 5, 6};
int ground = 12;
int interpin=2;
int interRead = A5;
//old pinV[7]= {0, 0, 0, 255, 255, 255, 255};
int pinV[7] = {0, 0, 0, 255, 255, 255, 255};
int pinFV[7] = {random(5, 10), random(5, 10), random(5, 10), random(5, 10), random(5, 10), random(5, 10), random(5, 10)};
int pinDelay[7] = {random(50, 70), random(50, 70), random(50, 70), random(50, 70), random(50, 70), random(50, 70), random(50, 70)};

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


  //provide power to led strip
  analogWrite(pins[3], 255);
  analogWrite(pins[4], 255);
  analogWrite(pins[5], 255);
  analogWrite(pins[6], 255);

  pinMode(interpin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interpin), interFunction, CHANGE);
  pinMode(interRead, INPUT);
  Serial.begin(9600);

}
void interFunction() {

  Serial.println(" Interupt ");
  Serial.print(analogRead(interRead));
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
            if (pinV[pin] > 255) {
        pinV[pin] = 255;
      }
      analogWrite(pins[pin], pinV[pin]);
      printP();
      delay(pinDelay[pin]);
    } while (pinV[pin] < value);
  }
  if (pinV[pin] > value) {
    do {
      pinV[pin] = pinV[pin] - pinFV[pin];
      if (pinV[pin] < 0 ) {
        pinV[pin] = 0;
      }
      analogWrite(pins[pin], pinV[pin]);
      printP();
      delay(pinDelay[pin]);
    } while (pinV[pin] > value);
  }
}
void printP() {
  Serial.print(pinV[2]);
  Serial.print(" ");
  Serial.print(pinV[1]);
  Serial.print(" ");
  Serial.print(pinV[0]);
  Serial.print(" ");
  Serial.print(pinV[3]);
  Serial.print(" ");
  Serial.print(pinV[4]);
  Serial.print(" ");
  Serial.print(pinV[5]);
  Serial.print(" ");
  Serial.print(pinV[6]);
  Serial.print(" ");
  Serial.print(" inter Read ");
  Serial.println(analogRead(interRead));
  
}

void loop() {
  // set the brightness of pin 9 led string and change the strip color:
  //green 2-1, blue 3-0, red 4-2, power 5-3
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
  pinFader(1, 0);   //green  

  
}
