char ssid[]            = "ssid";
char pass[]            = "pass";
char auth[]            = "auth";
//char serveraddr[]          = "blynk-cloud.com";

IPAddress serveraddr  (192,   168,   0,   55);
unsigned int port      = 1234; //use your own port of the server default:9443

// If you dont want to use DHCP 
IPAddress arduino_ip ( 192,  168,   0,  120);
IPAddress dns_ip     ( 192,  168,   0,   1);
IPAddress gateway_ip ( 192,  168,   0,   1);
IPAddress subnet_mask(255, 255, 255,     0);
