#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>

//define the LED pins on Arduino
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7
#define PIN8 8
#define PIN9 9
#define PIN10 10

//the delay time
#define wait 50

//Tshirt User ID
const int tshirtID = 9794;

//counter from the server
long counter=0;
char buffer[6];
String readString = String(10);

//define pressure sensor pin and value
const int velostat_pin = A0;
int pressValue = 0;

//define digit variables
int first_digit = 0;
int sec_digit = 0;
int third_digit = 0;

//define LED pixels arrays
int led2[15];
int led3[15];
int led4[15];
int led5[15];
int led6[15];
int led7[15];
int led8[15];
int led9[15];
int led10[15];

//define LED strips variables
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(15, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(15, PIN3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(15, PIN4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(15, PIN5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip6 = Adafruit_NeoPixel(15, PIN6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip7 = Adafruit_NeoPixel(15, PIN7, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip8 = Adafruit_NeoPixel(15, PIN8, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip9 = Adafruit_NeoPixel(15, PIN9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip10 = Adafruit_NeoPixel(15, PIN10, NEO_GRB + NEO_KHZ800);

//int count =0;


//Timout for preventing double-touch. 09/03/2014
unsigned long  lastTouchms;
#define minTouchSpan 2000

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(50);
  
  //initilize the led arrays
  for(int i=0; i< strip2.numPixels(); i++) {
    led2[i]=i;
    led3[i]=i;
    led4[i]=i;
    led5[i]=i;
    led6[i]=i;
    led7[i]=i;
    led8[i]=i;
    led9[i]=i;
    led10[i]=i;
  }
  
  strip2.begin();
  strip3.begin();
  strip4.begin();
  strip5.begin();
  strip6.begin();
  strip7.begin();
  strip8.begin();
  strip9.begin();
  strip10.begin();
  
  ShowOnLED();
  
  pinMode(velostat_pin, INPUT_PULLUP);
  
//Timout for preventing double-touch. 09/03/2014
  lastTouchms = 0;
}

void loop() {
  
  delay(50);
  //read from pressure sensor
  pressValue = analogRead(velostat_pin);
  
//Timout for preventing double-touch. 09/03/2014
  unsigned long cTime = millis();  
  //if the pressure is noticeable
  if(cTime - lastTouchms > minTouchSpan && pressValue < 43) {
    //send the ID to the server via bluetooth
    Serial.println(tshirtID);
    lastTouchms = cTime;
    delay(250);
  }//if pressValue
  
    
  while(Serial.available()) {
    
     
     char temp = (char)Serial.read();
     readString += temp;
    
      if(temp == '\n'){
  
        if(readString.length() > 0){
        readString.toCharArray(buffer, sizeof(buffer));
        counter = atoi(buffer);
   
         }
      
      }
    
  
    //if the number has 1 digit
      if(counter < 10) {
        //first_digit = counter;
        sec_digit = 0;
        third_digit = 0;
        ClearScreen(5);
        ClearScreen(10);
        //ClearScreen(0);
        DigitOnScreen(counter, 0);
        ClearScreen(5);
        ClearScreen(10);
        //delay(wait);
     
      
    }
    else if(counter >= 10) {
      //if the number has 2 digits
      if(counter < 100) {
        first_digit = counter % 10;
        sec_digit = counter / 10;
        DigitOnScreen(first_digit, 0);
        DigitOnScreen(sec_digit, 5);
      }
      //if the number has 3 digits
      else {
        first_digit = counter % 10;
        sec_digit = (counter % 100) / 10;
        third_digit = counter / 100;
        DigitOnScreen(first_digit, 0);
        DigitOnScreen(sec_digit, 5);
        DigitOnScreen(third_digit, 10);
      }
    }
   
   }

  Serial.flush();
  readString = "";   
    
      
}//loop


//show numbers on LED
void DigitOnScreen(int nthDigit, int start_point) {
  
  switch(nthDigit) {
    case 0:
      ClearScreen(start_point);
      for(int i=start_point; i<start_point+4; i++) {
        strip2.setPixelColor(led2[i], strip2.Color(0,0,255)); //gray
        strip10.setPixelColor(led10[i], strip10.Color(0,0,255));
        if(i == start_point) {
          strip3.setPixelColor(led3[i], strip3.Color(0,0,255));
          strip4.setPixelColor(led4[i], strip4.Color(0,0,255));
          strip5.setPixelColor(led5[i], strip5.Color(0,0,255));
          strip6.setPixelColor(led6[i], strip6.Color(0,0,255));
          strip7.setPixelColor(led7[i], strip7.Color(0,0,255));
          strip8.setPixelColor(led8[i], strip8.Color(0,0,255));
          strip9.setPixelColor(led9[i], strip9.Color(0,0,255));
        }
        if(i == start_point+3) {
          strip3.setPixelColor(led3[i], strip3.Color(0,0,255));
          strip4.setPixelColor(led4[i], strip4.Color(0,0,255));
          strip5.setPixelColor(led5[i], strip5.Color(0,0,255));
          strip6.setPixelColor(led6[i], strip6.Color(0,0,255));
          strip7.setPixelColor(led7[i], strip7.Color(0,0,255));
          strip8.setPixelColor(led8[i], strip8.Color(0,0,255));
          strip9.setPixelColor(led9[i], strip9.Color(0,0,255));
      }
      }
      
      ShowOnLED();
      //delay(1);
      break;
      
    case 1:
      ClearScreen(start_point);
      strip2.setPixelColor(led2[start_point+2], strip2.Color(0,0,255));
      strip3.setPixelColor(led3[start_point+2], strip3.Color(0,0,255));
      strip4.setPixelColor(led4[start_point+2], strip4.Color(0,0,255));
      strip5.setPixelColor(led5[start_point+2], strip5.Color(0,0,255));
      strip6.setPixelColor(led6[start_point+2], strip6.Color(0,0,255));
      strip7.setPixelColor(led7[start_point+2], strip7.Color(0,0,255));
      strip8.setPixelColor(led8[start_point+2], strip8.Color(0,0,255));
      strip9.setPixelColor(led9[start_point+2], strip9.Color(0,0,255));
      strip10.setPixelColor(led10[start_point+2], strip10.Color(0,0,255));
      
      ShowOnLED();
      delay(wait);
      break;
      
    case 2:
      ClearScreen(start_point);
      for(int i=start_point; i< start_point+4; i++) {
        strip2.setPixelColor(led2[i], strip2.Color(0,0,255));
        strip6.setPixelColor(led6[i], strip6.Color(0,0,255));
         strip10.setPixelColor(led10[i], strip10.Color(0,0,255));
        if(i == start_point+3) {
          strip7.setPixelColor(led7[i], strip7.Color(0,0,255));
          strip8.setPixelColor(led8[i], strip8.Color(0,0,255));
          strip9.setPixelColor(led9[i], strip9.Color(0,0,255));
        }
        if(i == start_point) {
          strip3.setPixelColor(led3[i], strip3.Color(0,0,255));
          strip4.setPixelColor(led4[i], strip4.Color(0,0,255));
          strip5.setPixelColor(led5[i], strip5.Color(0,0,255));
        }
      }
      ShowOnLED();
      delay(wait);
      break;
      
    case 3:
      ClearScreen(start_point);
      for(int i=start_point; i<start_point+4; i++) {
        strip2.setPixelColor(led2[i], strip2.Color(0,0,255));
        strip6.setPixelColor(led6[i], strip6.Color(0,0,255));
        strip10.setPixelColor(led10[i], strip10.Color(0,0,255));
        if(i == start_point) {
          strip3.setPixelColor(led3[i], strip3.Color(0,0,255));
          strip4.setPixelColor(led4[i], strip4.Color(0,0,255));
          strip5.setPixelColor(led5[i], strip5.Color(0,0,255));
          strip7.setPixelColor(led7[i], strip7.Color(0,0,255));
          strip8.setPixelColor(led8[i], strip8.Color(0,0,255));
          strip9.setPixelColor(led9[i], strip9.Color(0,0,255));
        }
      }
      ShowOnLED();
      delay(wait);
      break;
      
    case 4:
      ClearScreen(start_point);
      for(int i=start_point; i<start_point+4; i++) {
        strip6.setPixelColor(led6[i], strip6.Color(0,0,255));
        if( i == start_point) {
          strip2.setPixelColor(led2[i], strip2.Color(0,0,255));
          strip3.setPixelColor(led3[i], strip3.Color(0,0,255));
          strip4.setPixelColor(led4[i], strip4.Color(0,0,255));
          strip5.setPixelColor(led5[i], strip5.Color(0,0,255));
          strip7.setPixelColor(led7[i], strip7.Color(0,0,255));
          strip8.setPixelColor(led8[i], strip8.Color(0,0,255));
          strip9.setPixelColor(led9[i], strip9.Color(0,0,255));
          strip10.setPixelColor(led10[i], strip10.Color(0,0,255));
        }
        if( i == start_point+3) {
          strip2.setPixelColor(led2[i], strip2.Color(0,0,255));
          strip3.setPixelColor(led3[i], strip3.Color(0,0,255));
          strip4.setPixelColor(led4[i], strip4.Color(0,0,255));
          strip5.setPixelColor(led5[i], strip5.Color(0,0,255));
        }
      }
      ShowOnLED();
      delay(wait);
      break;
      
    case 5:
      ClearScreen(start_point);
      for(int i=start_point; i<start_point+4; i++) {
        strip2.setPixelColor(led2[i], strip2.Color(0,0,255));
        strip6.setPixelColor(led6[i], strip6.Color(0,0,255));
        strip10.setPixelColor(led10[i], strip10.Color(0,0,255));
        if(i == start_point+3) {
          strip3.setPixelColor(led3[i], strip3.Color(0,0,255));
          strip4.setPixelColor(led4[i], strip4.Color(0,0,255));
          strip5.setPixelColor(led5[i], strip5.Color(0,0,255));
        }
        if(i == start_point) {
          strip7.setPixelColor(led7[i], strip7.Color(0,0,255));
          strip8.setPixelColor(led8[i], strip8.Color(0,0,255));
          strip9.setPixelColor(led9[i], strip9.Color(0,0,255));
        }
      }
      ShowOnLED();
      delay(wait);
      break;
      
    case 6:
      ClearScreen(start_point);
      for(int i=start_point; i<start_point+4; i++) {
        strip2.setPixelColor(led2[i], strip2.Color(0,0,255));
        strip6.setPixelColor(led6[i], strip6.Color(0,0,255));
        strip10.setPixelColor(led10[i], strip10.Color(0,0,255));
        if(i == start_point+3) {
          strip3.setPixelColor(led3[i], strip3.Color(0,0,255));
          strip4.setPixelColor(led4[i], strip4.Color(0,0,255));
          strip5.setPixelColor(led5[i], strip5.Color(0,0,255));
          strip7.setPixelColor(led7[i], strip7.Color(0,0,255));
          strip8.setPixelColor(led8[i], strip8.Color(0,0,255));
          strip9.setPixelColor(led9[i], strip9.Color(0,0,255));
        }
        if(i == start_point) {
          strip7.setPixelColor(led7[i], strip7.Color(0,0,255));
          strip8.setPixelColor(led8[i], strip8.Color(0,0,255));
          strip9.setPixelColor(led9[i], strip9.Color(0,0,255));
        }
      }
      ShowOnLED();
      delay(wait);
      break;
      
    case 7:
      ClearScreen(start_point);
      for(int i=start_point; i<start_point+4; i++) {
        strip2.setPixelColor(led2[i], strip2.Color(0,0,255));
        if(i == start_point) {
          strip10.setPixelColor(led10[i], strip10.Color(0,0,255));
          strip3.setPixelColor(led3[i], strip3.Color(0,0,255));
          strip4.setPixelColor(led4[i], strip4.Color(0,0,255));
          strip5.setPixelColor(led5[i], strip5.Color(0,0,255));
          strip6.setPixelColor(led6[i], strip6.Color(0,0,255));
          strip7.setPixelColor(led7[i], strip7.Color(0,0,255));
          strip8.setPixelColor(led8[i], strip8.Color(0,0,255));
          strip9.setPixelColor(led9[i], strip9.Color(0,0,255));
         
        }
      }
      ShowOnLED();
      delay(wait);
      break;
      
    case 8:
      ClearScreen(start_point);
      for(int i=start_point; i< start_point+4; i++) {
        strip2.setPixelColor(led2[i], strip2.Color(0,0,255));
        strip6.setPixelColor(led6[i], strip6.Color(0,0,255));
        strip10.setPixelColor(led10[i], strip10.Color(0,0,255));
        if(i == start_point) {
          strip3.setPixelColor(led3[i], strip3.Color(0,0,255));
          strip4.setPixelColor(led4[i], strip4.Color(0,0,255));
          strip5.setPixelColor(led5[i], strip5.Color(0,0,255));
          strip7.setPixelColor(led7[i], strip7.Color(0,0,255));
          strip8.setPixelColor(led8[i], strip8.Color(0,0,255));
          strip9.setPixelColor(led9[i], strip9.Color(0,0,255));
        }
        if(i == start_point+3) {
          strip3.setPixelColor(led3[i], strip3.Color(0,0,255));
          strip4.setPixelColor(led4[i], strip4.Color(0,0,255));
          strip5.setPixelColor(led5[i], strip5.Color(0,0,255));
          strip7.setPixelColor(led7[i], strip7.Color(0,0,255));
          strip8.setPixelColor(led8[i], strip8.Color(0,0,255));
          strip9.setPixelColor(led9[i], strip9.Color(0,0,255));
        }
      }
      ShowOnLED();
      delay(wait);
      break;
      
    case 9:
      ClearScreen(start_point);
      for(int i=start_point; i<start_point+4; i++) {
        strip6.setPixelColor(led6[i], strip6.Color(0,0,255));
        strip2.setPixelColor(led2[i], strip2.Color(0,0,255));
        if(i == start_point+3) {
          strip3.setPixelColor(led3[i], strip3.Color(0,0,255));
          strip4.setPixelColor(led4[i], strip4.Color(0,0,255));
          strip5.setPixelColor(led5[i], strip5.Color(0,0,255));
        }
        if(i == start_point) {
          strip10.setPixelColor(led10[i], strip10.Color(0,0,255));
          strip3.setPixelColor(led3[i], strip3.Color(0,0,255));
          strip4.setPixelColor(led4[i], strip4.Color(0,0,255));
          strip5.setPixelColor(led5[i], strip5.Color(0,0,255));
          strip7.setPixelColor(led7[i], strip7.Color(0,0,255));
          strip8.setPixelColor(led8[i], strip8.Color(0,0,255));
          strip9.setPixelColor(led9[i], strip9.Color(0,0,255));
        }
      }
      ShowOnLED();
      delay(wait);
      break;
      
  }//switch
  
}//DigitOnScreen


//clear the screen
void ClearScreen(int start_point) {
  for(int i =start_point; i<start_point+4; i++) {
    strip2.setPixelColor(led2[i], strip2.Color(0,0,0));
    strip3.setPixelColor(led3[i], strip3.Color(0,0,0));
    strip4.setPixelColor(led4[i], strip4.Color(0,0,0));
    strip5.setPixelColor(led5[i], strip5.Color(0,0,0));
    strip6.setPixelColor(led6[i], strip6.Color(0,0,0));
    strip7.setPixelColor(led7[i], strip7.Color(0,0,0));
    strip8.setPixelColor(led8[i], strip8.Color(0,0,0));
    strip9.setPixelColor(led9[i], strip9.Color(0,0,0));
    strip10.setPixelColor(led10[i], strip10.Color(0,0,0));
    }
    ShowOnLED();
    //delay(wait);
}


// push data to LED
void ShowOnLED() {
  
  strip2.setBrightness(128);
  strip3.setBrightness(128);
  strip4.setBrightness(128);
  strip5.setBrightness(128);
  strip6.setBrightness(128);
  strip7.setBrightness(128);
  strip8.setBrightness(128);
  strip9.setBrightness(128);
  strip10.setBrightness(128);
  
  strip2.show();
  strip3.show();
  strip4.show();
  strip5.show();
  strip6.show();
  strip7.show();
  strip8.show();
  strip9.show();
  strip10.show();
}




