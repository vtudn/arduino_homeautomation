#include "LD_Project.h"
#include "timer.h"
#include "button_reading.h"
#include "button_processing.h"
#include "dht_sensor.h"
#include "gas_sensor.h"
#include "pir_sensor.h"
#include "soil_sensor.h"

//------------------dht_sensor.c----------------------
#include "DHT.h"
#include "Wire.h" 
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C lcd(0x27,16,2);
DHT dht(DHTPIN, DHTTYPE);
int sensorvalue;
int incomingByte=0;
char degree = 223;

void DHT11_LCD_init(void){
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.print("Temp: ");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.setCursor(11,0);
  lcd.print("0");
  lcd.print(" ");
  lcd.print(degree);
  lcd.print("C");
  lcd.setCursor(11,1);
  lcd.print("0");
  lcd.print(" %");
}

void DHT11_LCD(void){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(t) || isnan(h)){
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("Error!");
  } 
  else {
    lcd.setCursor(11,0);
    lcd.print(round(t));
    lcd.print(" ");
    lcd.print(degree);
    lcd.print("C");
    lcd.setCursor(11,1);
    lcd.print(round(h));
    lcd.print(" %");  
    Serial.print("!TEMP:");
    Serial.print(t);
    Serial.print("#");
    Serial.println("");
    Serial.print("!HUMI:");
    Serial.print(h);
    Serial.print("#");
    Serial.println("");  
  }
}
//--------------------------------------------------

void setup(){
  Serial.begin(9600);
  button_init();
  DHT11_LCD_init();
  gas_init();
  pir_init();
  soil_init();
  timer_init();
  timer_set(0, 10);
  timer_set(1, 10);
}

void loop(){
  // BUTTON
  fsm_for_input_processing();
  // BUTTON (1s)
  if (timer_flag[0] == 1){
    if (flag_1s == 1){
      button_more_than_1s();
      timer_set(0, 1000);
    }
    else timer_set(0, 10);
  }
  // DHT SENSOR
  if (timer_flag[1] == 1){
    DHT11_LCD();
    update_soil();
   // update_soil();
    timer_set(1, 10000);
  }
  // GAS SENSOR
  gas_run(); 
  // PIR SENSOR
  pir_run();
  // SOIL SENSOR
  soil_run(sensorvalue);
}

ISR(TIMER1_COMPA_vect){
  timer_run();
  button_reading();
}
void update_soil(void){
  sensorvalue=analogRead(SOIL);
  sensorvalue=map(sensorvalue,0,1023,0,100);
  Serial.print("!SOIL:");
  Serial.print(sensorvalue);
  Serial.println("#");
}

void SPrint(const char *msg) {
  Serial.println(msg);
}
void SPrints(const char *msg) {
  Serial.print(msg);
}
