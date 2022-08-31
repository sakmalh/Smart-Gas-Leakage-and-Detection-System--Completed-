const int led = 6;
const int buzzer = 3;
int fanrelay    = 4;
int bulbrelay   = 2;
int irsensor = 7;
int flag = 0;
int sensorValue;
#include <dht.h>
#define dataPin 5// Defines pin number to which the sensor is connected
dht DHT;




void setup()
{
  //setting up the correct pin modes
  pinMode(led,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(fanrelay, OUTPUT);
  pinMode(bulbrelay, OUTPUT);
  pinMode(irsensor,INPUT);
  //initializing the serial monitor
  Serial.begin(9600);
}

void loop()
{
  int readData = DHT.read11(dataPin); // DHT11
  float temp = DHT.temperature; // Gets the values of the temperature
  float humid = DHT.humidity;
  sensorValue = analogRead(0); 
  //read the input from mq2 gas sensor
  flag = digitalRead(irsensor);

  Serial.print("Air Quality = ");
  Serial.println(sensorValue);
  Serial.print("Temperature = ");
  Serial.println(temp);
  Serial.print("Humidity = ");
  Serial.println(humid);

  
  
  //int led_out = min(sensorValue,255);
  
  //send the output to buzzer
 
  //send the pwm signal to led
  
  //delay of 100ms
  int led_out = map(sensorValue, 80, 400, 0, 255); 
  
  if (sensorValue>200){
    digitalWrite(fanrelay, HIGH);
    digitalWrite(bulbrelay, LOW);
    
    noTone(buzzer);
    tone(buzzer,700,500);
    delay(100);
    noTone(buzzer);
    tone(buzzer,900,300);
    delay(50);
    noTone(buzzer);
    
    analogWrite(led,led_out);
  } else {
    digitalWrite(fanrelay, LOW);
    digitalWrite(bulbrelay, HIGH);
    digitalWrite(led,LOW);
  }
  
  if( flag == 0 ){
    Serial.println("FIRE DETECTED");
  }

  delay(2000);
}
