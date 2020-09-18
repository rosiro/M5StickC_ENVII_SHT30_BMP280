/*Please install the < Adafruit BMP280 Library > （https://github.com/adafruit/Adafruit_BMP280_Library）
 * from the library manager before use. 
 *This code will display the temperature, humidity and air pressure information on the screen*/
#include <M5StickC.h>
#include <Wire.h>
#include "Adafruit_Sensor.h"
#include <Adafruit_BMP280.h>
#include "SHT3X.h"
SHT3X sht30;
Adafruit_BMP280 bme;

float tmp = 0.0;
float hum = 0.0;
float pressure = 0.0;

void setup() {
  M5.begin();
  M5.Axp.ScreenBreath(10);    // 画面の輝度を少し下げる ----B
  M5.Lcd.setRotation(3);      // 左を上にする         ----C
  M5.Lcd.setTextSize(2);      // 文字サイズを2にする
  M5.Lcd.fillScreen(BLACK);   // 背景を黒にする
  Wire.begin();

  while (!bme.begin(0x76)){  
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    M5.Lcd.println("Could not find a valid BMP280 sensor, check wiring!");
  }
}

void loop() {
  pressure = bme.readPressure();
  if(sht30.get()==0){
    tmp = sht30.cTemp;
    hum = sht30.humidity;
  }
  double vbat = M5.Axp.GetVbatData() * 1.1 / 1000;  // バッテリー電圧を取得 ----D
  M5.Lcd.setCursor(0, 0, 1);
  M5.Lcd.printf("temp: %4.1f'C\r\n", tmp);
  M5.Lcd.printf("humid:%4.1f%%\r\n", hum);
  M5.Lcd.printf("press:%4.0fhPa\r\n", pressure / 100);
  M5.Lcd.printf("vbat: %4.2fV\r\n", vbat);

  delay(100);

}
