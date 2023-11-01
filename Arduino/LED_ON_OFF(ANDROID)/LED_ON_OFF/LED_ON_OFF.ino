#include <FastLED.h>
#define NUM_LEDS 107
#define DATA_PIN 8
CRGB leds[NUM_LEDS];
int soundsensor = 8;
int counter = 0;

String finalString="";

byte brightness=150;
String Red="";
String Green="";
String Blue="";
String mode="";
byte table[300][3];
int mSpeed=15;
int mSpeed2=mSpeed*2;

void setup() 
{
  Serial.begin(9600);   
  LEDS.addLeds<WS2813,D8,GRB>(leds,NUM_LEDS);
  LEDS.setBrightness(150); 
  pinMode(soundsensor, INPUT);
}

int methodcheck(){
  char data=Serial.read();
  if (data=='$' or data=='&'){
    finalString=finalString+data;
  }else{
    if(Serial.available() > 6 || data=='#'){
      finalString=finalString+data;
      return 0;
    }
    else{
      while (Serial.available() > 0){ 
        data=Serial.read();
      }
      return 1;
    }
  }
  while (Serial.available() > 0){ 
  data=Serial.read();
  if (data == ' '){
      if (finalString.charAt(0)=='$'){
          finalString=finalString.substring(1,finalString.length());
          if (finalString.toInt()>=0 && finalString.toInt()<=10000){
            mSpeed=finalString.toInt();
            mSpeed2=finalString.toInt()*2;
          }
      }
      if (finalString.charAt(0)=='&'){
            finalString=finalString.substring(1,finalString.length());
            if (finalString.toInt()>=0 && finalString.toInt()<=255){
            LEDS.setBrightness(finalString.toInt());
            brightness = finalString.toInt();
            }
      }
  }else{
     finalString = finalString + data; 
  }
  }
  finalString="";
  return 1;
}

void ALL_LEDS (int red, int green, int blue)
{
  int ccc = 0;
  while(ccc!=NUM_LEDS)
  {
  leds[ccc] = CRGB(red, blue, green);
  ccc++;
  }
}

void flashing()
{
  int xxx=0;
  int b=1;
  while(b==1)
  {
    xxx=0;
  while(xxx!=10 && b!=0)
  {
    ALL_LEDS(255 , 0, 0);
    FastLED.show();
    delay(mSpeed);
    if(Serial.available() > 0){
          b=methodcheck();
        }
    xxx=xxx+1;
  }
  xxx=0;
  while(xxx!=10 && b!=0)
  {
    ALL_LEDS(255, 0, 255);
    FastLED.show();
    if(Serial.available() > 0){
          b=methodcheck();
        }
    delay(mSpeed);
    xxx=xxx+1;
  }
  xxx=0;
  while(xxx!=10 && b!=0)
  {
    ALL_LEDS(0, 0, 255);
    FastLED.show();
    delay(mSpeed);
    if(Serial.available() > 0){
          b=methodcheck();
        }
    xxx=xxx+1;
  }
  xxx=0;
  while(xxx!=10 && b!=0)
  {
    ALL_LEDS(0, 255, 255);
    FastLED.show();
    delay(mSpeed);
    if(Serial.available() > 0){
          b=methodcheck();
        }
    xxx=xxx+1;
  }
  xxx=0;
  while(xxx!=10 && b!=0)
  {
    ALL_LEDS(0, 255, 0);
    FastLED.show();
    delay(mSpeed);
    if(Serial.available() > 0){
          b=methodcheck();
        }
    xxx=xxx+1;
  }
  xxx=0;
  while(xxx!=10 && b!=0)
  {
    ALL_LEDS(255, 255, 0);
    FastLED.show();
    delay(mSpeed);
    if(Serial.available() > 0){
          b=methodcheck();
        }
    xxx=xxx+1;
  }
  }
}

void music()
{
  int x = 0;
  int gg = 0;
  int g = 0;
  int y = 0;
  int yhy = 0;
  int q=0;
  while(x!=NUM_LEDS)
  {
    leds[x]=CRGB(0, 0, 0);
    x=x+1;
  }
  int b=1;
  while(b==1)
  {
  int sensorvalue = digitalRead(soundsensor);
  x = 16; 
  y = 88;
  if (sensorvalue==1)                                    
  { 
    leds[x]=CRGB(0,255,0);//1
    leds[x+1]=CRGB(0,255,100);//2
    leds[x+2]=CRGB(0,255,150);//3
    leds[x+3]=CRGB(0,255,200);//4
    leds[x+4]=CRGB(0,255,255);//5
    leds[x+5]=CRGB(0,180,255);//6
    leds[x+6]=CRGB(0,100,255);//7
    leds[x+7]=CRGB(0,80,255);//8
    leds[x+8]=CRGB(0,40,255);//9
    leds[x+9]=CRGB(0,20,255);//10
    leds[x+10]=CRGB(0,0,255);//1
    leds[x+11]=CRGB(20,0,255);//12
    leds[x+12]=CRGB(40,0,255);//13
    leds[x+13]=CRGB(80,0,255);//14
    leds[x+14]=CRGB(120,0,255);//15
    leds[x+15]=CRGB(190,0,255);//16
    leds[x+16]=CRGB(255,0,255);//17
    leds[x+17]=CRGB(255,0,220);//18
    leds[x+18]=CRGB(255,0,200);//19
    leds[x+19]=CRGB(255,0,180);//20
    leds[y]=CRGB(0,255,0);//1
    leds[y-1]=CRGB(0,255,100);//2
    leds[y-2]=CRGB(0,255,150);//3
    leds[y-3]=CRGB(0,255,200);//4
    leds[y-4]=CRGB(0,255,255);//5
    leds[y-5]=CRGB(0,180,255);//6
    leds[y-6]=CRGB(0,100,255);//7
    leds[y-7]=CRGB(0,80,255);//8
    leds[y-8]=CRGB(0,40,255);//9
    leds[y-9]=CRGB(0,20,255);//10
    leds[y-10]=CRGB(0,0,255);//1
    leds[y-11]=CRGB(20,0,255);//12
    leds[y-12]=CRGB(40,0,255);//13
    leds[y-13]=CRGB(80,0,255);//14
    leds[y-14]=CRGB(120,0,255);//15
    leds[y-15]=CRGB(190,0,255);//16
    leds[y-16]=CRGB(255,0,255);//17
    leds[y-17]=CRGB(255,0,220);//18
    leds[y-18]=CRGB(255,0,200);//19
    leds[y-19]=CRGB(255,0,180);//20

    FastLED.show();
    if(q==0)
    {
      delay(1000);
      q=1;
    }
    delay(mSpeed);
    if(Serial.available() > 0){
          b=methodcheck();
        }
  x=0;
  y=193;
  g=0;
  gg=0; 
  }  
  if (sensorvalue==0)  
  {
    if(gg>=67)
    {
      gg=0;
    }   
    int red = 0;
    int green = 0;
    int blue = 0;
    leds[35-gg]=CRGB(red, blue, green);
    leds[69+gg]=CRGB(red, blue, green);     
    gg=gg+1;
    FastLED.show();
    delay(mSpeed);
    if(Serial.available() > 0){
          b=methodcheck();
        }
  }
  g=g+1;
  yhy=yhy+1;
  }
}

void fade()
{
  int b=1;
  int red=255;
  int green=0;
  int blue=0;
  int zza=0;
  bool quit=false;
  while(b==1)
  {
    while (blue !=255 && b!=0)
    {
        blue = blue + 1;
        ALL_LEDS(red, blue, green);
        FastLED.show();
        if(zza<=100)
        {
        delay(mSpeed);        
        }
        else
        {
        delay(mSpeed);
        }
        zza=zza+1;

        if(Serial.available() > 0){
          b=methodcheck();

        }

    }
    zza=0;
    while(red !=0 && b!=0)
    { 
        red = red - 1;
        ALL_LEDS(red, blue, green);
        FastLED.show();
        if(zza>=200)
        {
        delay(mSpeed2);    
        }
        else
        {
        delay(mSpeed);
        }
        zza=zza+1;

        if(Serial.available() > 0){
          b=methodcheck();

        }


    }
    zza=0;
    while(green !=255 && b!=0)
    {
        green = green + 1;
        ALL_LEDS(red, blue, green);
        FastLED.show();
        if(zza<=100)
        {
        delay(mSpeed2);        
        }
        else
        {
        delay(mSpeed);
        }   
        zza=zza+1; 

        if(Serial.available() > 0){
          b=methodcheck();

        }

    } 
    zza=0;
    while(blue !=0 && b!=0)
    {
        
        blue = blue - 1;
        ALL_LEDS(red, blue, green);
        FastLED.show();
        if(zza>=200)
        {
        delay(mSpeed2);    
        }
        else
        {
        delay(mSpeed);
        }
        zza=zza+1;

        if(Serial.available() > 0){
          b=methodcheck();
          
        }


    } 
    zza=0;        
    while(red !=255 && b!=0)
    {
        red = red + 1;
        ALL_LEDS(red, blue, green);
        FastLED.show();
        if(zza<=100)
        {
        delay(mSpeed2);        
        }
        else
        {
        delay(mSpeed);
        }
        zza=zza+1;

        if(Serial.available() > 0){
          b=methodcheck();
        }
    } 
    zza = 0; 
    while(green !=0 && b!=0)
    {  
        green = green - 1;
        ALL_LEDS(red, blue, green);
        FastLED.show();
        zza=zza+1;
        if(zza>=200)
        {
        delay(mSpeed2);         
        }
        else
        {
        delay(mSpeed);
        }
        zza=zza+1;
        if(Serial.available() > 0){
          b=methodcheck();
        }
    }

    zza=0;
  }
}

int licz(int a)
{
   while(a >= NUM_LEDS)
   {
    a = a - NUM_LEDS;
   }
   return a;
}


void rainbow(){
  int b=1;
  int y=0;
  while(b==1)
    {
        leds[licz(y +   0  )] = CRGB( 255 , 7 , 0 );
        leds[licz(y +   1  )] = CRGB( 255 , 11 , 0 );
        leds[licz(y +   2  )] = CRGB( 255 , 22 , 0 );
        leds[licz(y +   3  )] = CRGB( 255 , 33 , 0 );
        leds[licz(y +   4  )] = CRGB( 255 , 44 , 0 );
        leds[licz(y +   5  )] = CRGB( 255 , 75 , 0 );
        leds[licz(y +   6  )] = CRGB( 255 , 85 , 0 );
        leds[licz(y +   7  )] = CRGB( 255 , 95 , 0 );
        leds[licz(y +   8  )] = CRGB( 255 , 105 , 0 );
        leds[licz(y +   9  )] = CRGB( 255 , 115 , 0 );
        leds[licz(y +   10  )] = CRGB( 255 , 125 , 0 );
        leds[licz(y +   11  )] = CRGB( 255 , 135 , 0 );
        leds[licz(y +   12  )] = CRGB( 255 , 145 , 0 );
        leds[licz(y +   13  )] = CRGB( 255 , 155 , 0 );
        leds[licz(y +   14  )] = CRGB( 255 , 155 , 0 );
        leds[licz(y +   15  )] = CRGB( 255 , 168 , 0 );
        leds[licz(y +   16  )] = CRGB( 255 , 182 , 0 );
        leds[licz(y +   17  )] = CRGB( 255 , 196 , 0 );
        leds[licz(y +   18  )] = CRGB( 255 , 255 , 0 );
        leds[licz(y +   19  )] = CRGB( 244 , 255 , 0 );
        leds[licz(y +   20  )] = CRGB( 233 , 255 , 0 );
        leds[licz(y +   21  )] = CRGB( 222 , 255 , 0 );
        leds[licz(y +   22  )] = CRGB( 211 , 255 , 0 );
        leds[licz(y +   23  )] = CRGB( 155 , 255 , 0 );
        leds[licz(y +   24  )] = CRGB( 145 , 255 , 0 );
        leds[licz(y +   25  )] = CRGB( 135 , 255 , 0 );
        leds[licz(y +   26  )] = CRGB( 125 , 255 , 0 );
        leds[licz(y +   27  )] = CRGB( 115 , 255 , 0 );
        leds[licz(y +   28  )] = CRGB( 105 , 255 , 0 );
        leds[licz(y +   29  )] = CRGB( 95 , 255 , 0 );
        leds[licz(y +   30  )] = CRGB( 85 , 255 , 0 );
        leds[licz(y +   31  )] = CRGB( 75 , 255 , 0 );
        leds[licz(y +   32  )] = CRGB( 55 , 255 , 0 );
        leds[licz(y +   33  )] = CRGB( 42 , 255 , 0 );
        leds[licz(y +   34  )] = CRGB( 28 , 255 , 0 );
        leds[licz(y +   35  )] = CRGB( 14 , 255 , 0 );
        leds[licz(y +   36  )] = CRGB( 0 , 255 , 0 );
        leds[licz(y +   37  )] = CRGB( 0 , 255 , 13 );
        leds[licz(y +   38  )] = CRGB( 0 , 255 , 27 );
        leds[licz(y +   39  )] = CRGB( 0 , 255 , 41 );
        leds[licz(y +   40  )] = CRGB( 0 , 255 , 75 );
        leds[licz(y +   41  )] = CRGB( 0 , 255 , 85 );
        leds[licz(y +   42  )] = CRGB( 0 , 255 , 95 );
        leds[licz(y +   43  )] = CRGB( 0 , 255 , 105 );
        leds[licz(y +   44  )] = CRGB( 0 , 255 , 115 );
        leds[licz(y +   45  )] = CRGB( 0 , 255 , 125 );
        leds[licz(y +   46  )] = CRGB( 0 , 255 , 135 );
        leds[licz(y +   47  )] = CRGB( 0 , 255 , 145 );
        leds[licz(y +   48  )] = CRGB( 0 , 255 , 155 );
        leds[licz(y +   49  )] = CRGB( 0 , 255 , 155 );
        leds[licz(y +   50  )] = CRGB( 0 , 255 , 168 );
        leds[licz(y +   51  )] = CRGB( 0 , 255 , 182 );
        leds[licz(y +   52  )] = CRGB( 0 , 255 , 196 );
        leds[licz(y +   53  )] = CRGB( 0 , 255 , 255 );
        leds[licz(y +   54  )] = CRGB( 0 , 242 , 255 );
        leds[licz(y +   55  )] = CRGB( 0 , 228 , 255 );
        leds[licz(y +   56  )] = CRGB( 0 , 214 , 255 );
        leds[licz(y +   57  )] = CRGB( 0 , 155 , 255 );
        leds[licz(y +   58  )] = CRGB( 0 , 145 , 255 );
        leds[licz(y +   59  )] = CRGB( 0 , 135 , 255 );
        leds[licz(y +   60  )] = CRGB( 0 , 125 , 255 );
        leds[licz(y +   61  )] = CRGB( 0 , 115 , 255 );
        leds[licz(y +   62  )] = CRGB( 0 , 105 , 255 );
        leds[licz(y +   63  )] = CRGB( 0 , 95 , 255 );
        leds[licz(y +   64  )] = CRGB( 0 , 85 , 255 );
        leds[licz(y +   65  )] = CRGB( 0 , 75 , 255 );
        leds[licz(y +   66  )] = CRGB( 0 , 55 , 255 );
        leds[licz(y +   67  )] = CRGB( 0 , 42 , 255 );
        leds[licz(y +   68  )] = CRGB( 0 , 28 , 255 );
        leds[licz(y +   69  )] = CRGB( 0 , 14 , 255 );
        leds[licz(y +   70  )] = CRGB( 0 , 0 , 255 );
        leds[licz(y +   71  )] = CRGB( 11 , 0 , 255 );
        leds[licz(y +   72  )] = CRGB( 22 , 0 , 255 );
        leds[licz(y +   73  )] = CRGB( 33 , 0 , 255 );
        leds[licz(y +   74  )] = CRGB( 44 , 0 , 255 );
        leds[licz(y +   75  )] = CRGB( 75 , 0 , 255 );
        leds[licz(y +   76  )] = CRGB( 85 , 0 , 255 );
        leds[licz(y +   77  )] = CRGB( 95 , 0 , 255 );
        leds[licz(y +   78  )] = CRGB( 105 , 0 , 255 );
        leds[licz(y +   79  )] = CRGB( 115 , 0 , 255 );
        leds[licz(y +   80  )] = CRGB( 125 , 0 , 255 );
        leds[licz(y +   81  )] = CRGB( 135 , 0 , 255 );
        leds[licz(y +   82  )] = CRGB( 145 , 0 , 255 );
        leds[licz(y +   83  )] = CRGB( 155 , 0 , 255 );
        leds[licz(y +   84  )] = CRGB( 155 , 0 , 255 );
        leds[licz(y +   85  )] = CRGB( 168 , 0 , 255 );
        leds[licz(y +   86  )] = CRGB( 182 , 0 , 255 );
        leds[licz(y +   87  )] = CRGB( 196 , 0 , 255 );
        leds[licz(y +   88  )] = CRGB( 255 , 0 , 255 );
        leds[licz(y +   89  )] = CRGB( 255 , 0 , 242 );
        leds[licz(y +   90  )] = CRGB( 255 , 0 , 228 );
        leds[licz(y +   91  )] = CRGB( 255 , 0 , 214 );
        leds[licz(y +   92  )] = CRGB( 255 , 0 , 155 );
        leds[licz(y +   93  )] = CRGB( 255 , 0 , 145 );
        leds[licz(y +   94  )] = CRGB( 255 , 0 , 135 );
        leds[licz(y +   95  )] = CRGB( 255 , 0 , 125 );
        leds[licz(y +   96  )] = CRGB( 255 , 0 , 115 );
        leds[licz(y +   97  )] = CRGB( 255 , 0 , 105 );
        leds[licz(y +   98  )] = CRGB( 255 , 0 , 88 );
        leds[licz(y +   99  )] = CRGB( 255 , 0 , 66 );
        leds[licz(y +   100  )] = CRGB( 255 , 0 , 44 );
        leds[licz(y +   101  )] = CRGB( 255 , 0 , 33 );
        leds[licz(y +   102  )] = CRGB( 255 , 0 , 12 );
        leds[licz(y +   103  )] = CRGB( 255 , 0 , 9 );
        leds[licz(y +   104  )] = CRGB( 255 , 0 , 7 );
        leds[licz(y +   105  )] = CRGB( 255 , 0 , 5 );
        FastLED.show();
        y=y+1;
        if(y==NUM_LEDS)
        {
        y=0; 
        }
        delay(mSpeed);
        if(Serial.available() > 0){
          b=methodcheck();
        }
    }  
}

void breathing(){
  int b=1;
  byte bright=brightness;
  bool state=true;
  while(b==1){
    if(bright==0){
     state=false;
    }
    if(bright==brightness){
      state=true;
    }
    ALL_LEDS(Red.toInt(),Green.toInt(),Blue.toInt());
    LEDS.setBrightness(bright);
    FastLED.show();
    if(state){
      bright=bright-1;
    }else{
      bright=bright+1;
    }
    delay(mSpeed);
    if(Serial.available() > 0){
          b=methodcheck();
    }
  }
  LEDS.setBrightness(brightness);
}

void loop() 
{
  char data;  
  bool space=false;
  if(Serial.available() > 0) 
  {
    data=Serial.read();
    
    if (data == ' '){
      if (finalString.charAt(0)!='#' && finalString.charAt(0)!='$' && finalString.charAt(0)!='&'){
          if (counter==0){
            Red = finalString;
            finalString="";
          }
          if (counter==1){
            Green = finalString;
            finalString="";
          }
          if (counter==2){
            Blue = finalString;
            finalString="";
          }
          counter=counter+1;
      }
      if (finalString.charAt(0)=='#' || finalString.charAt(0)=='$' || finalString.charAt(0)=='&'){
            if (counter==0){
            mode = finalString;
            finalString="";
            }
            counter=counter+1;
      }
  }else{
     finalString = finalString + data; 
  }
  }

  if (counter==1 && mode.charAt(0)=='#'){
    mode=mode.substring(1,2);
    switch(mode.toInt())
        {
          case 0:
            rainbow();
            break;
          case 1:
            fade();
            break;
          case 2:
            flashing();
            break;
          case 3:
            music();
            break;
          case 4:
            breathing();
            break;
        }
        counter=0;
        mode ="";
    
  }
  if (counter==1 && mode.charAt(0)=='&'){
    mode=mode.substring(1,(mode.length())); 
    LEDS.setBrightness(mode.toInt());
    brightness = mode.toInt();
    FastLED.show();
    counter=0;
    mode ="";
  }
  if (counter==1 && mode.charAt(0)=='$'){
      mode=mode.substring(1,(mode.length()));
      mSpeed=mode.toInt();
      mSpeed2=mode.toInt()*2;
      counter=0;
      mode ="";
  }
  
  if (counter==3){
    ALL_LEDS(Red.toInt(),Green.toInt(),Blue.toInt());
    FastLED.show();
    counter=0;
  }
}
