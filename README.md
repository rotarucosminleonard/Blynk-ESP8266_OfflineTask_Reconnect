# Blynk-ESP8266_OfflineTask_Reconnect
ESP8266 running a task online or offline. Check the connection periodically and reconnect when it is possible

This sketch is based on an example posted by Gunner with some modifications added in place to make it able to reconnect after Wifi or Server connection failures. 
It is able to check if it is a Wifi or a server connection issue and recover it when it is possible. The MCU runs the task every second whether it is online or not 
It turns the builtin led on and off (allways) and attempts to post the millis/1000 to blynk server if there is a connection to the server..
