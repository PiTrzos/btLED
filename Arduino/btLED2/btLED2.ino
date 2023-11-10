#include <FastLED.h>
#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h> //library for software serial

#define FASTLED_ESP8266_RAW_PIN_ORDER
#define NUM_LEDS 107
#define LED_TYPE WS2813
#define COLOR_ORDER BRG
#define LED_PIN D8
#define SOUND_SENDOR_PIN D4

CRGB leds[NUM_LEDS];
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_BRG + NEO_KHZ800);
SoftwareSerial btSerial(D2, D3); 
uint8_t prefix[] = {'A', 'd', 'a'}, hi, lo, chk, i;

CRGB colors[10] = {CRGB::Aqua};

DEFINE_GRADIENT_PALETTE(rainbowGradient) {
0,255,0,0,
8,255,0,0,
16,255,25,0,
24,255,35,0,
32,255,100,0,
41,255,115,0, //red - purple

49,255,180,0,
57,255,225,0,
65,255,255,0,// blue
74,125,255,0,
82,90,255,0,

90,25,255,0,
98,0,255,0,
106,0,255,60, //aqua
115,0,255,125,
123,0,255,225,

131,0,255,255,
139,0,200,255,
148,0,125,255,
156,0,60,255,
164,0,0,255,

172,0,0,255,
180,60,0,255,
189,122,0,255,
197,162,0,255,
205,201,0,255,

213,255,0,255,
222,255,0,125,
230,255,0,90,
238,255,0,60,
246,255,0,10,
255,255,0,0
};

char data;
int counter = 0;
String finString = "";

boolean restartRainbowFunc = false;

boolean isMode = false;
boolean isColor = false;
boolean isBrightnes = false;
boolean isSpeed = false;

String red = "";
String green = "";
String blue = "";

int oldRed = 255;
int oldGreen = 255;
int oldBlue = 255;

int brightnes = 125;
int modeSpeed = 50;
String mode = "";

bool switchMode = false;
int maxModes = 100;
int maxSpeed = 100;

int soundSensorValue = 0;

CRGBPalette16 currentPalette;
TBlendType    currentBlending;
void chase(){
  for (int i = 0; i < NUM_LEDS; i++ )
  {
    leds[i] = CRGB(255, 255, 255); //neopixel b=g
    FastLED.show();
    delay(20);
  }
}
void setup()
{
   Serial.begin(115200);
   btSerial.begin(9600);
   FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
   FastLED.setBrightness(125);
   chase();
   pinMode(SOUND_SENDOR_PIN, INPUT);
}

void ALL_LEDS(int r, int g, int b){
  for (int i = 0; i < NUM_LEDS; i++ )
  {
    leds[i] = CRGB(r, b, g); //neopixel b=g
  }
  FastLED.show();
}
void ALL_LEDS(uint32_t color){
  for (int i = 0; i < NUM_LEDS; i++ )
  {
    leds[i] = CRGB(color);
  }
  FastLED.show();
}
boolean endModeCheck(){
  boolean modeB = false;
  boolean modeS = false;
  finString = "";
  
    char data = btSerial.read();
    switch(data){
      case 'T':
        resetValues();
        isColor= true;
        return true;
      break;
      case 'M':
        resetValues();
        isMode = true;
        return true;
      break;
      case 'B':
        modeB = true;
      break;
      case 'S':
        modeS= true;
      break;
      default:
      break;
  }
  if(modeB || modeS){
    while (btSerial.available() > 0){
      data=btSerial.read();
      switch(data){
      case 'T':
        resetValues();
        isColor= true;
        return true;
      break;
      case 'M':
        resetValues();
        isMode = true;
        return true;
      break;
      case 'B':
        modeB = true;
      break;
      case 'S':
        modeS= true;
      break;
      case '\n':
        if(modeS){
          changeSpeed(finString);
        }
        if(modeB){
          changeBrightnes(finString);
        }
        modeS = false;
        modeB = false;
        finString ="";
      break;
      default:
      if(data!=' '){
        finString+=data;
      }else{
        
      }
      break;
      }
    }
  }
  finString ="";
  return false;
}

void resetValues(){
      finString = "";
      isMode = false;
      isColor = false;
      isBrightnes = false;
      isSpeed = false;
      switchMode = false;
      counter = 0;
}

void changeColor(String newRed, String newGreen, String newBlue){
  int redValue = constrain(newRed.toInt(),0,255);
  int greenValue = constrain(newGreen.toInt(),0,255);
  int blueValue = constrain(newBlue.toInt(),0,255);
  ALL_LEDS(redValue,greenValue,blueValue);
}

void fadeMode(){
  int r = 255;
  int g = 0;
  int b = 255;
  int colorTab[] = {r,g,b};
  int counter = 0;
  int counter2 = 0;
  boolean endMode = false;
  while(!endMode){
    if(counter%2==0){
      while(colorTab[counter2]!=0 && !endMode){
        colorTab[counter2]=colorTab[counter2]-1;
        ALL_LEDS(colorTab[0],colorTab[1],colorTab[2]);
        if(btSerial.available()){
          endMode = endModeCheck();
        }else{
          delay(modeSpeed);
        }
      }
    }else{
      while(colorTab[counter2]!=255 && !endMode){
        colorTab[counter2]=colorTab[counter2]+1;
        ALL_LEDS(colorTab[0],colorTab[1],colorTab[2]);
        if(btSerial.available()){
          endMode = endModeCheck();
        }else{
          delay(modeSpeed);
        }
      }
    }
    counter2++;
    if(counter2==3 && !endMode){
      counter2 = 0;
    }
    counter++;
    if(counter==2 && !endMode){
      counter = 0;
    }
  }
}
void flashMode(){
  boolean endMode = false;
  while(!endMode){
      if(btSerial.available() && !endMode){
          endMode = endModeCheck();
          if(endMode){
            return;
          }
      }else{
          ALL_LEDS(255,0,0);
          delay((1+modeSpeed)*15);
      }
      
      if(btSerial.available() && !endMode){
          endMode = endModeCheck();
          if(endMode){
            return;
          }
      }else{
          ALL_LEDS(0,255,0);
          delay((1+modeSpeed)*15);
      }
      
      
      if(btSerial.available() && !endMode){
          endMode = endModeCheck();
          if(endMode){
            return;
          }
      }else{
          ALL_LEDS(0,0,255);
          delay((1+modeSpeed)*15);
      }
      
      
      if(btSerial.available() && !endMode){
          endMode = endModeCheck();
          if(endMode){
            return;
          }
      }else{
          ALL_LEDS(255,255,0);
          delay((1+modeSpeed)*15);
      }
      
      
      if(btSerial.available() && !endMode){
          endMode = endModeCheck();
          if(endMode){
            return;
          }
      }else{
          ALL_LEDS(255,0,255);
          delay((1+modeSpeed)*15);
      }
      
      
      if(btSerial.available() && !endMode){
          endMode = endModeCheck();
          if(endMode){
            return;
          }
      }else{
          ALL_LEDS(0,255,255);
          delay((1+modeSpeed)*15);
      }
  }
}

void breathingMode(){
  boolean endMode = false;
  ALL_LEDS(255,0,0);
  int currentBrightnes = brightnes;
  counter = 0;
  while(!endMode){
    while(currentBrightnes!=0 && !endMode){
    if(btSerial.available() && !endMode){
          endMode = endModeCheck();
      }else{
          FastLED.setBrightness(currentBrightnes);
          FastLED.show();
          currentBrightnes--;
          delay((100+modeSpeed)/10);
      }
    }
    while(currentBrightnes!=brightnes && !endMode){
      if(btSerial.available() && !endMode){
          endMode = endModeCheck();
      }else{
          FastLED.setBrightness(currentBrightnes);
          FastLED.show();
          currentBrightnes++;
          delay((100+modeSpeed)/10);
      }
    }
  }
  FastLED.setBrightness(brightnes);
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
  int jump = 255/NUM_LEDS;
  int jump2 = ceil((double)255/(double)NUM_LEDS);
  int jump3 = NUM_LEDS/(255%NUM_LEDS);
  
    for( int i = 0; i < NUM_LEDS; ++i) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, 255, currentBlending);
        if(i%jump3==0){
          colorIndex += jump2;
        }else{
          colorIndex += jump;
        }
    }
}

void rainbow(CRGBPalette16 cp, TBlendType cb){
    currentPalette = cp;
    currentBlending = cb;
    
    boolean endMode = false;
    while(!endMode){
      if(btSerial.available() && !endMode){
          endMode = endModeCheck();
      }else{
          static uint8_t startIndex = 0;
          startIndex = startIndex + 1; /* motion speed */
          FillLEDsFromPaletteColors( startIndex);
          FastLED.show();
          delay(modeSpeed);
      }
    }
}
boolean fadeall() { 
  boolean endMode = false;
  for(int i = 0; i < NUM_LEDS; i++) {
    if(btSerial.available() && !endMode){
          endMode = endModeCheck();
          if(endMode){
            return endMode;
          }
      }else{
        leds[i].nscale8(250);
      }
  } 
  return endMode;
}

void ALL_BLACK(){
  for (int i = 0; i < NUM_LEDS; i++ )
  {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void pingPong(boolean isBlack){
  ALL_BLACK();
  boolean endMode = false;
  static uint8_t hue = 0;
  while(!endMode){
    for(int i = 0; i < NUM_LEDS; i++) {
      if(btSerial.available() && !endMode){
          endMode = endModeCheck();
          if(endMode){
            return;
          }
      }else{
        leds[i] = CHSV(hue++, 255, 255);
        FastLED.show(); 
        if(isBlack){
          leds[i] = CRGB::Black;
        }
        endMode = fadeall();
        delay(modeSpeed+10);
      }
      }
      if(!endMode){
        for(int i = (NUM_LEDS)-1; i >= 0; i--) {
        if(btSerial.available() && !endMode){
          endMode = endModeCheck();
          if(endMode){
            return;
          }
      }else{
        leds[i] = CHSV(hue++, 255, 255);
        FastLED.show();
        if(isBlack){
          leds[i] = CRGB::Black;
        }
        endMode = fadeall();
        delay(modeSpeed+10);
          }  
        }
      }
      
  } 
}

void sparkle(){
  boolean endMode = false;
  while(!endMode){
    if(btSerial.available() && !endMode){
          endMode = endModeCheck();
          if(endMode){
            return;
          }
    }
    int i = random(107);
    uint32_t color = random(16777215);
    strip.setPixelColor(i, color);
    strip.show();
    delay(modeSpeed);
    strip.setPixelColor(i, 0);
  }
  
}

void music(){
  boolean endMode = false;
  int brightnesCopy = brightnes;
  ALL_BLACK(); //black
  int counter = 0;
  while(!endMode){
    if(btSerial.available() && !endMode){
          endMode = endModeCheck();
          if(endMode){
            FastLED.setBrightness(brightnes);
            return;
          }
    }
    soundSensorValue = digitalRead(SOUND_SENDOR_PIN);
    if (soundSensorValue==0){ 
      FastLED.setBrightness(brightnes);
      brightnesCopy = brightnes;
      counter++;
    }  
    if (soundSensorValue==1){
      FastLED.setBrightness(brightnesCopy);
    }
    if(brightnesCopy>0){
      brightnesCopy=brightnesCopy-5;
    }else{
      ALL_LEDS(random(16777215));
      brightnesCopy=0;
    }
    delay(5);
    FastLED.show();
  }
  FastLED.setBrightness(brightnes);
}

void ambient(){
  boolean endMode = false;
  Serial.print("Ada\n");
  while(!endMode){
    for(i = 0; i < sizeof prefix; ++i) {
    waitLoop: while (!Serial.available()) ;;
    // Check next byte in Magic Word
    if(prefix[i] == Serial.read()) continue;
    // otherwise, start over
    i = 0;
    goto waitLoop;
  }
  
  // Hi, Lo, Checksum  
  while (!Serial.available()) ;;
  hi=Serial.read();
  while (!Serial.available()) ;;
  lo=Serial.read();
  while (!Serial.available()) ;;
  chk=Serial.read();
  
  // If checksum does not match go back to wait
  if (chk != (hi ^ lo ^ 0x55)) {
    i=0;
    goto waitLoop;
  }
  
  memset(leds, 0, NUM_LEDS * sizeof(struct CRGB));
  // Read the transmission data and set LED values
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    byte r, g, b;    
    while(!Serial.available());
    r = Serial.read();
    while(!Serial.available());
    g = Serial.read();
    while(!Serial.available());
    b = Serial.read();
    leds[i].r = r;
    leds[i].g = g;
    leds[i].b = b;
    if(btSerial.available() && !endMode){
          endMode = endModeCheck();
          if(endMode){
            return;
          }
    }
  }
  
  // Shows new values
  FastLED.show();
  } 
}

void changeMode(String newMode){
  int modeValue = constrain(newMode.toInt(),1,maxModes);
  switch(modeValue){
    case 1:
    fadeMode();
    break;
    
    case 2:
    rainbow(rainbowGradient,LINEARBLEND);
    break;
    
    case 3:
    breathingMode();
    break;
    
    case 4:
    rainbow(RainbowStripeColors_p,LINEARBLEND);
    break;

    case 5:
    rainbow(OceanColors_p,LINEARBLEND);
    break;

    case 6:
    flashMode();
    break;

    case 7:
    pingPong(true);
    break;

    case 8:
    pingPong(false);
    break;

    case 9:
    sparkle();
    break;

    case 10:
    music();
    break;

    case 11:
    ambient();
    break;
    
    default:
    break;
  }
}

void changeBrightnes(String newBrightnes){
  brightnes = constrain(newBrightnes.toInt(),0,255);
  
  FastLED.setBrightness(brightnes);
  FastLED.show();
}

void changeSpeed(String newSpeed){
  int speedValue = constrain(newSpeed.toInt(),0,maxSpeed);
  modeSpeed = speedValue;
}
void loop() 
{  
  if(btSerial.available()) {
    data = btSerial.read();
    switch(data){
      case 'T':
        isColor= true;
      break;
      case 'M':
        isMode = true;
      break;
      case 'B':
        isBrightnes = true;
      break;
      case 'S':
        isSpeed = true;
      break;
      case '\n':
        switchMode = true;
        btSerial.flush();
      break;
      default:
        if(data!= ' '){
          finString +=data;
        }else{
          if(isColor){
            switch(counter){
              case 0:
              red = finString;
              finString = "";
              counter++;
              break;
              case 1:
              green = finString;
              finString = "";
              counter++;
              break;
            }
          }
        }
      break;
    }
  }
  if(switchMode){
      if(isColor){
      changeColor(red,green,finString);
      resetValues();
      }
      if(isMode){
        isMode = false;
        changeMode(finString);
      }
      if(isBrightnes){
        changeBrightnes(finString);
        resetValues();
      }
      if(isSpeed){
        changeSpeed(finString);
        resetValues();
      }
    } 
  
}
