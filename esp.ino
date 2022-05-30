   #include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#define PIN A0
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "DHT.h"
#define DHTPIN D5
DHT dht(DHTPIN, DHT11);
#define rainAnalog A0
 

Adafruit_PCD8544 display = Adafruit_PCD8544(D4,D3,D2,D1,D0);
float resolution  = 3.3 / 1024;



#define ON_Board_LED 2 
 
int Delay=0; //delay count (20==30sec)
int k=0;
int bn=0;
int current=0;
int current_iot=0;
 
const char* ssid = "adi"; 
const char* password = "qwerty12345"; 
int x=0;
const char* host = "script.google.com";
const int httpsPort = 443;


WiFiClientSecure client; 

String GAS_ID = "AKfycbwUsBtULqAFRyixtySTfD6dS6MV_oXtEkR--GiUsnA4T6XDEB3HHBFMa8_ooetM17hF"; 


void setup() {
  
  pinMode(D6,OUTPUT);
  pinMode(PIN, INPUT);
  //DISPLAY
   
   display.begin();
 
  //DHT
  Serial.println(F("DHTxx test!"));
  dht.begin();
    
 
  Serial.begin(115200);
  delay(500);

 
  delay(500);
  
  WiFi.begin(ssid, password); 
  Serial.println("");
    
  pinMode(ON_Board_LED,OUTPUT); 
  digitalWrite(ON_Board_LED, HIGH); 
  digitalWrite(D6,HIGH);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
 
  }
  digitalWrite(ON_Board_LED, HIGH); 
  
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();


  client.setInsecure();
}

void loop() {
     
int curr=analogRead(PIN);                // Function to read from pin A0
  Serial.print("Voltage (when zero current) = ");
 
  delay(1000);
  //Humidity

  float humidity = dht.readHumidity();
  float temp = dht.readTemperature();
 
  //rain
    int rain = analogRead(rainAnalog);


 display.clearDisplay(); //clears display each time the loop starts over

display.setCursor(0,0);

display.print("The current is: "); //this will be written on the LCD

display.println(curr);

display.display();

delay(1000);


   sendData(temp,humidity,26,curr,rain );
}

int sendData(int temp,int humidity,int light,int curr,int rain ) {


  display.clearDisplay(); //clears display each time the loop starts over

display.setCursor(0,0);

display.print("The current is: "); //this will be written on the LCD

display.println(curr);

display.display();

delay(1000);
  current=current+10;
  Serial.println("==========");
  Serial.print("connecting to ");
  Serial.println(host);
  
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return 0;
  }

  if (bn==5){
    current_iot=current+10;
    bn=0;
    
  }
  else
  current_iot=current;
  
  
  String url = "/macros/s/" + GAS_ID + "/exec?temperature=" + String(temp) + "&humidity="+String(humidity)+"&light="+String(light)+"&current="+String(curr)+"&preci="+String(rain)+"&units="+String(220*curr/100)+"&current_iot="+String(220*curr/100);
  Serial.print("requesting URL: ");
  Serial.println(url);
  if (k==Delay){
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "User-Agent: BuildFailureDetectorESP8266\r\n" +
         "Connection: close\r\n\r\n");

  Serial.println("request sent");
  
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successfull!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.print("reply was : ");
  Serial.println(line);
  Serial.println("closing connection");
  Serial.println("==========");
  Serial.println();
  k=0;
} 
else if(k<Delay) {
k=k+1;}
bn=bn+1;}
