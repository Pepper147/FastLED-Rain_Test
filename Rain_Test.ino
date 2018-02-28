#include <FastLED.h>
#include <LEDMatrix.h>
//***************************************************************************************
//Trying to create a Rain animation on the 20x24 LED matrix.
//So far i have been able to get a single raindrop to fall down the matrix starting from a random Height and Width.
//I am having trouble getting multiple raindrops to fall at the same time. 
//I have been using this youTube video as a source of Reference on some of the problem solving that is taking place.
//https://www.youtube.com/watch?v=KkyIDI6rQJI&t=265s
// 
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
  int x     = random(0 , 19);                        //Starts the raindrop on a random X position 
  float y   = random(-40, -20);                      //Starts the raindrop on a random Y poistion 
                                                     //Placed "above" the matrix so that they fall into the matrix at different times)
  int ySpeed = random(1, 5);                         //Adding a speed variable for how fast the LEDs travel down the matrix


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
}

void loop(){
  Show();
  FastLED.delay(40);
  FastLED.clear();
}
  
void Show(){
  y = y + ySpeed;                           //y position = current value of y + the random speed variable 
  if(y > leds.Height()+2){                  //If the y value exceeds the height of the matrix, then give y a new value 
    y = random(-40, -20);
    }
  else {
  leds.DrawLine(x ,y , x , y + 2, CRGB::Blue);      //Draw a line from (x0, y0) to (x0, y0+2) The y+2 will make the raindrop 3 pixels tall
  }
}
