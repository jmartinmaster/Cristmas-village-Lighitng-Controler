/*
   Change log 6.8 -> 7.1.0
   Changed from atmega328 to atmega2560
   Added analog pins to read from
   Added function for reading analog pins
   Added function for catinc out of bounds readings
   Added Speed ability
   Added brightness ability
   Added RGB control from analog read
   Added Fountain
   Added function to write all pins when a pin changes so any and all pin changes are written

   NOTES:
   Changing documentation for clarification. (New/more comments for what does what
*/
/* current version is funtional as of
    NOT TESTED
*/

// Power/Ground pins: RGB, +5V, Village 1, Village 2, Village 3 VIA MOSFET(not powered or grounding to the arduino/2560 itself)
// Red pin D4, Green pin D5, Blue pin D6, 5 volt power pin D7, Village rail 1(5V+) pin D44, Village rail 2(GND) pin D45, Village rail 3(5V+) Pin D46
int pins[7] = {4, 5, 6, 7, 44, 45, 46};

//int ground = 12; Removed
int interpins[6] = {2, 3, 18, 19, 20, 21};

//pinV is a holder for any analogRead to write to
int pinV[7] = {0, 0, 0, 255, 255, 255, 255};

//pinFV manipulates how much value to remove/add when chaning pin state(Primarily used in pinFader)
int pinFV[7] = {random(5, 10), random(5, 10), random(5, 10), random(5, 10), random(5, 10), random(5, 10), random(5, 10)};

//pinDelay slows down how fast pinFader can subtract or add to the current pinV[#] before preformin analogWrite
int pinDelay[7] = {random(50, 70), random(50, 70), random(50, 70), random(50, 70), random(50, 70), random(50, 70), random(50, 70)};

void setup() {
  // declare pins[0-6] to be an output:
  //LEDstrip
  pinMode(pins[0], OUTPUT);//RGB Red
  pinMode(pins[1], OUTPUT);//RGB Green
  pinMode(pins[2], OUTPUT);//RGB Blue
  pinMode(pins[3], OUTPUT);//power pin LED
  pinMode(pins[4], OUTPUT);//Village rail 1
  pinMode(pins[5], OUTPUT);//Village rail 2 GND
  pinMode(pins[6], OUTPUT);//Village rail 3


  //provide power to led strip
  analogWrite(pins[3], 255);
  analogWrite(pins[4], 255);
  analogWrite(pins[5], 255);
  analogWrite(pins[6], 255);

  //setup for interupt pins
  pinMode(interpins[0], INPUT);
  pinMode(interpins[1], INPUT);
  pinMode(interpins[2], INPUT);
  pinMode(interpins[3], INPUT);
  pinMode(interpins[4], INPUT);
  pinMode(interpins[5], INPUT);

  //attaching interupt pins to their methods
  attachInterrupt(digitalPinToInterrupt(interpins[0]), interFunctionToggle, RISING);
  attachInterrupt(digitalPinToInterrupt(interpins[1]), interFunctionFountain, RISING);

  //Open a serial com for debuging (will print pin values, pin fade values, delays, and pin states/values
  Serial.begin(9600);

}
void interFunctionFountain() {

}
void interFunctionToggle() {
  //Setup hold loop to wait for button press to release (off/on)
  Serial.println(" Interupt ");
  analogWrite(11, 255);
  analogWrite(3, 255);
  analogWrite(10, 255);
  analogWrite(5, 255);
  analogWrite(9, 255);
  analogWrite(6, 255);
  analogWrite(4, 0);
}
int aRead(int pinNum) {
  int readNum = 0;
  return readNum;

}
void pinFader(int pin, int value) {

  aRead(A2);

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
