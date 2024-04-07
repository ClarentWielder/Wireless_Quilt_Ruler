/*
 *  Simple HTTP get webclient test
 */

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "Adafruit_VL53L1X.h"
#include <EthernetUdp.h>
#include <coap-simple.h>
#include <string>

#define IRQ_PIN 2
#define XSHUT_PIN 3
#define MAX_DIGITS

Adafruit_VL53L1X vl53 = Adafruit_VL53L1X(XSHUT_PIN, IRQ_PIN);
WiFiUDP Udp;
Coap coap(Udp);

const char* ssid     = "HSRouter";
const char* password = "smilingwindow576";

void callback_read_distance(CoapPacket &packet, IPAddress ip, int port) {
  Serial.println("Read Measurement command received");


  int16_t distance;
  if (vl53.dataReady()) {
    // new measurement for the taking!
    distance = vl53.distance();
    if (distance == -1) {
      // something went wrong!
      Serial.print(F("Couldn't get distance: "));
      Serial.println(vl53.vl_status);
      return;
    }
    Serial.print(F("Distance: "));
    Serial.print(distance);
    Serial.println(" mm");
    std::string str_dist = std::to_string(distance);
    size_t payload_len = str_dist.length();
    char* char_dist = &str_dist[0];
    //coap.sendResponse(packet, ip, port, light);


    coap.sendResponse(ip,port,packet.messageid,char_dist,payload_len, COAP_RESPONSE_CODE::COAP_CONTENT, COAP_CONTENT_TYPE::COAP_TEXT_PLAIN, packet.token, packet.tokenlen);
    // data is read out, time for another reading!
    vl53.clearInterrupt();
  }
}


void setup() {
  Serial.begin(115200);
  delay(100);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println(F("Adafruit VL53L1X sensor demo"));

  Wire.begin();
  if (! vl53.begin(0x29, &Wire)) {
    Serial.print(F("Error on init of VL sensor: "));
    Serial.println(vl53.vl_status);
    while (1)       delay(10);
  }
  Serial.println(F("VL53L1X sensor OK!"));

  Serial.print(F("Sensor ID: 0x"));
  Serial.println(vl53.sensorID(), HEX);

  if (! vl53.startRanging()) {
    Serial.print(F("Couldn't start ranging: "));
    Serial.println(vl53.vl_status);
    while (1)       delay(10);
  }
  Serial.println(F("Ranging started"));

  // Valid timing budgets: 15, 20, 33, 50, 100, 200 and 500ms!
  vl53.setTimingBudget(50);
  Serial.print(F("Timing budget (ms): "));
  Serial.println(vl53.getTimingBudget());

  /*
  vl.VL53L1X_SetDistanceThreshold(100, 300, 3, 1);
  vl.VL53L1X_SetInterruptPolarity(0);
  */
  // add server url endpoints.
  // can add multiple endpoint urls.

  coap.server(callback_read_distance, "read_distance");
  // coap.server(callback_text,"text");

  // start coap server/client
  coap.start();
  // coap.start(5683);
}

//int value = 0;

void loop() {
  //Serial.println("Ready");
  coap.loop();
  delay(1000);
}