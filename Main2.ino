#include "DClock.h"

//define display digit pins
int digit1 = 4;
int digit2 = 5;
int digit3 = 6;
int digit4 = 7;

//define shift register pins
int clockPin = 12;
int dataPin = 11;
int latchPin = 8;

//initialize timer
long startTime;

//define brightness
int brightness = 9;

//define interval
int interval = 1;

//initialize to print byte
int toPrint[] = {0,0,0,0};

//0 for 12 hour, 1 for 24 hour
bool format = 1;

//initialize digital clock
DClock dc = DClock();

//bytes describing the on/off bytes for each number
unsigned char seg_digits[] = {B11111100,  //0
                              B01100000,  //1
                              B11011010,  //2
                              B11110010,  //3
                              B01100110,  //4
                              B10110110,  //5
                              B10111110,  //6
                              B11100000,  //7
                              B11111110,  //8
                              B11100110,  //9
                              B00000000}; //Blank

void setup() {
  //set pins to output
  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);

  digitalWrite(digit1, HIGH);
  digitalWrite(digit2, HIGH);
  digitalWrite(digit3, HIGH);
  digitalWrite(digit4, HIGH);

  //start timer
  startTime = millis();

  //start serial communication;
  Serial.begin(9600);
}

void loop() {
  //check if user asks for different format
  //changes if so
  if(Serial.available() > 0) {
    String tmp = Serial.readString();

    if(tmp == "12") {
      format = 0;
    }
    else if(tmp == "24") {
      format = 1;
    }
  }
  
  //increment clock every time interval is reached
  if(millis() - startTime >= interval) {
    dc.increment();
    startTime = millis();
  }
  
  //print out clock numbers
  displayClock();
}

void displayClock() {    
  if(format) {
    toPrint[3] = dc.get_hours() / 10;
    toPrint[2] = dc.get_hours() % 10;
  }
  else {
    toPrint[3] = (dc.get_hours() % 12) / 10;
    toPrint[2] = (dc.get_hours() % 12) % 10;
  }

  toPrint[1] = dc.get_minutes() / 10;
  toPrint[0] = dc.get_minutes() % 10;

  
    
  digitalWrite(digit1, LOW);
  SRWrite(seg_digits[toPrint[0]]);
  delay(brightness);
  digitalWrite(digit1, HIGH);
  SRWrite(seg_digits[10]);

  digitalWrite(digit2, LOW);
  SRWrite(seg_digits[toPrint[1]]);
  delay(brightness);
  digitalWrite(digit2, HIGH);
  SRWrite(seg_digits[10]);

  digitalWrite(digit3, LOW);
  SRWrite(seg_digits[toPrint[2]]);
  delay(brightness);
  digitalWrite(digit3, HIGH);
  SRWrite(seg_digits[10]);

  digitalWrite(digit4, LOW);
  if(dc.get_ampm() && !format) {
    SRWrite(seg_digits[toPrint[3]] | 1);
  }
  else {
    SRWrite(seg_digits[toPrint[3]]);
  }
  delay(brightness);
  digitalWrite(digit4, HIGH);
  SRWrite(seg_digits[10]);
}

//function to write to the shift register
void SRWrite(byte numberToDisplay) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, numberToDisplay);
  digitalWrite(latchPin, HIGH);
}

