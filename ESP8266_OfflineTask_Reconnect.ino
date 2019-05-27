#define NAMEandVERSION "OfflineTask_Reconnect_V1.0"
/*
  This sketch is based on an example posted by Gunner with some modifications added in place to make it able to reconnect after Wifi or Server connection failures.
  It is able to check if it is a Wifi or a server connection issue and recover it when it is possible
  The MCU runs the task every second - It turns the builtin led on and off (allways) and post the millis/1000 to blynk server (only when a connection is available).
*/

//#define BLYNK_DEBUG
#define BLYNK_TIMEOUT_MS  500  // must be BEFORE BlynkSimpleEsp8266.h doesn't work !!!
#define BLYNK_HEARTBEAT   17   // must be BEFORE BlynkSimpleEsp8266.h works OK as 17s
#define BLYNK_PRINT Serial    
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

BlynkTimer timer;

char ssid[]            = "SSID";
char pass[]            = "PASSWORD";
char auth[]            = "AUTHKEY";
//char server[]          = "blynk-cloud.com";
//char server[]          = IPAddress(192,168,1,3);
unsigned int port      = 1234; //use your own port of the server

bool on = 0;
bool online = 0;

// If you dont want to use DHCP 
IPAddress arduino_ip ( 192,  168,   1,  123);
IPAddress dns_ip     ( 192,  168,   1,   1);
IPAddress gateway_ip ( 192,  168,   1,   1);
IPAddress subnet_mask(255, 255, 255,   0);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  
  Serial.begin(115200);
  Serial.println();
  WiFi.hostname(NAMEandVERSION);
  WiFi.mode(WIFI_STA);
  WiFi.config(arduino_ip, gateway_ip, subnet_mask);
  Blynk.config(auth, IPAddress(192,168,1,2), port);  // I am using the local Server
  CheckConnection();// It needs to run first to initiate the connection.Same function works for checking the connection!
  timer.setInterval(5000L, CheckConnection); 
  timer.setInterval(1000L, myTimerEvent);          
}

void loop() {
  if(Blynk.connected()){
    Blynk.run();
  }
  timer.run();
}


void CheckConnection(){    // check every 11s if connected to Blynk server
  if(!Blynk.connected()){
    online = 0;
    yield();
    if (WiFi.status() != WL_CONNECTED)
    {
      Serial.println("Not connected to Wifi! Connect...");
      //Blynk.connectWiFi(ssid, pass); // used with Blynk.connect() in place of Blynk.begin(auth, ssid, pass, server, port);
      WiFi.begin(ssid, pass);
      delay(400); //give it some time to connect
      if (WiFi.status() != WL_CONNECTED)
      {
        Serial.println("Cannot connect to WIFI!");
        online = 0;
      }
      else
      {
        Serial.println("Connected to wifi!");
      }
    }
    
    if ( WiFi.status() == WL_CONNECTED && !Blynk.connected() )
    {
      Serial.println("Not connected to Blynk Server! Connecting..."); 
      Blynk.connect();  // // It has 3 attempts of the defined BLYNK_TIMEOUT_MS to connect to the server, otherwise it goes to the enxt line 
      if(!Blynk.connected()){
        Serial.println("Connection failed!"); 
        online = 0;
      }
      else
      {
        online = 1;
      }
    }
  }
  else{
    Serial.println("Connected to Blynk server!"); 
    online = 1;    
  }
}


void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  if (online == 1)
  {
    Blynk.virtualWrite(V5, millis() / 1000);    
  }
  else 
  {
    Serial.println("Working Offline!");  
  }
  
  if (on == 0)
  {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)    
    on = 1;
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW                  
    on = 0;
  }
  Serial.println(millis() / 1000);
}
