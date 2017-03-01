#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DEBUG 1

#define OLED_RESET 13
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

SoftwareSerial CraneSerial(8, 7); // RX, TX

void setup()   {                
  Serial.begin(19200);
  Serial1.begin(19200);
  //SerialUSB.begin(9600);
  CraneSerial.begin(9600);//9600 mqtt  19200 ws
#ifdef DEBUG
  Serial.println("WifiCard Start");
#endif

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  display.clearDisplay();  
  // text display tests
  display.setTextSize(2);
  display.setTextColor(BLACK, WHITE);
  display.setCursor(0,1);
  display.fillRect(0, 0, 128, 17, 1);
  display.println("  FEILOLI ");
  
  display.setTextColor( WHITE); // 'inverted' text
  display.println("Meter 1");
  display.setTextSize(2);
  display.println("OTG RDY");
  display.println("M");
  display.display();
  delay(2000);
}


void loop() {
  char temp;
  
  while (CraneSerial.available()) {
    temp=CraneSerial.read();
    Serial1.write(temp);
    Serial.write(temp);
  }
  /*
  while (Serial.available()) {
    temp=Serial.read();
    Serial1.write(temp);
    Serial.write(temp);
  }
  */
  while (Serial1.available()) {
    temp=Serial1.read();
    CraneSerial.write(temp);
    Serial.write(temp);
  }
}


