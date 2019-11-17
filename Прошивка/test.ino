 #include <FastLED.h>
 #define NUM_LEDS 4  //Количество светодиодов
#define LED_PIN    9 //Выход данных
 //Тактовый выход
 #define LED_TYPE    WS2811
 #define COLOR_ORDER GRB
 #define BRIGHTNESS  64
 byte outA=2,outB=3,outC=4,analogOut=5;

 byte inA=6,inB=7,inC=8,analogIn=0;

byte indicationMtrixNew[2][2]={
    {0,0},
    {0,0}
 
  
 };




CRGB leds[NUM_LEDS];// массив, где хранятся цвета каждого светодиода


void setup() {
  pinMode(outA, OUTPUT);//first mx/dc comtrol input
  pinMode(outB, OUTPUT);//
  pinMode(outC, OUTPUT);//
   pinMode(13, OUTPUT);//
  pinMode(analogOut, OUTPUT);//first mx/dc input sugnal
  pinMode(inA, OUTPUT);// 
  pinMode(inB, OUTPUT);//second mx/dc comtrol input
  pinMode(inC, OUTPUT);//
 FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
   Serial.begin(9600);
  
}

void demuxOut(int x, int u) {//u 0-255
   if (x&0x1){
    digitalWrite(outA,HIGH);
  //  Serial.print("h");
  }else{
    digitalWrite(outA,LOW);
 //   Serial.print("l");
  }
   if (x&0x2){
    digitalWrite(outB,HIGH);
 //   Serial.print("h");
  }else{
    digitalWrite(outB,LOW);
 //    Serial.print("l");
  }
   if (x&0x4){
    digitalWrite(outC,HIGH);
//    Serial.print("h");
  }else{
    digitalWrite(outC,LOW);
//     Serial.print("l");
  }
//  Serial.println("");
  analogWrite(analogOut, u);
}




byte demuxIn(int x) {//u 0-255
  if (x&0x1){
    digitalWrite(inA,HIGH);
//    Serial.print("h");
  }else{
    digitalWrite(inA,LOW);
  //   Serial.print("l");
  }
   if (x&0x2){
    digitalWrite(inB,HIGH);
//    Serial.print("h");
    
  }else{
    digitalWrite(inB,LOW);
 //    Serial.print("l");
  }
   if (x&0x4){
    digitalWrite(inC,HIGH);
//    Serial.print("h");
  }else{
    digitalWrite(inC,LOW);
 //   Serial.print("l");
  }
  delay(100);
  return analogRead(analogIn);
 //  Serial.println("");
}

byte getPos(byte y, byte x) {
  demuxOut(y, 255);
  
  if (demuxIn(x) > 100){
    return 1;
     Serial.println("h");
  }
  return 0;
}
void check(){
   Serial.println("check start ");
  for(int i=0;i<2;i++)
  {
    for(int j=0;j<2;j++)
    {
    indicationMtrixNew[i][j]=getPos(i,j);
   
    }
  }
   Serial.println("check out ");
}

void writeCom(){
  Serial.println(" write");
 for(int i=0;i<2;i++)
  {
    for(int j=0;j<2;j++)
    {
    if(indicationMtrixNew[i][j]==1){
      Serial.print("1");
    }else{
      Serial.print("0");
    }
    }
    Serial.println(" ");
  }
  
}

void writeLED(){
    leds[1]=CRGB::Red;
    FastLED.show();   
}
void loop() {

    leds[0]=CRGB::Red;
     leds[1]=CRGB::Red;
      leds[2]=CRGB::Red;
       leds[3]=CRGB::Red;
    FastLED.show();   
    
 // check();
 // writeCom();
 // digitalWrite(13,HIGH);
  //delay(1000);

 
 // writeLED();

            
}