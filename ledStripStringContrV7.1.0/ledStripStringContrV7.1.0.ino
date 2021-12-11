/*
   Change log 6.8 -> 7.1.0

   *************************************
   Changed from atmega328 to atmega2560
   *************************************


   Added analog pins to read from
   Added function for reading analog pins (aInRead()0
   Added function for cathing out of bounds readings (catch());

   Added Speed ability via analog read
   Added brightness ability via analog read
   Added RGB control via analog read

   Added Fountain button pin (Interrupt 3)
   Added function to write all pins when a pin changes so any and all pin changes are written

   Change interFunctionToggle to turn "on"/"off" system by setting up hold(hn) to stop loop()

   Moved strings to flash to save space for later

   Removed unused methods and variables.

   NOTES:
   Changing documentation for clarification. (New/more comments for what does what
*/
/* current version is funtional as of
    NOT TESTED
*/

// Power/Ground pins: RGB, +5V, Village 1, Village 2, Village 3 VIA MOSFET(not powered or grounding to the arduino/2560 itself)
// Red pin D4, Green pin D5, Blue pin D6, 5 volt power pin D7, Village rail 1(5V+) pin D44, Village rail 2(GND) pin D45, Village rail 3(5V+) Pin D46
const byte pins[7] = {4, 5, 6, 7, 44, 45, 46};

//Fountain power pin
const byte fount = 14;
//interrupt pins
const byte interpins[6] = {2, 3, 18, 19, 20, 21};

//pinV is a holder for any analogRead to write to
int pinV[7] = {0, 0, 0, 255, 255, 255, 255};

//pinFV manipulates how much value to remove/add when chaning pin state(Primarily used in pinFader)
int pinFV[7] = {random(5, 10), random(5, 10), random(5, 10), random(5, 10), random(5, 10), random(5, 10), random(5, 10)};

//pinDelay slows down how fast pinFader can subtract or add to the current pinV[#] before preformin analogWrite
int pinDelay[7] = {random(50, 70), random(50, 70), random(50, 70), random(50, 70), random(50, 70), random(50, 70), random(50, 70)};

//Analog input pins
const byte aIn[7] = {A0, A1, A2, A3, A4, A5, A6};

//int for toggling all on/off
int hn = 1;
int hnR = 0;

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
  pinMode(fount, OUTPUT);//Fountain pin


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
  Serial.begin(115200);

}

void interFunctionFountain() {
  if (digitalRead(fount)) {
    digitalWrite(fount, LOW);
  }
  if (digitalRead(!fount)) {
    digitalWrite(fount, HIGH);
  }

}
void interFunctionToggle() {
  //Setup hold loop to wait for button press to release (off/on)
  Serial.println(" Interupt ");
  analogWrite(pins[0], 0);
  analogWrite(pins[1], 0);
  analogWrite(pins[2], 0);
  analogWrite(pins[3], 0);
  analogWrite(pins[4], 0);
  analogWrite(pins[5], 0);
  analogWrite(pins[6], 0);

  if (hnR == 1) {
    hn = 0;
  }
  else {
    hn = 1;
  }
  hold(hn);
}
void hold(int x) {
  do {
    delay(10);
  } while (x == 1);
  hnR = 1;
}
void pinWrite() {
  analogWrite(pins[0], pinV[0]);
  analogWrite(pins[1], pinV[0]);
  analogWrite(pins[2], pinV[0]);
  analogWrite(pins[3], pinV[0]);
  analogWrite(pins[4], pinV[0]);
  analogWrite(pins[5], pinV[0]);
  analogWrite(pins[6], pinV[0]);
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
      pinWrite();
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
      pinWrite();
      printP();
      delay(pinDelay[pin]);
    } while (pinV[pin] > value);
  }
}
void printP() {
  Serial.print(F(" pinV 0 "));
  Serial.print((analogRead(pinV[0])));
  Serial.print(F(" pinV 1 "));
  Serial.print(analogRead(pinV[1]));
  Serial.print(F(" pinV 2 "));
  Serial.print(analogRead(pinV[2]));
  Serial.print(F(" pinV 3 "));
  Serial.print(analogRead(pinV[3]));
  Serial.print(F(" pinV 4 "));
  Serial.print(analogRead(pinV[4]));
  Serial.print(F(" pinV 5 "));
  Serial.print(analogRead(pinV[5]));
  Serial.print(F(" pinV 6 "));
  Serial.print(analogRead(pinV[6]));
  Serial.print(F(" fountain "));
  Serial.println(digitalRead(14));
}

void loop() {

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
