#include <ArduinoJson.h>
#include <LWiFi.h>
#define LEDR 13
#define LEDG 12
#define LEDB 11

const char* ssid     = "AndroidAP0144";           // insert your SSID
const char* pass     = "pdfh6278";   // insert your password

WiFiClient client;

const char* server = "maker.ifttt.com"; 
const char* resource ="/trigger/PM25/with/key/gW6dy3yD9pSgHAGehG_luppmEZhzstmxr566_5uqnlZ?value1=";
const char* server2 = "opendata.epa.gov.tw";  
const char* resource2 = "/ws/Data/ATM00625/?$format=json"; 
char json[12000]; 

void setup(){
  Serial.begin(115200);
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println();
}

void loop(){
  // connect to server  
  while(!client.connect(server2, 80)){
    // wait for connecting server...
  }

  //Send request to resource
  client.print("GET ");
  client.print(resource2);
  client.println(" HTTP/1.1");
  client.print("Host: ");
  client.println(server2);
  client.println("Connection: close");
  client.println();

  delay(100);

  //Reading stream
  
  
  //client.setTimeout(10000);

  //Checking for the end of HTTP stream
  while(!client.find("\r\n\r\n")){
    // wait for finishing header stream reading ...
  }

  // Reading the response string
  client.readBytes(json, 12000);
  
  // process JSON from response string
  DynamicJsonBuffer jsonBuffer;
  JsonArray& rootArray = jsonBuffer.parseArray(json);
  JsonObject& linYuanSite = rootArray[40];

  const char* site1 = linYuanSite["Site"];
  double pm251 = linYuanSite["PM25"];
  
  // Print data to Serial

  Serial.print("*** ");
  Serial.print(site1);
  Serial.println(" ***");
  Serial.print("PM25: ");
  Serial.println(pm251);

  if(pm251< 35 )
  {
     digitalWrite(LEDR, LOW);
     digitalWrite(LEDB, LOW);
     digitalWrite(LEDG, HIGH);
     delay(1000);
  }
  else if(pm251> 35 && pm251 <53)
  {
     digitalWrite(LEDR, LOW);
     digitalWrite(LEDG, HIGH);
     digitalWrite(LEDB, HIGH);
     delay(1000);
  }
   else if(pm251> 53 && pm251 <70)
  {
     digitalWrite(LEDG, LOW);
     digitalWrite(LEDB, LOW);
     digitalWrite(LEDR, HIGH);

      while(!client.connect(server, 80)){
    // wait for connecting server...
     }

      //Send request to resource
      client.print("GET ");
      client.print(resource);
      client.println(" HTTP/1.1");
      client.print("Host: ");
      client.println(server);
      client.println("Connection: close");
      client.println();

      delay(3000);
  
  }
  else if(pm251> 70)
  {
    digitalWrite(LEDG, LOW);
    digitalWrite(LEDB, HIGH);
    digitalWrite(LEDR, HIGH); 
    
    while(!client.connect(server, 80)){
    // wait for connecting server...
     }

      //Send request to resource
      client.print("GET ");
      client.print(resource);
      client.println(" HTTP/1.1");
      client.print("Host: ");
      client.println(server);
      client.println("Connection: close");
      client.println();

      delay(3000);
  }
  client.stop(); // disconnect from server
  delay(2000); // the OWM free plan API does NOT allow more then 60 calls per minute
}


