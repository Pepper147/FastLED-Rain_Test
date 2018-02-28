#include <FastLED.h>
#include <LEDMatrix.h>
//***************************************************************************************
//Fast_LED-Rain_Test_V2
//Currently all is working well with this program. We can initialize how many raindrops we want to work with.
//They will all apear in random location and fall at random speeds.  
//Currently have to be carful of how much memory i am using.
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
  int dropNumber = 12;                                  //How many drops we want 
  int x[12], y[12], yspeed[12], tail[12], color[12];    //Initializing arrays for x and y positions, yspeed, trail length, and color  

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
    y[i] = -random(20, 5);                            //Random spot above the Matrix
    yspeed[i] = random(1, 4);                         //Random speed 
    tail[i] = random(1, 4);                           //Random tail length
    color[i] = random8();                             //Random color
  }
}

void loop(){
  Show();
  FastLED.delay(40);
  FastLED.clear();
}
  
void Show(){
  for(byte i = 0; i < dropNumber; i++){               //Now we begin to send the above information into our respected array
    y[i] = y[i] + yspeed[i];                         
    if(y[i] > MATRIX_HEIGHT + tail[i]){               //If our y position and our tail length appear off the matrix, then set new values for x, y, y, speed and tail
      y[i] = -random(20, 5);
      x[i] =  random(MATRIX_WIDTH);
      yspeed[i] = random(1, 4);
      tail[i]   = random(1, 4);
    }
    else{                                            //Draws a line of pixels down the array 
      leds.DrawLine(x[i], y[i], x[i], y[i] + yspeed[i], CRGB::Blue);
     //leds.DrawLine(x[i], y[i], x[i], y[i] + yspeed[i], CHSV(color[i],255,255));         //If you wanted to you can add a random color to each raindrop aswell
    }
  }
}

