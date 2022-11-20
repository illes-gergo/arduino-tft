#include <Adafruit_GFX.h>

#include <Adafruit_GFX.h>

#include <Adafruit_GFX.h> 
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>

MCUFRIEND_kbv tft;

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define SWAP(a, b) {uint16_t tmp = a; a = b; b = tmp;}
 uint8_t YP = A1;  // must be an analog pin, use "An" notation!
  uint8_t XM = A2;  // must be an analog pin, use "An" notation!
  uint8_t YM = 7;   // can be a digital pin
  uint8_t XP = 6;   // can be a digital pin
  uint8_t SwapXY = 0;

uint16_t TS_LEFT = 880;
uint16_t TS_RT  = 170;
uint16_t TS_TOP = 950;
uint16_t TS_BOT = 180;
  
  uint16_t identifier;
 TouchScreen ts = TouchScreen(XP, YP, XM, YM, 260);
  TSPoint tp;
uint8_t Orientation = 2;
int16_t PENRADIUS = 3;
   uint16_t tmp;
void setup(void) {
  // put your setup code here, to run once:
  tft.begin(9600);
  tft.reset();  
  identifier = tft.readID();
  switch (Orientation) {      // adjust for different aspects
        case 0:   break;        //no change,  calibrated for PORTRAIT
        case 1:   tmp = TS_LEFT, TS_LEFT = TS_BOT, TS_BOT = TS_RT, TS_RT = TS_TOP, TS_TOP = tmp;  break;
        case 2:   SWAP(TS_LEFT, TS_RT);  SWAP(TS_TOP, TS_BOT); break;
        case 3:   tmp = TS_LEFT, TS_LEFT = TS_TOP, TS_TOP = TS_RT, TS_RT = TS_BOT, TS_BOT = tmp;  break;
    }
  tft.begin(identifier); 
    tft.setRotation(Orientation);
  tft.fillScreen(BLACK);
  tft.fillRect(0,0,20,20,RED);
  Serial.begin(9600);
  delay(1000);
}
 uint16_t xpos, ypos;
void loop() {
  // put your main code here, to run repeatedly:
tp = ts.getPoint();
  pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    pinMode(XP, OUTPUT);
    pinMode(YM, OUTPUT);

if (tp.z>10){
  Serial.println(String(tp.x)+" "+String(tp.y)+" "+String(tp.z));
        xpos = map(tp.x, TS_LEFT, TS_RT, tft.width(), 0);
        ypos = map(tp.y, TS_TOP, TS_BOT, tft.height(), 0);
        Serial.println(String(xpos)+" "+String(ypos));
        Serial.println();
tft.fillCircle(xpos,ypos,((500-tp.z)/50),WHITE);
}
if(xpos <20 && ypos<20)
{
  tft.fillScreen(BLACK);
  tft.fillRect(0,0,20,20,RED);
  xpos = 100;
  ypos = 100;
}
//delay(1000);


}
