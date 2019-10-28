#include <ESP8266WiFi.h>        
#include <ESP8266WebServer.h>     
#include <FS.h>
#include <ArduinoJson.h> 

String ssid = "admin"; //Сеть по умолчанию
String password = "1234"; //Пароль по умолчанию
String jsonConfig = "{}";//Переменная для обработки файла конфигурации
String stateOf ="AP"; //какой режим включен

// Web интерфейс для устройства
ESP8266WebServer HTTP(80);
// Для файловой системы
File fsUploadFile;

int IN4 = 2; // Input3 подключен к выводу 4 d4
int IN3 = 0; //d3
int IN2 = 4; // Input1 подключен к выводу 6 d2
int IN1 = 5; //d1
//подключение к регулированию с помощью ШИМ
int ENA = 14; 
int ENB = 12; 

void setup() {
  Serial.begin(9600);
   FS_init();
   loadConfig();
   if(stateOf == "STA")
      WIFIinit();
   else
      StartAPMode();
  HTTP_init();

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
}

void loop() {
  HTTP.handleClient();
  delay(1);
}

