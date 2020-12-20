
#include <PololuLedStrip.h>
PololuLedStrip<A0> ledStrip;
const uint8_t NUMBER_OF_LEDS = 161;
//const uint8_t NUMBER_OF_STRIPES = 14;
const uint8_t NUMBER_OF_STRIPES = 14;
const uint8_t STEP = 32;
const uint8_t interval = 10;
uint8_t grey[NUMBER_OF_LEDS], j=interval;
//uint8_t stripes[NUMBER_OF_STRIPES] = {4,3,5,14,14,14,12,14,8,6,10,6,6,11};
uint8_t stripes[NUMBER_OF_STRIPES] = {57,53,24,24};
uint8_t sum[NUMBER_OF_STRIPES+1];
uint16_t hyst = 0;
rgb_color colors[NUMBER_OF_LEDS];
void setup()
{
    pinMode(13, OUTPUT);
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
  ledStrip.write(colors, NUMBER_OF_LEDS);
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
        colors[i].green = grey[NUMBER_OF_LEDS-i-1]/5;
        
        colors[i].blue =  grey[NUMBER_OF_LEDS-i-1]/4;
        //Serial.print(c);
        //Serial.print("\t");
  
    }
    //Serial.println();
    
    if(j >= interval){
      j = 0;
      grey[NUMBER_OF_LEDS-1] = 255;
    }else if(grey[NUMBER_OF_LEDS-1] > STEP){
        grey[NUMBER_OF_LEDS-1] -= STEP;
    }else{
        grey[NUMBER_OF_LEDS-1] = 0;
    }
    j++;
    hyst = 0;

  if(analogRead(A3) < 530){
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
  }else{
    digitalWrite(13, LOW);
  }
  delay(50);
}
int8_t isStart(uint8_t n){
  for(uint8_t i=0; i<NUMBER_OF_STRIPES+1; i++){
    if(n < sum[i]) return i-1;
  }
  return -1;
}

