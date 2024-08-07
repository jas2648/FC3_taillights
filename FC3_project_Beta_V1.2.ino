    /*
  Name:    FC3_project_Beta_V1.1
  Created: 11/15/2023
  Author:  James Sears

  Code and schematic demonstrating how to interface an Arduino with 12V signals
  from a vehicle.
*/

#include <Adafruit_NeoPixel.h>
// Vehicle connection signals
#define R_INDICATOR_SIG 3
#define L_INDICATOR_SIG 2
#define DRL_SIG 4                                                   
// Connections to the LED strips
#define L_INDICATOR_LED_PIN 5
#define R_INDICATOR_LED_PIN 6  
// Number of pixels                                              
#define NUMPIXELS 42
Adafruit_NeoPixel pixels_L = Adafruit_NeoPixel(NUMPIXELS, L_INDICATOR_LED_PIN, NEO_GRB + NEO_KHZ800);// pixel set up
Adafruit_NeoPixel pixels_R = Adafruit_NeoPixel(NUMPIXELS, R_INDICATOR_LED_PIN, NEO_GRB + NEO_KHZ800);// pixel set up



void setup()
{
  
  pixels_L.begin();                                                 //begin the left led strip for use
  pixels_R.begin();                                                 // begin the right led strip for use 
  
  pinMode(R_INDICATOR_SIG, INPUT);                                  //right indicator +5v from car as a signal 
  pinMode(L_INDICATOR_SIG, INPUT);                                  //left indicator +5v from car as a signal 
  pinMode(DRL_SIG, INPUT);                                          // day time running lights signal from car +5v
  
  pinMode(L_INDICATOR_LED_PIN, OUTPUT);                             //left led output 
  pinMode(R_INDICATOR_LED_PIN, OUTPUT);                             //right led output
  bool Static = digitalRead(DRL_SIG); 
  

  
  
 // ######################START UP ANIMATION###############
 if(Static){                                                        //loop only if the DRLs are on
  
  for(int cycles = 0; cycles <= 1 ; cycles++){                      //cycle through the loop twice
    
    
  
  for (int i = 0; i <= NUMPIXELS; i++)                              //i gets the number of pixels and will stay in the loop as long as i is greater than or equal to the value of pixles and will keep incrementing i each instance
              {
               pixels_R.setPixelColor(i, pixels_R.Color(255, 0, 0));//set one pixel to red based on what i is 
               pixels_R.setPixelColor(i-5, pixels_R.Color(0, 0, 0));//send a packet of 5 leds to travel along the strip
               pixels_R.show();                                     //update strip
               pixels_L.setPixelColor(i, pixels_L.Color(255, 0, 0));//set one pixel to red based on what i is 
               pixels_L.setPixelColor(i-5, pixels_L.Color(0, 0, 0));//send a packet of 5 leds to travel along the strip
               pixels_L.show();
               delay(10);                                           //delay 10 ms for smoothness 
              }
  
  
  for (int i = NUMPIXELS; i >= 0; i--)                              //i gets the number of pixels and will stay in the loop as long as i is greater than or equal to the value of pixles and will keep decrementing i each instance
              {
               pixels_R.setPixelColor(i, pixels_R.Color(255, 0, 0));//set one pixel to red based on what i is 
               pixels_R.setPixelColor(i+5, pixels_R.Color(0, 0, 0));//send a packet of 5 leds to travel along the strip
               pixels_R.show();                                     //update strip
               pixels_L.setPixelColor(i, pixels_L.Color(255, 0, 0));//set one pixel to red based on what i is 
               pixels_L.setPixelColor(i+5, pixels_L.Color(0, 0, 0));//send a packet of 5 leds to travel along the strip
               pixels_L.show();                                     //update strip
               delay(10);                                           //delay 10 ms for smoothness 
              }
        }
      
 for (int cycles_1 = 0; cycles_1 <= 2; cycles_1++){
              delay(100);
              pixels_R.fill(pixels_R.Color(255, 0, 0) , 0 , NUMPIXELS);  //fill all pixels with red instantly
              pixels_L.fill(pixels_L.Color(255, 0, 0) , 0 , NUMPIXELS);  //fill all pixels with red instantly
              pixels_L.show();                                           //update left pixels
              pixels_R.show();                                           //update right pixels
              delay(100);                                                //delay 100ms
              pixels_R.clear();                                          //clear right
              pixels_L.clear();                                          //clear left 
              pixels_L.show();                                           //update left pixels
              pixels_R.show();                                           //update right pixels
            } 
      }          
}
void loop()
{
                                                                    //read the indicator signal and save it as a bool each time the loop cycles so that it can get the status of the light each time.
  bool L_input = digitalRead(L_INDICATOR_SIG);
  bool R_input = digitalRead(R_INDICATOR_SIG); 
  bool Static = digitalRead(DRL_SIG);


  
  // ######################Indicators loop###############
          pixels_R.clear();                                         //Clear lights so that the loop runs soomthly 
          pixels_L.clear();                                         //Clear lights so that the loop runs soomthly 
  
  
  // ######################right signal without DRL################## 
  if (Static == 0 &&(R_input && !L_input)) {                      //if the right signal is high and the left signal is low and the static signal is low this loop will be activated 
          for (int i = NUMPIXELS; i >= 0; i--)                     //i gets the number of pixels and will stay in the loop as long as i is greater than or equal to the value of pixles and will keep decrementing i each instance
              {
               pixels_R.setPixelColor(i, pixels_R.Color(255, 0, 0));//set one pixel to red based on what i is 
               pixels_R.show();                                     //update strip
               delay(5);                                           //delay 10 ms for smoothness 
              }
  }

  
  //######################left signal without DRL####################
  else if (Static == 0 && (!R_input && L_input)) {                      //if the left signal is high and the right signal is low and the static signal is low this loop will be activated
         for (int i = NUMPIXELS; i >= 0; i--)                     //i gets the number of pixels and will stay in the loop as long as i is greater than or equal to the value of pixles and will keep decrementing i each instance
              {
               pixels_L.setPixelColor(i, pixels_L.Color(255, 0, 0));//set one pixel to red based on what i is 
               pixels_L.show();                                     //update strip
               delay(5);                                           //delay 10 ms for smoothness 
              }
  }


//#########################Hazards without DRL######################
 else if (Static == 0 && (L_input && R_input)) {                                      //if the left signal is high and the right signal is high this loop will be activated
          for (int i = NUMPIXELS; i >= 0; i--)                       //i gets the number of pixels and will stay in the loop as long as i is greater than or equal to the value of pixles and will keep decrementing i each instance
              {
              pixels_R.setPixelColor(i, pixels_R.Color(255, 0, 0));  //set one pixel to red based on what i is
              pixels_L.setPixelColor(i, pixels_L.Color(255, 0, 0));  //set one pixel to red based on what i is                                   
              pixels_R.show();                                       //update strip
              pixels_L.show();                                       //update strip
              delay(4);                                              //8ms delay for smoothness
              }
  }
  
  // ######################right signal################## 
  else if (!L_input && R_input) {                                        //if the right signal is high and the left signal is low this loop will be activated 
           for (int i = NUMPIXELS; i >= 0; i--)                     //i gets the number of pixels and will stay in the loop as long as i is greater than or equal to the value of pixles and will keep decrementing i each instance
              {
               pixels_R.setPixelColor(i, pixels_R.Color(255, 0, 0));//set one pixel to red based on what i is 
               pixels_R.show();                                     //update strip
               delay(10);                                           //delay 10 ms for smoothness 
              }
  }

  
  //######################left signal####################
  else if (!R_input && L_input) {                                   //if the left signal is high and the right signal is low this loop will be activated
          for (int i = NUMPIXELS; i >= 0; i--)                      //i gets the number of pixels and will stay in the loop as long as i is greater than or equal to the value of pixles and will keep decrementing i each instance
            {
            pixels_L.setPixelColor(i, pixels_L.Color(255, 0, 0));   //set one pixel to red based on what i is
            pixels_L.show();                                        //update strip
            delay(10);                                              //delay 10 ms for smoothness    
            }   
  }

  
 //#########################Hazards######################
 else if (L_input && R_input) {                                      //if the left signal is high and the right signal is high this loop will be activated
          for (int i = NUMPIXELS; i >= 0; i--)                       //i gets the number of pixels and will stay in the loop as long as i is greater than or equal to the value of pixles and will keep decrementing i each instance
              {
              pixels_R.setPixelColor(i, pixels_R.Color(255, 0, 0));  //set one pixel to red based on what i is
              pixels_L.setPixelColor(i, pixels_L.Color(255, 0, 0));  //set one pixel to red based on what i is                                   
              pixels_R.show();                                       //update strip
              pixels_L.show();                                       //update strip
              delay(8);                                              //8ms delay for smoothness
              }
  }

//############################DRL#######################
  else {                                                              //if any other state is reached, this part will run
    
           pixels_R.fill(pixels_R.Color(255, 0, 0) , 0 , NUMPIXELS);  //fill all pixels with red instantly
           pixels_L.fill(pixels_L.Color(255, 0, 0) , 0 , NUMPIXELS);  //fill all pixels with red instantly
           pixels_L.show();                                           //update left pixels
           pixels_R.show();                                           //update right pixels
  }
}                                                                     //end of voidloop()
