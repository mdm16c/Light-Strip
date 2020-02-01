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
int colorDelta = 1;
int effect = 3;
int lastEffect = -1;

//animation vars
int diy1 = 0;
CRGB LED0Color = CRGB(0, 0, 0);
int diy2 = 0;
int diy3 = 0;
int diy4 = 0;
int quick = 0;
int slow = 0;
int chromaDelta = 6;
bool playing = true;

//colors
//accepts colors in green, red, blue
CRGB red = CRGB(0, 255, 0);
CRGB green = CRGB(255, 0, 0);
CRGB lightGreen = CRGB(204, 0, 102);
CRGB blue = CRGB(0, 0, 255);
CRGB lightBlue = CRGB(128, 0, 255);
CRGB skyBlue = CRGB(206, 135, 250);
CRGB lightSkyBlue = CRGB(216, 173, 230);
CRGB turquoise = CRGB(206, 0, 209);
CRGB lightTurquoise = CRGB(224, 64, 208);
CRGB darkTurquoise = CRGB(139, 0, 139);
CRGB white = CRGB(254, 254, 254);
CRGB darkOrange = CRGB(128, 255, 0);
CRGB orange = CRGB(153, 255, 51);
CRGB lightOrange = CRGB(178, 255, 102);
CRGB yellow = CRGB(255, 255, 0);
CRGB purple = CRGB(0, 153, 153);
CRGB lightPurple = CRGB(0, 204, 102);
CRGB pink = CRGB(105, 255, 180);
CRGB lightPink = CRGB(192, 255, 203);
CRGB darkPink = CRGB(20, 255, 147);
CRGB indigo = CRGB(0, 75, 130);

void setup() {
  // sanity check
  delay(2000);

  // setup IR reciever
  Serial.begin(9600);
  irrecv.enableIRIn();

  //blink arduino LED on input recieved
  irrecv.blink13(true);

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

          if (leds[0].r != 0 || leds[0].g != 0 || leds[0].b != 0) {
            LED0Color = leds[0];
          }
          else {
            LED0Color = red;
          }
          FastLED.clear();
          leds[0] = LED0Color.fadeLightBy(102);
          diy1 = 0;
//          FastLED.show();
        }
        else {
          if (diy1 < 9 || diy1 == NUMPIXELS) {
            for (int i = diy1+1; i > 0; i--) {
              if (i > NUMPIXELS) {
                continue;
              }
              leds[i] = leds[i-1];
            }
            if (diy1 == 0 || diy1 == 4) {
              leds[diy1] = LED0Color.fadeLightBy(77);
            }
            else if (diy1 == 1 || diy1 == 5) {
              leds[diy1] = LED0Color.fadeLightBy(51);
            }
            else if (diy1 == 2 || diy1 == 6) {
              leds[diy1] = LED0Color.fadeLightBy(26);
            }
            else if (diy1 == 3) {
              leds[diy1] = LED0Color;
            }
            else if (diy1 == NUMPIXELS || diy1 == 7) {
              leds[diy1] = LED0Color.fadeLightBy(102);
            }
          }
          else {
            for (int i = NUMPIXELS; i > 0; i--) {
              leds[i] = leds[i-1];
            }
          }
        }
        if (diy1 < NUMPIXELS) {
          diy1++;
        }
        else {
          diy1 = 0;
        }
        
        FastLED.show();
        delay(35);
        Serial.println(diy1);
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
    }
  }

  while (!irrecv.isIdle());

  if (irrecv.decode(&results)) {

    //holding button down functionality
    if (results.value == 0XFFFFFFFF) {
      results.value = key_value;
    }
    Serial.println(results.value, HEX);

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

      //command not recognized
      default:
        effect = -1;
        Serial.print(results.value, HEX);
        Serial.println(" is not a recognized command.");
        break;
    }

    key_value = results.value;
    irrecv.resume();
  }
}
