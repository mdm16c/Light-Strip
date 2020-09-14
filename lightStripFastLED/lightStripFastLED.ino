#include <IRremote.h>
#include <FastLED.h>

// IR pin + setup IR reciever
const int RECV_PIN = 8;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

//FastLED Neopixel setup
#define NUMPIXELS 150
#define PIN 6
CRGB leds[NUMPIXELS];
int brightnessDelta = 4;
int brightness = 125;
int colorDelta = 2;
int effect = 3;
int lastEffect = -1;

//animation vars
bool diy1Playing = false;
CRGB LED0Color = CRGB(0, 0, 0);
int diy2 = 0;
int diy3 = 0;
int diy4 = 0;
int diy5Counter = 0;
bool jump3Switch = false;
bool jump7Switch = false;
CRGB jump7Color1 = CRGB(0,0,0);
CRGB jump7Color2 = CRGB(0,0,0);
CRGB jump7Color3 = CRGB(0,0,0);
CRGB jump7Color4 = CRGB(0,0,0);
CRGB jump7Color5 = CRGB(0,0,0);
CRGB jump7Color6 = CRGB(0,0,0);
CRGB jump7Color7 = CRGB(0,0,0);
CRGB jump7Color8 = CRGB(0,0,0);
CRGB jump7Color9 = CRGB(0,0,0);
CRGB jump7Color10 = CRGB(0,0,0);
int quick = 0;
int slow = 0;
int chromaDelta = 6;
int fade3 = 125;
bool fade3Switch = false;
CRGB fade7Color = CRGB(0,0,0);
bool playing = true;

//colors
//accepts colors in green, red, blue
CRGB red = CRGB(0, 255, 0);
CRGB green = CRGB(255, 0, 0);
CRGB lightGreen = CRGB(205, 50, 50);
CRGB blue = CRGB(0, 0, 255);
CRGB lightBlue = CRGB(128, 0, 255);
CRGB skyBlue = CRGB(206, 135, 250);
CRGB lightSkyBlue = CRGB(210, 150, 50);
CRGB turquoise = CRGB(204, 0, 102);
CRGB lightTurquoise = CRGB(224, 64, 208);
CRGB darkTurquoise = CRGB(50, 90, 139);
CRGB white = CRGB(254, 254, 254);
CRGB darkOrange = CRGB(75, 255, 0);
CRGB orange = CRGB(100, 255, 0);
CRGB lightOrange = CRGB(125, 255, 0);
CRGB yellow = CRGB(200, 255, 0);
CRGB purple = CRGB(0, 153, 153);
CRGB lightPurple = CRGB(0, 204, 102);
CRGB pink = CRGB(105, 255, 180);
CRGB lightPink = CRGB(200, 255, 50);
CRGB darkPink = CRGB(50, 255, 100);
CRGB indigo = CRGB(0, 75, 130);

void setup() {
  // sanity check
  delay(2000);

  // setup IR reciever
  Serial.begin(9600);
  irrecv.enableIRIn();

  //blink arduino LED on input recieved
  //irrecv.blink13(true);

  //FastLED NeoPixel
  FastLED.addLeds<WS2812B, PIN>(leds, NUMPIXELS);
  FastLED.clear();
  FastLED.setBrightness(brightness);
  FastLED.show();
}

void loop() {
  if (effect != -1) {
    switch (effect) {

      //brightness up [1][1]
      case 0:
        if (brightness + brightnessDelta <= 255) {
          brightness += brightnessDelta;
        }
        else {
          brightness = 255;
        }
        FastLED.setBrightness(brightness);
        if (lastEffect >= 30 && playing) {
          effect = lastEffect;
        }
        else {
          effect = -1;
        }
        FastLED.show();
        break;

      //brightness down [1][2]
      case 1:
        if (brightness - brightnessDelta >= 1) {
          brightness -= brightnessDelta;
        }
        else {
          brightness = 1;
        }
        FastLED.setBrightness(brightness);
        if (lastEffect >= 30 && playing) {
          effect = lastEffect;
        }
        else {
          effect = -1;
        }
        FastLED.show();
        break;

      //play/pause [1][3]
      case 2:
        //pause
        if (playing) {
          playing = false;
          effect = -1;
        }
        //play
        else {
          playing = true;
          effect = lastEffect;
        }
        break;

      //power [1][4]
      case 3:
        FastLED.clear();
        FastLED.show();
        effect = -1;
        lastEffect = 3;
        break;

      //red R [2][1]
      case 4:
        FastLED.clear();
        fill_solid(leds, NUMPIXELS, red);
        FastLED.show();
        effect = -1;
        lastEffect = 4;
        break;

      //green G [2][2]
      case 5:
        FastLED.clear();
        fill_solid(leds, NUMPIXELS, green);
        FastLED.show();
        effect = -1;
        lastEffect = 5;
        break;

      //blue B [2][3]
      case 6:
        FastLED.clear();
        fill_solid(leds, NUMPIXELS, blue);
        FastLED.show();
        effect = -1;
        lastEffect = 6;
        break;

      //white W [2][4]
      case 7:
        FastLED.clear();
        fill_solid(leds, NUMPIXELS, white);
        FastLED.show();
        effect = -1;
        lastEffect = 7;
        break;

      //dark orange [3][1]
      case 8:
        FastLED.clear();
        fill_solid(leds, NUMPIXELS, darkOrange);
        FastLED.show();
        effect = -1;
        lastEffect = 8;
        break;

      //light green [3][2]
      case 9:
        FastLED.clear();
        fill_solid(leds, NUMPIXELS, lightGreen);
        FastLED.show();
        effect = -1;
        lastEffect = 9;
        break;

      //light blue [3][3]
      case 10:
        FastLED.clear();
        fill_solid(leds, NUMPIXELS, lightBlue);
        FastLED.show();
        effect = -1;
        lastEffect = 10;
        break;

      //pink [3][4]
      case 11:
        FastLED.clear();
        fill_solid(leds, NUMPIXELS, pink);
        FastLED.show();
        effect = -1;
        lastEffect = 11;
        break;

      //orange [4][1]
      case 12:
        FastLED.clear();
        fill_solid(leds, NUMPIXELS, orange);
        FastLED.show();
        effect = -1;
        lastEffect = 12;
        break;

      //light turquoise [4][2]
      case 13:
        FastLED.clear();
        fill_solid(leds, NUMPIXELS, lightTurquoise);
        FastLED.show();
        effect = -1;
        lastEffect = 13;
        break;

      //purple [4][3]
      case 14:
        FastLED.clear();
        fill_solid(leds, NUMPIXELS, purple);
        FastLED.show();
        effect = -1;
        lastEffect = 14;
        break;

      //light pink [4][4]
      case 15:
        FastLED.clear();
        fill_solid(leds, NUMPIXELS, lightPink);
        FastLED.show();
        effect = -1;
        lastEffect = 15;
        break;

      //light orange [5][1]
      case 16:
        FastLED.clear();
        fill_solid(leds, NUMPIXELS, lightOrange);
        FastLED.show();
        effect = -1;
        lastEffect = 16;
        break;

      //turquoise [5][2]
      case 17:
        FastLED.clear();
        fill_solid(leds, NUMPIXELS, turquoise);
        FastLED.show();
        effect = -1;
        lastEffect = 17;
        break;

      //light purple [5][3]
      case 18:
        FastLED.clear();
        fill_solid(leds, NUMPIXELS, lightPurple);
        FastLED.show();
        effect = -1;
        lastEffect = 18;
        break;

      //sky blue [5][4]
      case 19:
        FastLED.clear();
        fill_solid(leds, NUMPIXELS, skyBlue);
        FastLED.show();
        effect = -1;
        lastEffect = 19;
        break;

      //yellow [6][1]
      case 20:
        FastLED.clear();
        fill_solid(leds, NUMPIXELS, yellow);
        FastLED.show();
        effect = -1;
        lastEffect = 20;
        break;

      //dark turquoise [6][2]
      case 21:
        FastLED.clear();
        fill_solid(leds, NUMPIXELS, darkTurquoise);
        FastLED.show();
        effect = -1;
        lastEffect = 21;
        break;

      //dark pink [6][3]
      case 22:
        FastLED.clear();
        fill_solid(leds, NUMPIXELS, darkPink);
        FastLED.show();
        effect = -1;
        lastEffect = 22;
        break;

      //light sky blue [6][4]
      case 23:
        FastLED.clear();
        fill_solid(leds, NUMPIXELS, lightSkyBlue);
        FastLED.show();
        effect = -1;
        lastEffect = 23;
        break;

      //red up [7][1]
      case 24:
        for (int i = 0; i < NUMPIXELS; i++) {
          if (leds[i].r > 0 || leds[i].g > 0 || leds[i].b > 0) {
            leds[i] += CRGB( 0, colorDelta, 0);
          }
        }
        FastLED.show();
        if (lastEffect >= 30 && playing) {
          effect = lastEffect;
        }
        else {
          effect = -1;
        }
        break;

      //green up [7][2]
      case 25:
        for (int i = 0; i < NUMPIXELS; i++) {
          if (leds[i].r > 0 || leds[i].g > 0 || leds[i].b > 0) {
            leds[i] += CRGB( colorDelta, 0, 0);
          }
        }
        FastLED.show();
        if (lastEffect >= 30 && playing) {
          effect = lastEffect;
        }
        else {
          effect = -1;
        }
        break;

      //blue up [7][3]
      case 26:
        for (int i = 0; i < NUMPIXELS; i++) {
          if (leds[i].r > 0 || leds[i].g > 0 || leds[i].b > 0) {
            leds[i] += CRGB( 0, 0, colorDelta);
          }
        }
        FastLED.show();
        if (lastEffect >= 30 && playing) {
          effect = lastEffect;
        }
        else {
          effect = -1;
        }
        break;

      //red down [8][1]
      case 27:
        for (int i = 0; i < NUMPIXELS; i++) {
          if (leds[i].r > 0 || leds[i].g > 0 || leds[i].b > 0) {
            leds[i] -= CRGB( 0, colorDelta, 0);
          }
        }
        FastLED.show();
        if (lastEffect >= 30 && playing) {
          effect = lastEffect;
        }
        else {
          effect = -1;
        }
        break;

      //green down [8][2]
      case 28:
        for (int i = 0; i < NUMPIXELS; i++) {
          if (leds[i].r > 0 || leds[i].g > 0 || leds[i].b > 0) {
            leds[i] -= CRGB( colorDelta, 0, 0);
          }
        }
        FastLED.show();
        if (lastEffect >= 30 && playing) {
          effect = lastEffect;
        }
        else {
          effect = -1;
        }
        break;

      //blue down [8][3]
      case 29:
        for (int i = 0; i < NUMPIXELS; i++) {
          if (leds[i].r > 0 || leds[i].g > 0 || leds[i].b > 0) {
            leds[i] -= CRGB( 0, 0, colorDelta);
          }
        }
        FastLED.show();
        if (lastEffect >= 30 && playing) {
          effect = lastEffect;
        }
        else {
          effect = -1;
        }
        break;

      //DIY 1 [9][1]
      case 30:                            // leds[i].fadeLightBy(64) is decrease in brightness by 25%
        if (lastEffect != 30) {
          diy1Playing = true;
          FastLED.clear();
          leds[0] = LED0Color.fadeLightBy(102);
          leds[1] = LED0Color.fadeLightBy(77);
          leds[2] = LED0Color.fadeLightBy(51);
          leds[3] = LED0Color.fadeLightBy(26);
          leds[4] = LED0Color;
          leds[5] = LED0Color.fadeLightBy(26);
          leds[6] = LED0Color.fadeLightBy(51);
          leds[7] = LED0Color.fadeLightBy(77);
          leds[8] = LED0Color.fadeLightBy(102);
          
        }
        else {
          CRGB lastLED = leds[NUMPIXELS];
          for (int i = NUMPIXELS; i > 0; i--) {
            leds[i] = leds[i-1];
          }
          leds[0] = lastLED;
        }
        
        FastLED.show();
        delay(75);
        lastEffect = 30;
        break;

      //DIY 2 [9][2]
      case 31:
        if (lastEffect != 31 || diy2 == 0) {
          fill_solid(leds, NUMPIXELS, CRGB(random(1, 255), random(1, 255), random(1, 255)));
          diy2 = 0;
        }
        leds[diy2].setRGB( 0, 0, 0 );
        if (diy2 < NUMPIXELS) {
          diy2++;
        }
        else {
          diy2 = 0;
        }
        FastLED.show();
        delay(35);
        lastEffect = 31;
        break;

      //DIY 3 [9][3]
      case 32:
        //initialize
        if (lastEffect != 32) {
          fill_solid(leds, NUMPIXELS, CRGB( 0, 0, 0 ));
          diy3 = 0;
        }
        //assign color to first index
        if (diy3 <= 21) {
          leds[0] = red;
        }
        else if (diy3 > 21 && diy3 <= 43) {
          leds[0] = darkOrange;
        }
        else if (diy3 > 43 && diy3 <= 64) {
          leds[0] = yellow;
        }
        else if (diy3 > 64 && diy3 <= 86) {
          leds[0] = green;
        }
        else if (diy3 > 86 && diy3 <= 107) {
          leds[0] = blue;
        }
        else if (diy3 > 107 && diy3 <= 129) {
          leds[0] = indigo;
        }
        else {
          leds[0] = purple;
        }
        //shift everything over one index
        for (int i = NUMPIXELS; i > 0; i--) {
          leds[i] = leds[i-1];
        }

        //increment diy var
        if (diy3 < NUMPIXELS) {
          diy3++;
        }
        else {
          diy3 = 0;
        }
        FastLED.show();
        delay(35);
        lastEffect = 32;
        break;

      //DIY 4 [10][1]
      case 33:
        //initialize
        if (lastEffect != 33) {
          fill_solid(leds, NUMPIXELS, CRGB( 0, 0, 0 ));
          diy4 = 0;
        }
        
        //assign color to first index
        if (diy4 <= 2) {
          leds[0] = red;
        }
        else if ( (diy4 >= 3 && diy4 <= 5) || (diy4 >= 9 && diy4 <= 11) ) {
          leds[0] = white;
        }
        else {
          leds[0] = blue;
        }

        FastLED.show();
        //shift everything over one index
        for (int i = NUMPIXELS; i > 0; i--) {
          leds[i] = leds[i-1];
        }

        //increment diy var
        if (diy4 < 11) {
          diy4++;
        }
        else {
          diy4 = 0;
        }

        delay(100);
        lastEffect = 33;
        break;

      //Quick [7][4]
      case 34:
        //initialize
        if (lastEffect != 34) {
          fill_solid(leds, NUMPIXELS, red);
          quick = 0;
        }

        //determine where to start
        if (leds[0].r < 255 && leds[0].g == 255 && leds[0].b == 0) {
          quick = 0;
        }
        else if (leds[0].r == 255 && leds[0].g > 0 && leds[0].b == 0) {
          quick = 1;
        }
        else if (leds[0].r > 0 && leds[0].g == 0 && leds[0].b < 255) {
          quick = 2;
        }
        else if (leds[0].r == 0 && (leds[0].g < 153 || leds[0].b > 153)) {
          quick = 3;
        }
        else if ((leds[0].r < 20 || leds[0].g < 255 || leds[0].b > 147) && (quick == 3 || quick == 4)) {
          quick = 4;
        }
        else {
          quick = 5;
        }

        //change color
        //transition from red to darkOrange to yellow (increment r)
        if (quick == 0) {
          for (int i = 0; i < NUMPIXELS; i++) {
            if (leds[i].r > 200) {
              leds[i].r += chromaDelta*1.5;
            }
            else {
              if (leds[i].r + (chromaDelta/2) > 255) {
                leds[i].r = 255;
              }
              else {
                leds[i].r += (chromaDelta/2);
              }
            }
          }
        }
        //transition from yellow to green (decrement g)
        else if (quick == 1) {
          for (int i = 0; i < NUMPIXELS; i++) {
            if (leds[i].g > 128) {
              leds[i].g -= chromaDelta*1.2;
            }
            else {
              if (leds[i].g - chromaDelta < 0) {
                leds[i].g = 0;
              }
              else {
                leds[i].g -= chromaDelta;
              }
            }
          }
        }
        //transition from green to blue (decrement r, increment b)
        else if (quick == 2) {
          for (int i = 0; i < NUMPIXELS; i++) {
            if (leds[i].r - (chromaDelta) < 0 || leds[i].b + (chromaDelta) > 255) {
              leds[i].r = 0;
              leds[i].b = 255;
            }
            else {
              leds[i].r -= (chromaDelta);
              leds[i].b += (chromaDelta);
            }
          }
        }
        //transition from blue to purple (increment g to 153, decrement b to 153)
        else if (quick == 3) {
          for (int i = 0; i < NUMPIXELS; i++) {
            if (leds[i].b - (chromaDelta) < 153) {
              leds[i].b = 153;
              if (leds[i].g + chromaDelta > 153) {
                leds[i].g = 153;
              }
              else {
                leds[i].g += chromaDelta;
              }
            }
            else {
              leds[i].b -= (chromaDelta);
              leds[i].g += (chromaDelta);
            }
          }
        }
        //transition from purple to darkPink (r = 0 -> 20, g = 153 -> 255 , b = 153 -> 147)
        else if (quick == 4) {
          for (int i = 0; i < NUMPIXELS; i++) {
            if (leds[i].b - (chromaDelta/3) < 147) {
              leds[i].b = 147;
              if (leds[i].r + (chromaDelta/2) > 20) {
                leds[i].r = 20;
                if (leds[i].g + chromaDelta > 255) {
                  leds[i].g = 255;
                }
                else {
                  leds[i].g += chromaDelta;
                }
              }
              else {
                leds[i].r += (chromaDelta/2);
                leds[i].g += (chromaDelta/2);
              }
            }
            else {
              leds[i].r += (chromaDelta/3);
              leds[i].g += (chromaDelta/3);
              leds[i].b -= (chromaDelta/3);
            }
          }
        }
        //transition from darkPink to red (r = 20 -> 0, b = 147 -> 0)
        else { // quick == 5
          for (int i = 0; i < NUMPIXELS; i++) {
            if (leds[i].r - (chromaDelta/2) < 0) {
              leds[i].r = 0;
              if (leds[i].b - chromaDelta < 0) {
                leds[i].b = 0;
              }
              else {
                leds[i].b -= chromaDelta;
              }
            }
            else {
              leds[i].b -= (chromaDelta/2);
              leds[i].r -= (chromaDelta/2);
            }
          }
        }
        
        FastLED.show();
        delay(10);
        lastEffect = 34;
        break;

      //Slow [8][4]
      case 35:
        //initialize
        if (lastEffect != 35) {
          fill_solid(leds, NUMPIXELS, red);
          slow = 0;
        }

        //determine where to start
        if (leds[0].r < 255 && leds[0].g == 255 && leds[0].b == 0) {
          slow = 0;
        }
        else if (leds[0].r == 255 && leds[0].g > 0 && leds[0].b == 0) {
          slow = 1;
        }
        else if (leds[0].r > 0 && leds[0].g == 0 && leds[0].b < 255) {
          slow = 2;
        }
        else if (leds[0].r == 0 && (leds[0].g < 153 || leds[0].b > 153)) {
          slow = 3;
        }
        else if ((leds[0].r < 20 || leds[0].g < 255 || leds[0].b > 147) && (slow == 3 || slow == 4)) {
          slow = 4;
        }
        else {
          slow = 5;
        }

        //change color
        //transition from red to darkOrange to yellow (increment r)
        if (slow == 0) {
          for (int i = 0; i < NUMPIXELS; i++) {
            if (leds[i].r > 200) {
              leds[i].r += chromaDelta*1.5;
            }
            else {
              if (leds[i].r + (chromaDelta/2) > 255) {
                leds[i].r = 255;
              }
              else {
                leds[i].r += (chromaDelta/2);
              }
            }
          }
        }
        //transition from yellow to green (decrement g)
        else if (slow == 1) {
          for (int i = 0; i < NUMPIXELS; i++) {
            if (leds[i].g > 128) {
              leds[i].g -= chromaDelta*1.2;
            }
            else {
              if (leds[i].g - chromaDelta < 0) {
                leds[i].g = 0;
              }
              else {
                leds[i].g -= chromaDelta;
              }
            }
          }
        }
        //transition from green to blue (decrement r, increment b)
        else if (slow == 2) {
          for (int i = 0; i < NUMPIXELS; i++) {
            if (leds[i].r - (chromaDelta) < 0 || leds[i].b + (chromaDelta) > 255) {
              leds[i].r = 0;
              leds[i].b = 255;
            }
            else {
              leds[i].r -= (chromaDelta);
              leds[i].b += (chromaDelta);
            }
          }
        }
        //transition from blue to purple (increment g to 153, decrement b to 153)
        else if (slow == 3) {
          for (int i = 0; i < NUMPIXELS; i++) {
            if (leds[i].b - (chromaDelta) < 153) {
              leds[i].b = 153;
              if (leds[i].g + chromaDelta > 153) {
                leds[i].g = 153;
              }
              else {
                leds[i].g += chromaDelta;
              }
            }
            else {
              leds[i].b -= (chromaDelta);
              leds[i].g += (chromaDelta);
            }
          }
        }
        //transition from purple to darkPink (r = 0 -> 20, g = 153 -> 255 , b = 153 -> 147)
        else if (slow == 4) {
          for (int i = 0; i < NUMPIXELS; i++) {
            if (leds[i].b - (chromaDelta/3) < 147) {
              leds[i].b = 147;
              if (leds[i].r + (chromaDelta/2) > 20) {
                leds[i].r = 20;
                if (leds[i].g + chromaDelta > 255) {
                  leds[i].g = 255;
                }
                else {
                  leds[i].g += chromaDelta;
                }
              }
              else {
                leds[i].r += (chromaDelta/2);
                leds[i].g += (chromaDelta/2);
              }
            }
            else {
              leds[i].r += (chromaDelta/3);
              leds[i].g += (chromaDelta/3);
              leds[i].b -= (chromaDelta/3);
            }
          }
        }
        //transition from darkPink to red (r = 20 -> 0, b = 147 -> 0)
        else { // slow == 5
          for (int i = 0; i < NUMPIXELS; i++) {
            if (leds[i].r - (chromaDelta/2) < 0) {
              leds[i].r = 0;
              if (leds[i].b - chromaDelta < 0) {
                leds[i].b = 0;
              }
              else {
                leds[i].b -= chromaDelta;
              }
            }
            else {
              leds[i].b -= (chromaDelta/2);
              leds[i].r -= (chromaDelta/2);
            }
          }
        }
        
        FastLED.show();
        delay(40);
        lastEffect = 35;
        break;

      //Flash [10][4]
      case 36:
        if (lastEffect != 36 || leds[0] == CRGB(0,0,0)) {
          fill_solid(leds, NUMPIXELS, LED0Color);
        }
        else {
          FastLED.clear();
        }
        
        FastLED.show();
        delay(50);
        lastEffect = 36;
        break;

      //Auto [9][4]
      case 37:
        if (lastEffect != 37 || (!leds[0])) {
          FastLED.clear();
          for (int i = 0; i < NUMPIXELS; i+=2) {
            leds[i] = LED0Color;
          }
        }
        else {
          FastLED.clear();
          for (int i = 1; i < NUMPIXELS; i+=2) {
            leds[i] = LED0Color;
          }
        }
        
        FastLED.show();
        delay(75);
        lastEffect = 37;
        break;

      //DIY 5 [10][2]
      case 38:
        diy5Counter++;
        if (diy5Counter == 8) {
          FastLED.clear();
          diy5Counter = 0;
          for (long i = 0; i < random(115,130); i++) {
            long color = random(1,4);
            if (color == 1) {
              long index = random(0, NUMPIXELS-1);
              leds[index] = darkTurquoise;
              leds[index].fadeLightBy(random(75,250));
            }
            else if (color == 2) {
              long index = random(0, NUMPIXELS-1);
              leds[index] = lightGreen;
              leds[index].fadeLightBy(random(75,250));
            }
            else {
              long index = random(0, NUMPIXELS-1);
              leds[index] = lightOrange;
              leds[index].fadeLightBy(random(75,250));
            }
          }
        }
        
        FastLED.show();
        delay(random(150,400));
        lastEffect = 38;
        break;

      //Jump 3 [11][1]
      case 39:
        if (lastEffect != 39) {
          FastLED.clear();
          leds[0] = red;
          
          leds[1] = red;
          leds[2] = red;
          leds[27] = blue;
          leds[28] = blue;
          
          leds[29] = blue;
          leds[30] = blue;

          leds[31] = blue;
          leds[32] = blue;
          leds[57] = yellow;
          leds[58] = yellow;
          
          leds[59] = yellow;
          leds[60] = yellow;

          leds[61] = yellow;
          leds[62] = yellow;
          leds[87] = red;
          leds[88] = red;
          
          leds[89] = red;
          leds[90] = red;

          leds[91] = red;
          leds[92] = red;
          leds[117] = blue;
          leds[118] = blue;
          
          leds[119] = blue;
          leds[120] = blue;

          leds[121] = blue;
          leds[122] = blue;
          leds[147] = yellow;
          leds[148] = yellow;
          
          leds[149] = yellow;
          
          jump3Switch = false;
        }
        else {
          if (!jump3Switch) {
            //normal
            for (int i = 14; i > 0; i--) {
              leds[i] = leds[i-1];
              leds[i-1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = red;
              }
            }
            for (int i = 15; i < 29; i++) {
              leds[i] = leds[i+1];
              leds[i+1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = blue;
              }
            }
            for (int i = 44; i > 30; i--) {
              leds[i] = leds[i-1];
              leds[i-1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = blue;
              }
            }
            for (int i = 45; i < 59; i++) {
              leds[i] = leds[i+1];
              leds[i+1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = yellow;
              }
            }
            for (int i = 74; i > 60; i--) {
              leds[i] = leds[i-1];
              leds[i-1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = yellow;
              }
            }
            for (int i = 75; i < 89; i++) {
              leds[i] = leds[i+1];
              leds[i+1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = red;
              }
            }
            for (int i = 104; i > 90; i--) {
              leds[i] = leds[i-1];
              leds[i-1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = red;
              }
            }
            for (int i = 105; i < 119; i++) {
              leds[i] = leds[i+1];
              leds[i+1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = blue;
              }
            }
            for (int i = 134; i > 120; i--) {
              leds[i] = leds[i-1];
              leds[i-1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = blue;
              }
            }
            for (int i = 135; i < 149; i++) {
              leds[i] = leds[i+1];
              leds[i+1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = yellow;
              }
            }
            if (leds[14]) {
                jump3Switch = true;
            }
          }
          else {
            //alt
            for (int i = 0; i < 14; i++) {
              leds[i] = leds[i+1];
              leds[i+1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = purple;
              }
            }
            for (int i = 29; i > 15; i--) {
              leds[i] = leds[i-1];
              leds[i-1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = purple;
              }
            }
            for (int i = 30; i < 44; i++) {
              leds[i] = leds[i+1];
              leds[i+1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = green;
              }
            }
            for (int i = 59; i > 45; i--) {
              leds[i] = leds[i-1];
              leds[i-1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = green;
              }
            }
            for (int i = 60; i < 74; i++) {
              leds[i] = leds[i+1];
              leds[i+1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = darkOrange;
              }
            }
            for (int i = 89; i > 75; i--) {
              leds[i] = leds[i-1];
              leds[i-1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = darkOrange;
              }
            }
            for (int i = 90; i < 104; i++) {
              leds[i] = leds[i+1];
              leds[i+1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = purple;
              }
            }
            for (int i = 119; i > 105; i--) {
              leds[i] = leds[i-1];
              leds[i-1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = purple;
              }
            }
            for (int i = 120; i < 134; i++) {
              leds[i] = leds[i+1];
              leds[i+1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = green;
              }
            }
            for (int i = 149; i > 135; i--) {
              leds[i] = leds[i-1];
              leds[i-1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = green;
              }
            }
            if (leds[0]) {
                jump3Switch = false;
                //Serial.println("switching to normal");
            }
          }
        }
        FastLED.show();
        delay(37);
        lastEffect = 39;
        break;

      //Jump 7 [11][2]
      case 40:
        if (lastEffect != 40) {
          FastLED.clear();
          leds[0] = jump7Color1;
          
          leds[1] = jump7Color1;
          leds[2] = jump7Color1;
          leds[27] = jump7Color2;
          leds[28] = jump7Color2;
          
          leds[29] = jump7Color2;
          leds[30] = jump7Color3;

          leds[31] = jump7Color3;
          leds[32] = jump7Color3;
          leds[57] = jump7Color4;
          leds[58] = jump7Color4;
          
          leds[59] = jump7Color4;
          leds[60] = jump7Color5;

          leds[61] = jump7Color5;
          leds[62] = jump7Color5;
          leds[87] = jump7Color6;
          leds[88] = jump7Color6;
          
          leds[89] = jump7Color6;
          leds[90] = jump7Color7;

          leds[91] = jump7Color7;
          leds[92] = jump7Color7;
          leds[117] = jump7Color8;
          leds[118] = jump7Color8;
          
          leds[119] = jump7Color8;
          leds[120] = jump7Color9;

          leds[121] = jump7Color9;
          leds[122] = jump7Color9;
          leds[147] = jump7Color10;
          leds[148] = jump7Color10;
          
          leds[149] = jump7Color10;
          
          jump7Switch = false;
        }
        else {
          if (!jump7Switch) {
            //normal
            for (int i = 14; i > 0; i--) {
              leds[i] = leds[i-1];
              leds[i-1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = jump7Color1;
              }
            }
            for (int i = 15; i < 29; i++) {
              leds[i] = leds[i+1];
              leds[i+1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = jump7Color2;
              }
            }
            for (int i = 44; i > 30; i--) {
              leds[i] = leds[i-1];
              leds[i-1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = jump7Color3;
              }
            }
            for (int i = 45; i < 59; i++) {
              leds[i] = leds[i+1];
              leds[i+1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = jump7Color4;
              }
            }
            for (int i = 74; i > 60; i--) {
              leds[i] = leds[i-1];
              leds[i-1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = jump7Color5;
              }
            }
            for (int i = 75; i < 89; i++) {
              leds[i] = leds[i+1];
              leds[i+1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = jump7Color6;
              }
            }
            for (int i = 104; i > 90; i--) {
              leds[i] = leds[i-1];
              leds[i-1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = jump7Color7;
              }
            }
            for (int i = 105; i < 119; i++) {
              leds[i] = leds[i+1];
              leds[i+1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = jump7Color8;
              }
            }
            for (int i = 134; i > 120; i--) {
              leds[i] = leds[i-1];
              leds[i-1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = jump7Color9;
              }
            }
            for (int i = 135; i < 149; i++) {
              leds[i] = leds[i+1];
              leds[i+1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = jump7Color10;
              }
            }
            if (leds[14]) {
                jump7Switch = true;
            }
          }
          else {
            //alt
            for (int i = 0; i < 14; i++) {
              leds[i] = leds[i+1];
              leds[i+1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = jump7Color1;
              }
            }
            for (int i = 29; i > 15; i--) {
              leds[i] = leds[i-1];
              leds[i-1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = jump7Color2;
              }
            }
            for (int i = 30; i < 44; i++) {
              leds[i] = leds[i+1];
              leds[i+1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = jump7Color3;
              }
            }
            for (int i = 59; i > 45; i--) {
              leds[i] = leds[i-1];
              leds[i-1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = jump7Color4;
              }
            }
            for (int i = 60; i < 74; i++) {
              leds[i] = leds[i+1];
              leds[i+1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = jump7Color5;
              }
            }
            for (int i = 89; i > 75; i--) {
              leds[i] = leds[i-1];
              leds[i-1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = jump7Color6;
              }
            }
            for (int i = 90; i < 104; i++) {
              leds[i] = leds[i+1];
              leds[i+1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = jump7Color7;
              }
            }
            for (int i = 119; i > 105; i--) {
              leds[i] = leds[i-1];
              leds[i-1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = jump7Color8;
              }
            }
            for (int i = 120; i < 134; i++) {
              leds[i] = leds[i+1];
              leds[i+1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = jump7Color9;
              }
            }
            for (int i = 149; i > 135; i--) {
              leds[i] = leds[i-1];
              leds[i-1] = CRGB(0,0,0);
              if (leds[i]) {
                leds[i] = jump7Color10;
              }
            }
            if (leds[0]) {
                jump7Switch = false;
                //Serial.println("switching to normal");
            }
          }
        }
        FastLED.show();
        delay(37);
        lastEffect = 40;
        break;

      //Fade 3 [11][3]
      case 41:
        if (lastEffect != 41) {
          FastLED.clear();
          fill_solid(leds, NUMPIXELS, LED0Color);
          FastLED.setBrightness(100);
          fade3Switch = false;
        }
        else {
          if (!fade3Switch) {
            fade3 -= 1;
            if (fade3 == 1) {
              fade3Switch = true;
            }
          }
          else {
            fade3 += 1;
            if (fade3 == 100) {
              fade3Switch = false;
            }
          }
          FastLED.setBrightness(fade3);
        }
        
        FastLED.show();
        if (fade3 < 25) {
          delay(75);
        }
        else if (fade3 >= 25 && fade3 < 50) {
          delay(60);
        }
        else if (fade3 >= 50 && fade3 < 75) {
          delay(40);
        }
        else {
          delay(25);
        }
        lastEffect = 41;
        break;

      //Fade 7 [11][4]
      case 42:
        if (lastEffect != 42) {
          FastLED.clear();
          fill_solid(leds, NUMPIXELS, CRGB(random(1,254),random(1,254),random(1,254)));
          fade7Color = CRGB(random(1,254),random(1,254),random(1,254));
        }
        else {
          if (leds[0].r < fade7Color.r) {
            for (int i = 0; i < NUMPIXELS; i++) {
              leds[i].r += 1;
            }
          }
          else if (leds[0].r > fade7Color.r) {
            for (int i = 0; i < NUMPIXELS; i++) {
              leds[i].r -= 1;
            }
          }
          if (leds[0].g < fade7Color.g) {
            for (int i = 0; i < NUMPIXELS; i++) {
              leds[i].g += 1;
            }
          }
          else if (leds[0].g > fade7Color.g) {
            for (int i = 0; i < NUMPIXELS; i++) {
              leds[i].g -= 1;
            }
          }
          if (leds[0].b < fade7Color.b) {
            for (int i = 0; i < NUMPIXELS; i++) {
              leds[i].b += 1;
            }
          }
          else if (leds[0].b > fade7Color.b) {
            for (int i = 0; i < NUMPIXELS; i++) {
              leds[i].b -= 1;
            }
          }
          if (leds[0].r == fade7Color.r && leds[0].g == fade7Color.g && leds[0].b == fade7Color.b) {
            fade7Color = CRGB(random(1,254),random(1,254),random(1,254));
          }
        }
        
        FastLED.show();
        delay(25);
        lastEffect = 42;
        break;

      //Diy 6 [11][4]
      case 43:
        FastLED.clear();
        fill_solid(leds, NUMPIXELS, CRGB(random(1,254),random(1,254),random(1,254)));
        FastLED.show();
        effect = -1;
        lastEffect = 43;
//        Serial.print("r: "); 
//        Serial.print(leds[0].r);
//        Serial.print(" g: ");
//        Serial.print(leds[0].g);
//        Serial.print(" b: ");
//        Serial.println(leds[0].b);
        break;
    }
  }

  while (!irrecv.isIdle());

  if (irrecv.decode(&results)) {

    //holding button down functionality
    if (results.value == 0XFFFFFFFF) {
      results.value = key_value;
    }
    //Serial.println(results.value, HEX);

    bool newColor = false;
    for (int i = 0; i < NUMPIXELS; i++) {
            if (leds[i].r != 0 || leds[i].g != 0 || leds[i].b != 0) {
              LED0Color = leds[i];
              newColor = true;
              break;
            }
          }
          if (!newColor) {
            LED0Color = red;
          }

    switch (results.value) {

      //brightness up [1][1]
      case 0xFF3AC5:
        effect = 0;
        break;

      //brightness down [1][2]
      case 0xFFBA45:
        effect = 1;
        break;

      //play/pause [1][3]
      case 0xFF827D:
        effect = 2;
        break;

      //power [1][4]
      case 0xFF02FD:
        effect = 3;
        playing = true;
        break;

      //red R [2][1]
      case 0xFF1AE5:
        effect = 4;
        playing = true;
        break;

      //green G [2][2]
      case 0xFF9A65:
        effect = 5;
        playing = true;
        break;

      //blue B [2][3]
      case 0xFFA25D:
        effect = 6;
        playing = true;
        break;

      //white W [2][4]
      case 0xFF22DD:
        effect = 7;
        playing = true;
        break;

      //dark orange [3][1]
      case 0xFF2AD5:
        effect = 8;
        playing = true;
        break;

      //light green [3][2]
      case 0xFFAA55:
        effect = 9;
        playing = true;
        break;

      //light blue [3][3]
      case 0xFF926D:
        effect = 10;
        playing = true;
        break;

      //pink [3][4]
      case 0xFF12ED:
        effect = 11;
        playing = true;
        break;

      //orange [4][1]
      case 0xFF0AF5:
        effect = 12;
        playing = true;
        break;

      //light turquoise [4][2]
      case 0xFF8A75:
        effect = 13;
        playing = true;
        break;

      //purple [4][3]
      case 0xFFB24D:
        effect = 14;
        playing = true;
        break;

      //light pink [4][4]
      case 0xFF32CD:
        effect = 15;
        playing = true;
        break;

      //light orange [5][1]
      case 0xFF38C7:
        effect = 16;
        playing = true;
        break;

      //turquoise [5][2]
      case 0xFFB847:
        effect = 17;
        playing = true;
        break;

      //light purple [5][3]
      case 0xFF7887:
        effect = 18;
        playing = true;
        break;

      //sky blue [5][4]
      case 0xFFF807:
        effect = 19;
        playing = true;
        break;

      //yellow [6][1]
      case 0xFF18E7:
        effect = 20;
        playing = true;
        break;

      //dark turquoise [6][2]
      case 0xFF9867:
        effect = 21;
        playing = true;
        break;

      //dark pink [6][3]
      case 0xFF58A7:
        effect = 22;
        playing = true;
        break;

      //light sky blue [6][4]
      case 0xFFD827:
        effect = 23;
        playing = true;
        break;

      //red up [7][1]
      case 0xFF28D7:
        effect = 24;
        break;

      //green up [7][2]
      case 0xFFA857:
        effect = 25;
        break;

      //blue up [7][3]
      case 0xFF6897:
        effect = 26;
        break;

      //red down [8][1]
      case 0xFF08F7:
        effect = 27;
        break;

      //green down [8][2]
      case 0xFF8877:
        effect = 28;
        break;

      //blue down [8][3]
      case 0xFF48B7:
        effect = 29;
        break;

      //DIY 1 [9][1]
      case 0xFF30CF:
        effect = 30;
        playing = true;
        break;

      //DIY 2 [9][2]
      case 0xFFB04F:
        effect = 31;
        playing = true;
        break;

      //DIY 3 [9][3]
      case 0xFF708F:
        effect = 32;
        playing = true;
        break;
        
      //DIY 4 [10][1]
      case 0xFF10EF:
        effect = 33;
        playing = true;
        break;

      //quick [7][4]
      case 0xFFE817:
        effect = 34;
        playing = true;
        break;

      //slow [8][4]
      case 0xFFC837:
        effect = 35;
        playing = true;
        break;

      //Flash [10][4]
      case 0xFFD02F:
        effect = 36;
        playing = true;
        break;

      //Auto [9][4]
      case 0xFFF00F:
        effect = 37;
        playing = true;
        break;

      //DIY 5 [10][2]
      case 0xFF906F:
        effect = 38;
        playing = true;
        break;

      //Jump 3 [11][1]
      case 0xFF20DF:
        effect = 39;
        playing = true;
        break;

      //Jump 7 [11][2]
      case 0xFFA05F:
        effect = 40;
        playing = true;
        jump7Color1 = CRGB(random(1,254),random(1,254),random(1,254));
        jump7Color2 = CRGB(random(1,254),random(1,254),random(1,254));
        jump7Color3 = CRGB(random(1,254),random(1,254),random(1,254));
        jump7Color4 = CRGB(random(1,254),random(1,254),random(1,254));
        jump7Color5 = CRGB(random(1,254),random(1,254),random(1,254));
        jump7Color6 = CRGB(random(1,254),random(1,254),random(1,254));
        jump7Color7 = CRGB(random(1,254),random(1,254),random(1,254));
        jump7Color8 = CRGB(random(1,254),random(1,254),random(1,254));
        jump7Color9 = CRGB(random(1,254),random(1,254),random(1,254));
        jump7Color10 = CRGB(random(1,254),random(1,254),random(1,254));
        break;

      //Fade 3 [11][3]
      case 0xFF609F:
        effect = 41;
        playing = true;
        break;

      //Fade 7 [11][4]
      case 0xFFE01F:
        effect = 42;
        playing = true;
        break;

      //DIY 6 [10][3]
      case 0xFF50AF:
        effect = 43;
        playing = true;
        break;

      //command not recognized
      default:
        //effect = -1;
        //Serial.print(results.value, HEX);
        //Serial.println(" is not a recognized command.");
        break;
    }

    key_value = results.value;
    irrecv.resume();
  }
}
