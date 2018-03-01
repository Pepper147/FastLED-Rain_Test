#include <FastLED.h>
#include <LEDMatrix.h>
//***************************************************************************************
//Reed Jeandell, March 01 2018
//Fast_LED-Rain_Test_V4
//An adaptation the LED-Rain_Test_V4.  
//Fully functional program that will simulate raindrops falling down the matrix.  
//Added a fadeing value to the LEDs using nscale8.
//***************************************************************************************
#define LED_PIN        7                             //Data Pin for the Arduino
#define COLOR_ORDER    GRB                           //Color order for WS2812B LED strip
#define CHIPSET        WS2812B                       //Model name for LED strip
#define MATRIX_WIDTH   20                            // Set this negative if physical led 0 is opposite to where you want logical 0
#define MATRIX_HEIGHT  24                            // Set this negative if physical led 0 is opposite to where you want logical 0
#define MATRIX_TYPE    HORIZONTAL_ZIGZAG_MATRIX      // See top of LEDMatrix.h for matrix wiring types
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))   //Fast define that will calculate the exact size of any array
#define NUM_LEDS      (MATRIX_WIDTH * MATRIX_HEIGHT) //Defining the total number of LEDS
#define BRIGHTNESS 10                                //Safety Brightness setting just incase i forget to add the power safety function

cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;

//Globals
  int dropNumber = 25;                                  //The number of drops that we want. NOTE: change he array values to match the dropNumber
  int x[25], y[25], yspeed[25], tail[25];               //Initializing arrays for x and y positions, yspeed and trail length 

void setup()
{
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds[0], leds.Size());
  FastLED.setBrightness(BRIGHTNESS);
 // set_max_power_in_volts_and_milliamps(5, 12000);       
  //Safety procotion, stating that i am using 5V 12A power supply (Max)
  Serial.begin(9600);
  Serial.println("The rogram has started");
  FastLED.clear(true);
  delay(500);
  FastLED.showColor(CRGB::Red);
  delay(1000);

  for(byte i = 0; i < dropNumber; i++){               //Loop that will set random values into each array
    x[i] = random(MATRIX_WIDTH);                      //Random spot on the X axis
    y[i] = -random(15, 5);                            //Random spot above the Matrix.  
    yspeed[i] = random(4, 7);                         //Random speed 
    tail[i]   = random(1, 3);                         //Random tail length
  }
}
void loop() {
  Rain();
  FastLED.delay(50);
  FastLED.clear();
}

void fadeall(){                                  //Added function that will dimm all LEDs in each dropNumber
  for(int i = 0; i < dropNumber; i++){
    leds(x[i], y[i]).nscale8(245);
  }
}
void Rain(){
  for(byte i = 0; i < dropNumber; i++){           //Now we begin to send the above information into our respected array
    y[i] = y[i] + yspeed[i];
    if(y[i] > MATRIX_HEIGHT + tail[i]){           //If our y position and our tail length appear off the matrix, then set new values for x, y, y, yspeed and tail
      y[i] = -random(15, 5);
      x[i] =  random(MATRIX_WIDTH);
      yspeed[i] = random( 2, 4);       //2 4 
      tail[i]   = random( 8, 10);      //8 10 
      
      }
    else if (yspeed[i] >=3)     {fadeall();   leds.DrawLine(x[i], y[i], x[i], y[i] + yspeed[i], CHSV(160,255,255));}
    else                        {fadeall();   leds.DrawLine(x[i], y[i], x[i], y[i] + yspeed[i], CHSV(160,255,150));}
    }                           //Using fadeall function, then light up the raindrops, then assigning a color, hue and Brightness value depending on speed.
  }

