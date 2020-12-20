
#include <PololuLedStrip.h>
//const uint8_t STRIPE_LENGTH[] = {15,13,13,13,13,13,11,13,7,5,9,5,6,10};
//const uint8_t STRIPE_INDEX[] = {0,15,28,41,54,67,80,91,104,111,116,125,130,136};
// 111 + 35
// Create an ledStrip object and specify the pin it will use.
PololuLedStrip<12> ledStrip;
const uint8_t NUMBER_OF_LEDS = 9;
//const uint8_t NUMBER_OF_STRIPES = 14;
const uint8_t NUMBER_OF_STRIPES = 14;
const uint8_t STEP = 16;
const uint8_t interval = 10;
uint8_t grey[NUMBER_OF_LEDS], j=interval;
//uint8_t stripes[NUMBER_OF_STRIPES] = {4,3,5,14,14,14,12,14,8,6,10,6,6,11};
uint8_t stripes[NUMBER_OF_STRIPES] = {56,54,24,23};
uint8_t sum[NUMBER_OF_STRIPES+1];

volatile rgb_color colors[NUMBER_OF_LEDS];
void setup()
{
  //Serial.begin(115200);
  //Serial.println("FF");
  sum[0] = 0;
  for(uint8_t i=0; i<NUMBER_OF_STRIPES+1; i++){
    sum[i+1] = sum[i] + stripes[i];
  }
  for(uint8_t i=0; i<160; i++){
    //colors[i] = rgb_color(0,0,0);
  }
  //ledStrip.write(colors, 160);
  //Serial.println("FF");
}

void loop()
{
  for(uint8_t i=0; i<NUMBER_OF_LEDS; i++){
      if(i < NUMBER_OF_LEDS-1){
          grey[i] = grey[i+1];
      }
      int8_t is = isStart(i);
      float red = (i-sum[is]);
      red = red/stripes[is];
      float blue;
      if(red <0.5){
          blue = 0.5 - red;
      }else{
          blue = 0;
      }
      colors[i].red = red*grey[i]/2;
      
      colors[i].blue =  blue*grey[i];
      //Serial.print(c);
      //Serial.print("\t");

  }
  ledStrip.write(colors, NUMBER_OF_LEDS);
  //Serial.println();
  delay(50);
  
  if(j >= interval){
    j = 0;
    grey[NUMBER_OF_LEDS-1] = 255;
  }else if(grey[NUMBER_OF_LEDS-1] > STEP){
      grey[NUMBER_OF_LEDS-1] -= STEP;
  }else{
      grey[NUMBER_OF_LEDS-1] = 0;
  }
  j++;

}
int8_t isStart(uint8_t n){
  for(uint8_t i=0; i<NUMBER_OF_STRIPES+1; i++){
    if(n < sum[i]) return i-1;
  }
  return -1;
}

