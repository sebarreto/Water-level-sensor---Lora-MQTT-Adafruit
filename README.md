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
   
2. Tin soldering iron

   Depending on which ESP32 module did you buy it'll be a good idea to get a tin soldering iron. It'll work anyway, but some connections will be a little shaky.

## Software solution
