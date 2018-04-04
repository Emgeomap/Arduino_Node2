#include <SPI.h>
#include <RFID.h>
#include <Ethernet.h>
#include <dht11.h>
RFID lrt720(7, 6);
#define DHT11PIN 5
#define BUZZER 4
#define LED 3
#define door 2
dht11 DHT11;
String _data = "|";
byte mac[] = {0x90, 0xA2, 0xDA, 0x0F, 0x2A, 0x8D};
byte ip[] = {192, 168, 0, 177};
byte gw[] = {192, 168, 0, 1};
byte subnet[] = {255, 255, 255, 0};
EthernetClient client;
String dataId = "";
String recivedData = "";
String queryTemp;
String queryKartId;
unsigned long tempZaman;
unsigned long doorZaman;
unsigned long kartZaman;
unsigned long kecenZaman;
String _humidity = "";
String _temperature = "";
void setup()
{
  Ethernet.begin(mac, ip);
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(door, INPUT);
  SPI.begin();
  lrt720.init();
  delay(500);
}
void loop()
{
  kecenZaman = millis();
  if (kecenZaman - tempZaman > 5000)
  {
    tempZaman = kecenZaman;
    int chk = DHT11.read(DHT11PIN);
    _humidity = DHT11.humidity;
    _temperature = DHT11.temperature;
    queryTemp = "tempurature/?humudity=" + _humidity + "&heat=" + _temperature;
    senddata(queryTemp);
    queryTemp = "";
  }
  if (digitalRead(door) == LOW)
  {
    if (kecenZaman - doorZaman > 1000)
    {
      doorZaman = kecenZaman;
      senddata("doorPosition/?status=true");
    }
  }
  else
  {
    if (kecenZaman - doorZaman > 4000)
    {
      doorZaman = kecenZaman;
      senddata("doorPosition/?status=false");
    }
  }
  if (client.available())
  {
    char c = client.read();
    recivedData += c;
    if (c == '\n')
    {
      Serial.println(recivedData);
      client.stop();
      if (recivedData.indexOf("200") > 0)
      {
        Serial.println("OK");
      }
      else
      {
        Serial.println("NO");
      }
      client.stop();
      recivedData = "";
    }
  }

  if (lrt720.isCard())
  {
    if (lrt720.readCardSerial())
    {
      if (kecenZaman - kartZaman > 3000)
      {
        kartZaman = kecenZaman;
        Serial.print("KartID : ");
        for (int i = 0; i < 5; i++)
        {
          dataId += lrt720.serNum[i];
        }
        Serial.println(dataId);
        //      digitalWrite(BUZZER, HIGH);
        digitalWrite(LED, HIGH);
        delay(50);
        //      digitalWrite(BUZZER, LOW);
        digitalWrite(LED, LOW);
        delay(50);
        //      digitalWrite(BUZZER, HIGH);
        digitalWrite(LED, HIGH);
        delay(50);
        //      digitalWrite(BUZZER, LOW);
        digitalWrite(LED, LOW);
        queryKartId = "kartId=" + dataId;
        senddata(queryKartId);
        queryKartId = "";
        dataId = "";
      }
    }
  }
  lrt720.halt();
}
void senddata(String data)
{
  if (client.connect("192.168.0.105", 3000))
  {
    Serial.println(data);
    client.print("GET /");
    client.print(String(data));
    client.println(" HTTP 1.1");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println();
    client.print(data);
  }
}
/*
    client.print("GET /sensor/?A0=");
    client.print(String(analogRead(A0)));
    client.print("&A1=");
    client.print(String(analogRead(A1)));
    client.println(" HTTP 1.1");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println();
    client.print(data);
*/
