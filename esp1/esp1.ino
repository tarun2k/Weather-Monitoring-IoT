//https://script.google.com/macros/s/AKfycbxUXAdux83G4-2aaSfJnjPu3n_pP5K78dPls5_a_sQCI_IMkMxs/exec 
//https://script.google.com/macros/s/AKfycbzgrv1weuZMoS-1Q8sFM0Zg8vw0SyRWDVSyhkhT6PMhd3WsiWvG/exec 

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid = "Tarun";    //your wifi network
const char* password = "123456789";     //yout wifi pasword
const char* host = "script.google.com";
const int httpsPort = 443;

WiFiClientSecure client;

const char* fingerprint = "46 B2 C3 44 9C 59 09 8B 01 B6 F8 BD 4C FB 00 74 91 2F EF F6";

String GAS_ID = "AKfycbxUXAdux83G4-2aaSfJnjPu3n_pP5K78dPls5_a_sQCI_IMkMxs";     //spreadsheet id


float temp=25.4, humi=52.0, volt1=2.3;
int gas1=100;
char cmd_arr1[20];
int cmd_count1;

void setup() 
{
  
  Serial.begin(9600); 
  Serial.println();

  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  client.setInsecure();
}

void serial_get_command()
{
  char inchar=0;
  if(Serial.available() > 0)
  {
    inchar = Serial.read();    
    if(inchar == '<')
    {
      cmd_count1=0;
      while(inchar != '>' && cmd_count1<20)
      {
        if(Serial.available() > 0)
        {
          inchar = Serial.read();
          cmd_arr1[cmd_count1++] = inchar;
          cmd_arr1[cmd_count1] = '\0';
        }        
      }
      if(inchar == '>')
      {
        cmd_count1--;
        cmd_arr1[cmd_count1] = '\0';
        if(cmd_arr1[0]=='A'){cmd_arr1[0]='0';temp = atof(cmd_arr1);} 
        else if(cmd_arr1[0]=='B'){cmd_arr1[0]='0';humi = atof(cmd_arr1);}
        else if(cmd_arr1[0]=='C'){cmd_arr1[0]='0';gas1 = atof(cmd_arr1);} 
        else if(cmd_arr1[0]=='D'){cmd_arr1[0]='0';volt1 = atof(cmd_arr1);}
        else if(cmd_arr1[0]=='E'){cmd_arr1[0]='0';sendData(temp, humi, gas1, volt1);}
      }
    }
  }
}


void loop() 
{
  serial_get_command();
  
}

void sendData(int tem, int hum , int gas, int volt)
{
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  if (client.verify(fingerprint, host)) {
  Serial.println("certificate matches");
  } else {
  Serial.println("certificate doesn't match");
  }
  String string_temperature =  String(tem, DEC); 
  String string_humidity =  String(hum, DEC); 
  String string_Gas =  String(gas, DEC); 
  String string_Volt =  String(volt, DEC); 
  String url = "/macros/s/" + GAS_ID + "/exec?temperature=" + string_temperature + "&humidity=" + string_humidity + "&gas=" + string_Gas + "&volt=" + string_Volt;
  //Serial.print
  Serial.print("requesting URL: ");
  Serial.println(url);

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
  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("closing connection");
} 
