#include "TibuBoard.h"
#include "BasicFunctions.h"
#include "USBSerial.h"
#include <stdio.h>
#include <math.h>
#include "WString.h"


/*#define HIGH 0x1
#define LOW  0x0*/

/*#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2*/

#define true 0x1
#define false 0x0

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105

#define SERIAL  0x0
#define DISPLAY 0x1

#define LSBFIRST 0
#define MSBFIRST 1

#define CHANGE 1
#define FALLING 2
#define RISING 3


void setup(void);
void loop(void);

//WMATH prototypes
// WMath prototypes
long random(long);
long random(long, long);
void randomSeed(unsigned int);
long map(long, long, long, long, long);
