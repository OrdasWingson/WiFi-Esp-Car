void HTTP_init(void) {
  HTTP.on("/forword", go_forword);     //едем вперед
  HTTP.on("/left", go_left);     //лево
  HTTP.on("/right", go_right);     //право
  HTTP.on("/reset", stopWheels); //остановка
  HTTP.on("/back", go_back); //назад
  HTTP.on("/config", conf); //обработка конфигурации
  HTTP.on("/mode", changeMode); //смена режима работы сервера
 
  // Запускаем HTTP сервер
  HTTP.begin();

}

void engins(int enA=0, int enB=0, int in1=0, int in2=0,int in3=0, int in4=0){
      analogWrite (ENA, enA);
      analogWrite (ENB, enB);
      digitalWrite(IN1, in1);   
      digitalWrite(IN2, in2);
      digitalWrite(IN3, in3);   
      digitalWrite(IN4, in4);
}

//Код движения вперед
void go_forword(){
  engins(255,255,1,0,1,0);
  HTTP.send(200, "text/plain", "OK ");
}

//Код движения налево
void go_left(){
  engins(150,150,0,1,1,0);
  HTTP.send(200, "text/plain", "OK ");
}

//Код движения направо
void go_right(){
  engins(150,150,1,0,0,1);
  HTTP.send(200, "text/plain", "OK ");
}

//Остановка
void stopWheels(){
  engins(0,0,0,0,0,0);
  HTTP.send(200, "text/plain", "OK ");
}

//Код движения назад
void go_back(){
  engins(150,150,0,1,0,1);
  HTTP.send(200, "text/plain", "OK ");
}


//конфигурация
void conf()
{
  //root
  HTTP.send(200, "application/json", jsonConfig);
}

//режим подключения
void changeMode()
{
  stateOf = HTTP.arg("mode");
  Serial.println("mode - " + stateOf); 
  
  if(stateOf == "STA"){
    ssid = HTTP.arg("ssid");
    //Serial.println("ssid - " + ssid);
    password = HTTP.arg("pass");
    //Serial.println("password - " + password);
    WiFi.disconnect();
    Serial.println("DISCONECT");
    WIFIinit();
  }
  if(stateOf == "AP"){
    Serial.println("AP START");
     StartAPMode();
  }
   HTTP.send(200, "text/plain", "OK"); // AP/STA
  saveConfig();
 
}

