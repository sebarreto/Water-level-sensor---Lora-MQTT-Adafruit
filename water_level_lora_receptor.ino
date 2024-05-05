//Library for Wi-Fi connection
#include <WiFi.h>
//Libraries for MQTT sending data to Adafruit
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
//Libraries for LoRa
#include <SPI.h>
#include <LoRa.h>
//Libraries for OLED Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//User and password to connect Wi-Fi local network & Adafruit IO configuration 
#include "home_wifi_mqtt.h"
//define the pins used by the LoRa transceiver module
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26
//433E6 for Asia
//866E6 for Europe
//915E6 for North America
#define BAND 866E6
//OLED pins
#define OLED_SDA 4
#define OLED_SCL 15 
#define OLED_RST 16
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
//Object to handle the screen
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);
//String to receive data from the sender
String LoRaData;
//Object to handle wifi & mqtt connection
WiFiClient client;
// MQTT cliente configuration, we use Wi-Fi object & MQTT data coming from home_wifi_mqtt.h file.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish water_level = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/water_level");
//------------------- MAIN PROGRAM ---------------------
void setup() {
  //reset OLED display via software
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);
  //initialize OLED
  Wire.begin(OLED_SDA, OLED_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("LORA RECEIVER ");
  display.display();  
  //initialize Serial Monitor
  Serial.begin(9600);

  Serial.println("LoRa Receiver L.Water");
  //SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);
  //setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initializing OK!");
  display.setCursor(0,10);
  display.println("LoRa Inicialization OK!");
  display.display(); 
  // WIFI connection.
  Serial.println(); Serial.println();
  delay(10);
  Serial.print(F("Connecting Wi-Fi ... "));
  Serial.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();
  Serial.println(F("Wi-Fi connected"));
  Serial.println(F("IP address: "));
  Serial.println(WiFi.localIP());
 
  // Adafruit IO connection
  connect_adafruit(); 
}

// Adafruit IO connection via MQTT
void connect_adafruit()
{
  Serial.print(F("Connecting Adafruit IO... "));
  int8_t ret;
  while ((ret = mqtt.connect()) != 0)
  {
    switch (ret)
    {
      case 1: Serial.println(F("Protocol error")); break;
      case 2: Serial.println(F("ID rejected")); break;
      case 3: Serial.println(F("Server unavailable")); break;
      case 4: Serial.println(F("Error user/password")); break;
      case 5: Serial.println(F("Not authorized")); break;
      case 6: Serial.println(F("Sub-description failed")); break;
      default: Serial.println(F("Connection failed")); break;
    }
 
    if(ret >= 0)
      mqtt.disconnect();
 
    Serial.println(F("Retrying connection..."));
    delay(10000);
  }
  Serial.println(F("Adafruit IO connected!"));
}

void loop() {
  //try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    //received a packet
    Serial.print("Received packet. L.Water: ");

    //read packet
    while (LoRa.available()) {
      LoRaData = LoRa.readString();
      Serial.print(LoRaData);
    }

    //print data from packet
    int rssi = LoRa.packetRssi();
    Serial.print(" RSSI: ");    
    Serial.println(rssi);

   // Dsiplay information
   display.clearDisplay();
   display.setCursor(0,0);
   display.print("W. LEVEL + LORA");
   display.setCursor(0,20);
   display.print("Message received:");
   display.setCursor(0,30);
   display.print(LoRaData);
   display.setCursor(0,40);
   display.print("RSSI:");
   display.setCursor(30,40);
   display.print(rssi);
   display.display(); 
    // ping Adafruit IO to verify connection
    if(! mqtt.ping(3))
    {
      // Adafruit IO re-connection
      if(! mqtt.connected())
        connect_adafruit();
    }
    if (!water_level.publish(LoRaData.c_str())) {  //Sending water level via MQTT
      Serial.println(F("Failure"));
    }
    else {
      Serial.println(F("Sent it!"));
    }  
  }
}
