//----------------------------------------Include the NodeMCU ESP8266 Library
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Servo.h>
#include <MQ135.h>

//----------------------------------------

#include "DHT.h"  //--> Include the DHT Sensor Library 
#define DHTTYPE DHT11 //--> Defines the type of DHT sensor used (DHT11, DHT21, and DHT22), in this project the sensor used is DHT11.

#include "index.h" //--> Include the contents of the User Interface Web page, stored in the same folder as the .ino file

#define LEDonBoard 2  //--> Defining an On Board LED, used for indicators when the process of connecting to a wifi router
#define ServoPort1 D3   //--> connect to pin D3  Aim
#define ServoPort2 D2   //--> connect to pin D3  Pan
const int MQ135Pin = A0; // MQ135 sensor pin is connected to Analog pin A0
MQ135 mq135(MQ135Pin);
#define LED D5          //--> Connect to D5= laser

//----------------------------------------SSID and Password of your WiFi router
const char* ssid = "realme 9";
const char* password = "rcc12345";
//----------------------------------------

ESP8266WebServer server(80);  //--> Server on port 80

const int DHTPin = 5; //--> The pin used for the DHT11 sensor is Pin D1=Pin 5
DHT dht(DHTPin, DHTTYPE); //--> Initialize DHT sensor, DHT dht(Pin_used, Type_of_DHT_Sensor);
const int PIRPin = 2; //--> The pin used for the PIR sensor is Pin D4 = Pin 2
Servo myservo1;  //--> create servo object to control a servo
Servo myservo2;  //--> create servo object to control a servo

//----------------------------------------This routine is executed when you open NodeMCU ESP8266 IP Address in browser
void handleRoot() {
 String s = MAIN_page; //--> Read HTML contents
 server.send(200, "text/html", s); //--> Send web page
}
//----------------------------------------
//----------------------------------------Procedure for reading the temperature value of a DHT11 sensor
void handleDHT11Temperature() {
  float t = dht.readTemperature();  //--> Read temperature as Celsius (the default). If you want to read the temperature sensor in Fahrenheit, use this -> float t = dht.readTemperature (true);
  String Temperature_Value = String(t);
 
  server.send(200, "text/plane", Temperature_Value); //--> Send Temperature value only to client ajax request
  
  if (isnan(t)) { //--> Check if any reads failed and exit early (to try again).  
    Serial.println("Failed to read from DHT sensor!");
  }
  else {
    Serial.print("DHT11 || Temperature : ");
    Serial.print(t);
    Serial.print(" || ");
  }
}
//----------------------------------------
//----------------------------------------Procedure for reading humidity values from DHT11 sensors
void handleDHT11Humidity() {
  float h = dht.readHumidity();
  String Humidity_Value = String(h);
 
  server.send(200, "text/plane", Humidity_Value); //--> Send Humidity value only to client ajax request
  if (isnan(h)) {
    Serial.println("Failed to read from DHT sensor !");
  }
  else {
    Serial.print("Humidity : ");
    Serial.println(h);
  }
}

// procedure for reading servomotor 
void handleServo(){
  String POS1 = server.arg("servoPOS1");
  int pos1 = POS1.toInt();
  myservo1.write(pos1);   //--> Move the first servo motor according to the POS value
  delay(15);
  Serial.print("Servo 1 Angle:");
  Serial.println(pos1);
  
  String POS2 = server.arg("servoPOS2");
  int pos2 = POS2.toInt();
  myservo2.write(pos2);   //--> Move the second servo motor according to the POS value
  delay(15);
  Serial.print("Servo 2 Angle:");
  Serial.println(pos2);
  
  server.send(200, "text/plane","");
}

// smoke sensor
void handleMQ135Gas() {
  float rzero = mq135.getRZero();
  float ppm = mq135.getPPM();
  String Gas_Value = String(ppm);
  server.send(200, "text/plane", Gas_Value); // Send gas concentration value only to client ajax request
  Serial.print("MQ135 || Gas Concentration: ");
  Serial.print(ppm);
  Serial.print(" ppm || RZero: ");
  Serial.print(rzero);
  Serial.print(" ohms || ");
}

//----------------------------------------Procedure for reading the PIR sensor value
void handlePIRSensor() {
  int pirValue = digitalRead(PIRPin); //--> Read the PIR sensor value
  String pirStatus = "";
  if (pirValue == HIGH) { //--> Check the PIR sensor value and send the status to the client
    pirStatus = "Yes";
  } else {
    pirStatus = "No";
  }
  server.send(200, "text/plane", pirStatus); //--> Send the PIR sensor status to the client
  
  Serial.print("PIR Sensor : ");
  Serial.println(pirStatus);
}

// ------------------------Laser code

void led_control() {
 String state = "OFF";
 String act_state = server.arg("state");
 if(act_state == "1") {
  digitalWrite(LED,HIGH); //LED ON
  state = "ON";
 }
 else {
  digitalWrite(LED,LOW); //LED OFF
  state = "OFF";
 }
 server.send(200, "text/plane", state);
}



//----------------------------------------
//----------------------------------------Setup
void setup(void){
  Serial.begin(115200);
  delay(500);
  dht.begin();  //--> Start reading DHT11 sensors
  myservo1.attach(ServoPort1); //--> attaches the servo on D1 to the servo object
  myservo2.attach(ServoPort2); //--> attaches the servo on D1 to the servo object
  pinMode(PIRPin, INPUT); //--> Set the PIR sensor pin as input
  pinMode(LED,OUTPUT);    //--> led status
  // mq135.begin();
  delay(500);
  
  WiFi.begin(ssid, password); //--> Connect to your WiFi router
  Serial.println("");
    
  pinMode(LEDonBoard,OUTPUT); //--> On Board LED port Direction output
  digitalWrite(LEDonBoard, HIGH); //--> Turn off Led On Board

  
  //----------------------------------------Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.
    digitalWrite(LEDonBoard, LOW);
    delay(250);
    digitalWrite(LEDonBoard, HIGH);
    delay(250);
    //----------------------------------------
  }
  //----------------------------------------
  digitalWrite(LEDonBoard, HIGH); //--> Turn off the On Board LED when it is connected to the wifi router.
  //----------------------------------------If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  //----------------------------------------
  server.on("/", handleRoot); //--> Routine to handle at root location. This is to display web page.
  server.on("/readTemperature", handleDHT11Temperature);  //--> Routine to handle the call procedure handleDHT11Temperature
  server.on("/readHumidity", handleDHT11Humidity);  //--> Routine to handle the call procedure handleDHT11Humidity
  server.on("/setPOS",handleServo); //--> Sets servo position from Web request
  server.on("/readGas", handleMQ135Gas); //--> Sets gas from Web request
  server.on("/readPIR", handlePIRSensor);  //--> Routine to handle the call procedure handlePIRSensor
  server.on("/led_set", led_control);  //--> Routine to handle the call of Laser

  server.begin(); //--> Start server
  Serial.println("HTTP server started");
}
//----------------------------------------
//----------------------------------------Loop
void loop(){
  server.handleClient();  //Handle client requests
}
//----------------------------------------
