
#include "Charliplexing.h"
#include "Font.h"
#include "Charliplexing.h"
#include "Font.h"
#include "Arduino.h"




 char readout[]="12345678";
int j=0;
boolean dunnit=false;



void setup()                   
{
  
   LedSign::Init();
  Serial.begin(9600);
}


void loop(){   

if (dunnit==true){
  
while (Serial.available()){

 readout[j]=Serial.read();j++;

}
 
 for (int t=0;t<j;t++){Serial.print (readout[t]);}j=0;dunnit=false;
 //for (int t=0;t<3;t++){j++;readout[j]=" ";}
}
if (dunnit==false){
  showit();
}}

void showit(){
  dunnit=true;
for (int8_t x=DISPLAY_COLS, i=0;; x--) {
   LedSign::Clear();
        for (int8_t x2=x, i2=i; x2<DISPLAY_COLS;) {
       int8_t w = Font::Draw(readout[i2], x2, 0);
       x2 += w, i2 = (i2+1)%strlen(readout);
       if (x2 <= 0)   // off the display completely?
      x = x2, i = i2;
   }
        delay(120);
    }

}

