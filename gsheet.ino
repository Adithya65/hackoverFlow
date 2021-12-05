 #include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>




#define ON_Board_LED 2 
 
int Delay=0; //delay count (20==30sec)
int k=0;
int bn=0;
int current=0;
int current_iot=0;
 
const char* ssid = "jio upstair"; 
const char* password = "Adithya1"; 
int x=0;
const char* host = "script.google.com";
const int httpsPort = 443;


WiFiClientSecure client; 

String GAS_ID = "AKfycbx9QnO3qUJditCvlrsozgO9CzuTwCZXWj726h0INjQI--xfbQbN"; 


void setup() {
  pinMode(12,OUTPUT);//D6
pinMode(14,INPUT);//D5
pinMode(16,OUTPUT);
  Serial.begin(115200);
  delay(500);

 
  delay(500);
  
  WiFi.begin(ssid, password); 
  Serial.println("");
    
  pinMode(ON_Board_LED,OUTPUT); 
  digitalWrite(ON_Board_LED, HIGH); 
  
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
  
  sendData( ); 
}

void sendData( ) {

  current=current+10;
  Serial.println("==========");
  Serial.print("connecting to ");
  Serial.println(host);
  
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  if (bn==5){
    current_iot=current+10;
    bn=0;
    
  }
  else
  current_iot=current;
  
  
  String url = "/macros/s/" + GAS_ID + "/exec?temperature=" + String(current_iot) + "&humidity=" + String(current);
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
