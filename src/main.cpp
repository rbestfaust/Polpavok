#include <Arduino.h>
//connectig library for Oled
#include <GyverOLED.h>
//String for connection
GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;



/*
Схема подключения поплавка без блока питания.
В А3 подключили белый провод + одна нога сопротевления
Вторая нога сопротивления в порт 5В ардуино
Синий провод поплавка в землю на ардуино
adress of OLED - 0x3C
*/


 // Need to SetUP Poplavok
#define readingPinKrutilki A3
#define pin5VforOLED 2 //pin for VCC 5V
float Voltag = 0;
int Razryad = 0;
float Percent_of_Fuel = 0;
float TempPercent = 0;
const float MaxVoltag = 5.0; // Максимальное значение вольтажа
int infoPercentToOLED = 0;

void setup() {

{// Need to SetUP Poplavok
  Serial.begin(9600); //Starting COM port
  pinMode(readingPinKrutilki, INPUT); //initilize reading rezistor
  pinMode(13,OUTPUT); //for test
}

{// NeedToOled Initilizing and start
  pinMode(pin5VforOLED, OUTPUT); //NeedToOled +5v
  digitalWrite(pin5VforOLED,HIGH); //NeedToOled +5v
  oled.init();        // инициализация
  oled.clear();       // очистка
  oled.setScale(3);   // масштаб текста (1..4)
  oled.home();        // курсор в 0,0
  oled.print("(^///^)"); //Screensaver

  delay(2000);
  oled.clear();

;

}



 
}

void loop() {

  //for test Github

  {// PoplavokNa4alo Razryad and Voltag
  Razryad = analogRead(readingPinKrutilki); // reading in 10bit
  Voltag = ((float)Razryad / 1024) * MaxVoltag; // convert to voltage 0 to 5
  }

{// FormulaAndPrint
  // Расчет процентного значения
if (Voltag <= 0.01) {
    Percent_of_Fuel = 100; // Если Voltag <= 0.01, то 100%
} else if (Voltag >= 0.13) {
    Percent_of_Fuel = 0; // Если Voltag >= 0.13, то 0%
} else {
    Percent_of_Fuel = 100 - ((Voltag - 0.01) / (0.13 - 0.01)) * 100; // Инверсия пропорции
}

  Serial.println("Razryad = " + String(Razryad) + " Voltag = " + String(Voltag) + " Percent = " + String(Percent_of_Fuel) + String(infoPercentToOLED));
/*Some test code*/
  if(Percent_of_Fuel == 100){digitalWrite(13, HIGH);}else{digitalWrite(13, LOW);}

 }
 
  infoPercentToOLED = int(Percent_of_Fuel); //Float to Int
  Serial.println(infoPercentToOLED); //debug
  oled.setScale(3);   // масштаб текста (1..4)
  oled.home();        // курсор в 0,0
  oled.print(infoPercentToOLED);
 
 delay(350);

 if(infoPercentToOLED >= 100 || infoPercentToOLED <= 10)oled.clear(); //clear when layer need to clean

}

/*

*/