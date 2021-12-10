
  //power for led strip and led string
  int power = 13;
  //setup each color of the led stip and give it a fadeable value
  int blue = 12;
  int blueV = 0;
  int red = 10;
  int redV = 0;
  int green = 11;
  int greenV = 0;
  int led = 9;

  //brightness for vilage
  int brightness = 0;
  int fadeAmount = 1;
  int fadeR = 1;
  int fadeB = 3;
  int fadeG = 5;
  
void setup() {
    // declare pin 9-13 to be an output:
  pinMode(power, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(led, OUTPUT);

  //provide power to led strip
  analogWrite(power,255);
}

void loop() {
   // set the brightness of pin 9 led string and change the strip color:
  analogWrite(led, brightness);
  analogWrite(power, 255);
  analogWrite(red, redV);
  analogWrite(green, greenV);
  analogWrite(blue, blueV);

  // change the brightness and led strip color for next time through the loop:
  brightness = brightness + fadeAmount;
  redV = redV + fadeR;
  blueV = blueV + fadeB;
  greenV = greenV + fadeG;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
    
  }
  if (redV <= 0 || redV >= 255) {
    fadeR = -fadeR;
    
  }
  if (greenV <= 0 || greenV >= 255) {
    fadeG = -fadeG;
    
  }
  if (blueV <= 0 || blueV >= 255) {
    fadeB = -fadeB;
    
  }
 
  // wait for x milliseconds to see the dimming effect
  delay(40);
  
}
