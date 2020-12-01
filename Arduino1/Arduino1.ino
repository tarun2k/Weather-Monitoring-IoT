
int gas = A0;
int sensorValue; 

int analog_value;
float input_voltage = 0.0;

#include "DHT.h"
#define DHTPIN A2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float h,t;

void Gas_read()
{
  //Average   
  for(int x = 0 ; x < 100 ; x++) 
  { 
    sensorValue = sensorValue + analogRead(gas); 
  } 
  sensorValue = sensorValue/100.0; 
  Serial.print("<C");Serial.print(sensorValue);Serial.print(">");
}

void read_solar()
{
   analog_value = analogRead(A1);
   input_voltage = (analog_value * 5.0) / 1024.0; 

   
   if (input_voltage < 0.1) 
   {
     input_voltage=0.0;
   } 
   Serial.print("<D");Serial.print(input_voltage);Serial.print(">");
}


void temp_read()
{
  h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  t = dht.readTemperature();
  Serial.print("<A");Serial.print(t);Serial.print(">");
  Serial.print("<B");Serial.print(h);Serial.print(">");
}
 
void setup() 
{ 
  Serial.begin(9600);
  dht.begin(); 
} 
  
void loop() 
{ 
 temp_read(); 
 Gas_read(); 
 read_solar();
 Serial.println("<E>");
 delay(2000);
}
