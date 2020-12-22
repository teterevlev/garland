#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN            A0
#define NUMPIXELS      300
#define PINK 5
#define PINK_FALL 16
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);
uint16_t sin(uint32_t _x){
  uint8_t x = _x;
  if(x<64){
    return 0;
  }else if(x<128){
    return x-64;
  }else if(x<192){
    return (192-x);
  }else{
    return 0;
  }
}
uint16_t sin1(uint32_t x){
  x = x%256;
  if(x<128){
    return x;
  }else{
    return (255-x);
  }
}
uint32_t t=0;
int16_t a = 32;
int16_t x = 8;
int16_t v = 32;

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
    for(int i=0;i<NUMPIXELS;i++){
      pixels.setPixelColor(i, pixels.Color(255,255,255));
    }
}
uint8_t green;
uint8_t blue;
uint8_t red;
uint32_t nextPinkTime = 3;
uint32_t nextBlackTime = 10;
uint16_t nextPink = 3;
void loop() {
  t++;
  for(int i=0;i<NUMPIXELS;i++){
    red = pixels.getPixelColor(i)>>16;
    int next = i+1;
    if(next < NUMPIXELS && pixels.getPixelColor(next) == 0){
      pixels.setPixelColor(i, 0);
      continue;
    }
    if(t == nextPinkTime && i==nextPink){
      pixels.setPixelColor(i, pixels.Color(255,255,255));
    }else{
      uint16_t color = sin(i*3-t*4/8)*sin(t*4);
      color += sin(i*4+t*17/8)*sin(t*3);
      uint16_t color1 = sin(i*59+t*3/8)*sin(t*2);
      color1+= sin(i*5-t*2/8)*sin(t*3);
      //blue+= sin(i*113/a+t*3/x)*sin(t*47/v);
      //blue+= sin(i*197/a-t*4/x)*sin(t*89/v);
      //blue+= sin(i*67/a+t*3/x)*sin(t*109/v);
      if(color > color1){
        blue = color>>9;
        if(red > 40){
          red -= PINK_FALL;
          green = 0;
          uint8_t b = red>>1;
          if(blue < b) blue = b;
        }else{
          green = color>>8;
          red = 0;
        }
      }else{
        green = color>>7;
        if(red > 40){
          red -= PINK_FALL;
          green = 0;
          uint8_t b = red>>1;
          if(blue < b) blue = b;
        }else{
          blue = color>>6;
          red = 0;
        }
      }
      if(blue<2) blue = 3;
      pixels.setPixelColor(i, pixels.Color(red,green,blue));
    }
  }
  if(t >= nextPinkTime){
    nextPinkTime += random(1, PINK
    );
    nextPink = random(NUMPIXELS);
  }/*
  if(t >= (nextBlackTime)){
    nextBlackTime += random(130, 390);
  }else if(t >= (nextBlackTime-3)){
    pixels.setPixelColor(NUMPIXELS-1, 0);
  }*/
  pixels.show(); // This sends the updated pixel color to the hardware.
}
