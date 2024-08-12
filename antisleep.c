#include<ESP8266WiFi.h>
#include<WiFiClientSecure.h>
#include<UniversalTelegramBot.h>
#include<ArduinoJson.h>

const char* ssid = "sleep123";
const char* password ="123456789";

#define BOTtoken "6225258473:AAF9mct_oKdB7eI381O6lLZTPLHkrauOCZM"  // your Bot Token (Get from Botfather)
#define CHAT_ID "1106569834"


X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void setup()
{
    Serial.begin(9600);
    Serial.println("Starting TelegramBot...");
    pinMode(D7,INPUT);
    pinMode(D6,OUTPUT);

    configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
    client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org

    Serial.print("Connecting Wifi: ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  bot.sendMessage(CHAT_ID, "anti sleep detection system...");

}
void loop()
{
  int i=0;
  while(digitalRead(D7)==LOW)
  {
    i++;
    delay(100);
  }
  if(i>10)
  {
    digitalWrite(D6,HIGH);
     bot.sendMessage(CHAT_ID,"person is sleeping...");
     delay(2000);
     digitalWrite(D6,LOW);
     i=0;
  }

}
