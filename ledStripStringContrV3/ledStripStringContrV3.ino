/*
 * Change log
 * moved LED strip to pins 2,3,4,5
 */
//power for led strip and led string
//obsolete power moved to pin 5-3
//int power = 13;

//array test for pins and values
//green 12,0 blue 11,1 red 10,2 led 9,3
int pins[4] = {3, 4, 2, 5};
int pinV[4] = {0, 0, 0, 255};

//brightness and fade speed for vilage
int brightness = 0;
int fadeAmount = 1;


void setup() {
  // declare pin 9-13 to be an output:
  //power moved to pin 5-3
  //pinMode(power, OUTPUT);
  pinMode(pins[0], OUTPUT);
  pinMode(pins[1], OUTPUT);
  pinMode(pins[2], OUTPUT);
  pinMode(pins[3], OUTPUT);
  analogWrite(pins[3],255);

  //provide power to led strip
  //power moved to pin 5-3
  //analogWrite(power, 255);
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
        Serial.print(pinV[3]);
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
      Serial.print(pinV[3]);
      Serial.print(" ");
       delay(50);
    } while (pinV[pin] > value);
  }
}

void loop() {
  // set the brightness of pin 9 led string and change the strip color:
   //power moved to pin 5-3
   //analogWrite(power, 255);  
//green 12,1 blue 11,0 red 10,2 led 9,3
  pinFader(1, 255); //no green
  pinFader(3, 255);
  pinFader(2, 255); //no red
  pinFader(3, 0);
  pinFader(1, 0); //green on
  pinFader(3, 255);
  pinFader(0, 255); //no blue
  pinFader(3, 0);
  pinFader(2, 0);   //red on
  pinFader(3, 255);
  pinFader(1, 255); //no green
  pinFader(3, 0);
  pinFader(0, 0);   //blue on
  pinFader(3, 255);
  pinFader(1, 0);   //green on
  pinFader(3, 0);
}
