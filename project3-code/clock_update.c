#include "clock.h"

#define MAX_DAY_SECS 24*60*60   // Limit of number of seconds in a day

// Accepts time of day in seconds as an argument and modifies the
// struct pointed at by tod to fill in its hours, minutes,
// etc. fields.  If time_of_day_sec is invalid (negative or larger
// than the number of seconds in a day) does nothing to tod and
// returns 1 to indicate an error. Otherwise returns 0 to indicate
// success. This function DOES NOT modify any global variables
//
// CONSTRAINT: Uses only integer operations. No floating point
// operations are used as the target machine does not have a FPU.
// 
// CONSTRAINT: Limit the complexity of code as much as possible. Do
// not use deeply nested conditional structures. Seek to make the code
// as short, and simple as possible. Code longer than 40 lines may be
// penalized for complexity.
int set_tod_from_secs(int time_of_day_sec, tod_t *tod){
  if(time_of_day_sec < 0 || time_of_day_sec >= MAX_DAY_SECS){ // error checking
    return 1;
  }
  int tod_hours = time_of_day_sec / 3600;
  int ispm = tod_hours >= 12 ? 1 : 0;
  tod_hours = tod_hours % 12;
  tod_hours = tod_hours == 0 ? 12 : tod_hours;
  int tod_minutes = (time_of_day_sec / 60) % 60;
  int tod_seconds = time_of_day_sec % 60;
  tod->hours = tod_hours;
  tod->minutes = tod_minutes;
  tod->seconds = tod_seconds;
  tod->ispm = ispm;

  // tod->hours = time_of_day_sec / 3600;
  // tod->minutes = (time_of_day_sec / 60) % 60;
  // tod->seconds = time_of_day_sec % 60;
  // tod->ispm = ispm;

  return 0;
}
  

int digit_masks[10] = {         // bit masks representing each of the valid digits
  0b0111111,                     // zero
  0b0000110,                     // one 
  0b1011011,                     // two 
  0b1001111,                     // three 
  0b1100110,                     // four 
  0b1101101,                     // five 
  0b1111101,                     // six 
  0b0000111,                     // seven 
  0b1111111,                     // eight 
  0b1101111,                     // nine 
};

#define BLANK   0b0000000                     // blank
#define AM_MASK (0x1 << 28)                   // position of AM bit
#define PM_MASK (0x1 << 29)                   // position of PM bit


// Accepts a tod and alters the bits in the int pointed at by display
// to reflect how the LCD clock should appear. If any fields of tod
// are negative or too large (e.g. bigger than 12 for hours, bigger
// than 59 for min/sec), no change is made to display and 1 is
// returned to indicate an error. Otherwise returns 0 to indicate
// success. This function DOES NOT modify any global variables
//
// May make use of an array of bit masks corresponding to the pattern
// for each digit of the clock to make the task easier.
// 
// CONSTRAINT: Limit the complexity of code as much as possible. Do
// not use deeply nested conditional structures. Seek to make the code
// as short, and simple as possible. Code longer than 85 lines may be
// penalized for complexity.
int set_display_bits_from_tod(tod_t tod, int *display){
  if(tod.hours < 0   || tod.hours > 12 || 
     tod.minutes < 0 || tod.minutes > 59 ||
     tod.seconds < 0 || tod.seconds > 59 ||
     (tod.ispm != 0 && tod.ispm != 1))
  {
    return 1;
  }

  int hr_tens = BLANK;
  if(tod.hours >= 10){
    hr_tens = digit_masks[1];
  }
  int hr_ones = digit_masks[tod.hours % 10];
  int mn_tens = digit_masks[tod.minutes / 10];
  int mn_ones = digit_masks[tod.minutes % 10];
  int ampm = 0;
  if(tod.ispm){
    ampm = PM_MASK;
  }
  else{
    ampm = AM_MASK;
  }

  int state = 0;
  state |= (mn_ones <<  0);
  state |= (mn_tens <<  7);
  state |= (hr_ones << 14);
  state |= (hr_tens << 21);
  state |= ampm;

  *display = state;
  return 0;
}

// Examines the TIME_OF_DAY_SEC global variable to determine hour,
// minute, and am/pm.  Sets the global variable CLOCK_DISPLAY_PORT bits
// to show the proper time.  If TIME_OF_DAY_SEC appears to be in error
// (to large/small) makes no change to CLOCK_DISPLAY_PORT and returns 1
// to indicate an error. Otherwise returns 0 to indicate success.
//
// Makes use of the set_tod_from_secs() and
// set_display_bits_from_tod() functions.
// 
// CONSTRAINT: Does not allocate any heap memory as malloc() is NOT
// available on the target microcontroller.  Uses stack and global
// memory only.
int clock_update(){
  tod_t tod = {};
  int result = set_tod_from_secs(TIME_OF_DAY_SEC, &tod);
  if(result!=0){
    return 1;
  }
  int state = 0;
  set_display_bits_from_tod(tod,&state);
  CLOCK_DISPLAY_PORT = state;
  return 0;
}
