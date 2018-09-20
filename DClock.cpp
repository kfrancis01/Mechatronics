#include "DClock.h"

//constructor function 1
//sets clock to 00:00
DClock::DClock() {
  this->hours = 0;
  this->minutes = 0;
  this->apm = 0;
}

//constructor function 2
//sets clock to hour and minute given
DClock::DClock(int hour, int minute) {
  this->hours = hour;
  this->minutes = minute;
  if(hour >= 12) {
    this->apm = 1;
  }
  else {
    this->apm = 0;
  }
}

//gets hours from clock
int DClock::get_hours() {
	return hours;
}

//gets minutes from clock
int DClock::get_minutes() {
	return minutes;
}

//gets the am/pm value
int DClock::get_ampm() {
	return apm;
}

//increments the clock by 1 minute
//rolls over the hours if minutes reach 60
void DClock::increment() {
  minutes++;

  if(minutes >= 60) {
    minutes = 0;
    hours++;
  }

  if(hours >= 24) {
    hours = 0;
  }

  if(hours >= 12) {
    apm = 1;
  }
  else {
    apm = 0;
  }
}
