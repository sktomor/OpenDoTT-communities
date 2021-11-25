/* credits to sparkfun for this public domain code */

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI //Defines an if condition 
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0,
    /* clock=*/ SCL,
    /* data=*/ SDA,
    /* reset=*/ U8X8_PIN_NONE);

#include "HX711.h" //This library can be obtained here http://librarymanager/All#Avia_HX711

#define calibration_factor 516.5 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define LOADCELL_SCK_PIN   6
#define LOADCELL_DOUT_PIN  5

HX711 scale;

void setup() {
  Serial.begin(9600);
  Serial.println("HX711 scale demo");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare();  //Assuming there is no weight on the scale at start up, reset the scale to 0

  Serial.println("Readings:");

  u8g2.begin();
  u8g2.setDisplayRotation(U8G2_R2);          // rotations --> https://github.com/olikraus/u8g2/wiki/u8g2reference#setdisplayrotation
  u8g2.setFont(u8g2_font_fub11_tf);         // here --> https://github.com/olikraus/u8g2/wiki/fntlistall

}

void loop() {
  Serial.print("Reading: ");
  Serial.print(scale.get_units(), 0); //scale.get_units() returns a float
  Serial.print(" g"); 
  Serial.println();
  
  u8g2.drawStr(10,40, String( (int) scale.get_units()).c_str() ); // here --> https://github.com/olikraus/u8g2/wiki/u8g2reference#drawstr
  u8g2.sendBuffer();                         // transfer internal memory to the display

}
