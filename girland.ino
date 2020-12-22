#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN            A0
#define NUMPIXELS      300
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
uint16_t sin(uint32_t x){
  x = x%256;
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
}
uint8_t green;
uint8_t blue;
uint8_t red;
uint32_t nextPinkTime = 3;
uint16_t nextPink = 3;
void loop() {
  t++;
  for(int i=0;i<NUMPIXELS;i++){
    red = pixels.getPixelColor(i)>>16;
    if(t == nextPinkTime && i==nextPink){
      pixels.setPixelColor(i, pixels.Color(255,255,255));
    }else{
      uint16_t color = sin(i*23/a-t*11/x)*sin(t*73/v);
      color += sin(i*19/a+t*17/x)*sin(t*37/v);
      //color+= sin(i*59/a+t*7/x)*sin(t*223/v);
      //color+= sin(i*337/a-t*23/x)*sin(t*179/v);
      //blue+= sin(i*113/a+t*3/x)*sin(t*47/v);
      //blue+= sin(i*197/a-t*4/x)*sin(t*89/v);
      //blue+= sin(i*67/a+t*3/x)*sin(t*109/v);
      blue = color>>7;
      if(red > 40){
        red -= 16;
        green = 0;
        uint8_t b = red>>1;
        if(blue < b) blue = b;
      }else{
        green = color>>6;
        red = 0;
      }
      if(blue<2) blue = 2;
      pixels.setPixelColor(i, pixels.Color(red,green,blue));
    }
  }
  if(t >= nextPinkTime){
    nextPinkTime += random(1, 250);
    nextPink = random(NUMPIXELS);
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
}
