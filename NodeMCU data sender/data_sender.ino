#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
 
const char* ssid = "SoAp";
const char* password = "naruto4123";

const int AnalogIn = A0; 
const int DigitalIn = D2; 
const int pumpout = D0; 
 
void setup () {

  pinMode(AnalogIn,INPUT);
  pinMode(DigitalIn,INPUT);
  pinMode(pumpout,OUTPUT);
  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.print("Connecting..");
 
  }
 
}

int getWellLevel(){
  int level;
  level = digitalRead(DigitalIn);
  
  return level;
}

int getTankLevel(){
  int level;
  int data = analogRead(AnalogIn);
  level = ((data-20)*100/(990-20));
  if(level > 100){
    level=100;
  }
  if(level < 0){
    level=0;
  }
  return level;
}

void control(int tankLevel,int wellLevel){
  
  if(tankLevel > 90 || wellLevel==0){ // check whether tankLevel is greater than 90 or wellLevel is low
    
    digitalWrite(pumpout,LOW);
    
    
  }else if(tankLevel < 50 && wellLevel==1){ // check whether tankLevel is lower than 50 or wellLevel is high
    
    digitalWrite(pumpout,HIGH);
    
  }
}
 
void loop() {
 
    if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
     HTTPClient http;  //Declare an object of class HTTPClient
    
    int wellLevel=getWellLevel(); // read and calculating well level
    int tankLevel=getTankLevel(); //  read and calculating tank level

    Serial.println(String(wellLevel)+" "+String(tankLevel));
   
    

    control(tankLevel,wellLevel);
    
    http.begin("http://192.168.8.105:5000/?q="+String(wellLevel)+"&p="+String(tankLevel));  //Specify request destination
    Serial.print("sending request.....");
    int httpCode = http.GET();                                                                  //Send the request
 
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload
 
    }
 
    http.end();   //Close connection
 
  }
 
  delay(1);    //Send a request every 3 seconds
 
}



