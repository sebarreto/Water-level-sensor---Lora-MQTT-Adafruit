# Water-level-sensor + LoRa + MQTT + Adafruit
Project with a water level sensor and sending packages using LoRa peer-to-peer connection + MQTT + Adafruit to visualize

![General Architecture](https://i.postimg.cc/Mpr0xDKt/architecture.png)

## List of materials

1. Solu SL067 water level sensor.
2. LILYGO® TTGO 1/2Pcs LoRa32 V1.0 (LoRa SX1276 ESP32) - 868Mhz (Europe).
3. Battey 9v.
4. Protoboard.
5. Battety - Protoboard plug MB102.
6. USB wire type B (ideally x2).
7. Wires male-female x 3.

I spent around **25 dollars** in 2023. I bought everything via Aliexpress. You can also find components via Amazon, Ebay and local stores.

## Hardware recommendations

1. ESP32 LoRa board.

   Frequency selection:
   
   ![ESP32 LoRa board](https://i.postimg.cc/1zXQV9Ss/esp32-Lo-Ra-board.png)

   There are different brands and models out there. I only tried this brand (Lilygo). Pay attention to LoRa frequency, differents geographical zones will have different operation frequency. In this example it is just peer-to-peer connection, although you might try to test LoRaWAN and solutions as The Things of Networks (TTN) to device management.

   Pin diagram:
   
   ![ESP32 LoRa diagram](https://i.postimg.cc/rFgyDZ4G/esp32-diagram.jpg)

   In my case, the diagram coming with TTGO board was incorrect. I didn't know pin numbers until I found this improved diagram. I don't remember where I got it, but thanks stranger.
   
3. Tin soldering iron

   Depending on which ESP32 module did you buy it'll be a good idea to get a tin soldering iron. It'll work anyway, but some connections will be a little shaky.

## Software solution

For this project I decided to practice with Arduino IDE (C++). I've created two folder. One for ESP32 sender and one for ESP32 receiver.

![ESP32 sender & receptor](https://i.postimg.cc/QdkSRc14/water-level-folder-computer.png)

> In receptor folder I also included external password file (Wi-Fi & MQTT credentials).

1. Sender.

You'll find comments in the code (water_level_lora_sender.ino) basically...
- You must include libraries to handle LoRa.
- Configure external display screen.
- Configure the input/output water level sensor pins. Here is a detailed guide: [circuits-diy](https://www.circuits-diy.com/solu-sl067-water-sensor-arduino-tutorial/).
- Send read value.
- Visualization of variables and complementary information.

2. Receptor.

You'll find comments in the code (water_level_lora_receptor.ino) basically...
- You must include libraries to handle LoRa, MQTT and Wi-Fi.
- Modify the file home_wifi_mqtt.h
- Configure external display screen.
- Configure MQTT client and publish.
- Send value via MQTT to Adafruit.
- Visualization of variables and complementary information.

3. Adafruit

You need to create an account on Adafruit IO: [Adafruit IO](https://io.adafruit.com/).
- Create and activate your account.
- Get your Adafruit TOKEN.
- Create your feed. Here a guide: [Adafruit IO feeds](https://learn.adafruit.com/adafruit-io-basics-feeds).
- Create your dashboard. Here a guide: [Adafruit IO dashboard](https://cdn-learn.adafruit.com/downloads/pdf/adafruit-io-basics-dashboards.pdf).

## Project implementation

- Here the "Sender" I've connected it with a battery. So I can move it, and also because I had only one UBS B connector XD.

![ESP32 sender](https://i.postimg.cc/FzN0bBnh/water-level-sensor-1.jpg) 
  
- Here the "Receptor".

![ESP32 receptor](https://i.postimg.cc/sgv7JSKG/water-level-sensor-2.jpg)

> I took really bad pictures XD. When both are connected and sending data screens show the messages that we've programmed.
  
- Adafruit.

![ESP32 feed](https://i.postimg.cc/25WWsDsz/adafruit-1.png)

![ESP32 dashboard](https://i.postimg.cc/DZdXzcfH/adafruit-dashboard.png)

> You can use another platform like Grafana.
