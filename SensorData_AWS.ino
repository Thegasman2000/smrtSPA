#include <MQTT.h>
#include <MQTTClient.h>

#include <ArduinoJson.h>

////LIGHT SENSOR CODE
#include "SparkFun_AS7265X.h" //Click here to get the library: http://librarymanager/All#SparkFun_AS7265X
AS7265X sensor;
//#include <Wire.h>
////LIGHT SENSOR CODE

//#include <MQTTClient.h>
#include <Arduino_JSON.h>
#include "config.h"
#include <WiFiClientSecure.h>
//#include "WiFi.h"

// The MQTT topics that this device should publish
#define AWS_IOT_PUBLISH_TOPIC "esp32/pub"

WiFiClientSecure net = WiFiClientSecure();
MQTTClient client = MQTTClient(512);


#define BUFFER_LEN 512
long lastMsg = 0;
char msg[BUFFER_LEN];
int value = 0;
byte mac[6];
char mac_Id[18];
float resolution = 3.3 / 1023;

void connectAWS()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.begin(AWS_IOT_ENDPOINT, 8883, net);
  client.onMessage(messageReceived);
  Serial.print("Connecting to AWS IOT");

  while (!client. connect(THINGNAME)) {
    Serial.print(".");
    delay(100);
  }

  if (!client.connected()) {
    Serial.println("AWS IoT Timeout!");
    return;
  }

  Serial.println("AWS IoT Connected!");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);

  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling `client.loop()`.
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  ////LIGHT SENSOR CODE
  Serial.println("AS7265x Spectral Triad Example");
  if (sensor.begin() == false)
  {
    Serial.println("Sensor does not appear to be connected. Please check wiring. Freezing...");
    while (1)
      ;
  }
  sensor.disableIndicator(); //Turn off the blue status LED

  Serial.println("A,B,C,D,E,F,G,H,R,I,S,J,T,U,V,W,K,L");
  ////LIGHT SENSOR CODE

  connectAWS();
  WiFi.macAddress(mac);
  snprintf(mac_Id, sizeof(mac_Id), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

void loop() {
  long now = millis();
  //  if (now - lastMsg > 2000) {
  //    lastMsg = now;
  //    //============================================================================
  //    String macIdStr = mac_Id;
  //
  //    //char temperature[BUFFER_LEN];
  //    const char input[] = "{\"result\":true,\"count\":\"%d\",\"foo\":\"%d\"}";
  //    //snprintf (temperature, BUFFER_LEN, 1234, 123);
  //    //String airquality = String(now).c_str();
  //    JSONVar myObject;
  //    myObject["hello"] = "world";
  //    myObject["true"] = true;
  //    myObject["x"] = now;
  //    String jsonString = JSON.stringify(myObject);
  //
  //    //snprintf (temperature, BUFFER_LEN, “ {“mac_Id” : “ % s”, “AirQualityIndex” : “ % d”}”, macIdStr.c_str(), airquality.c_str());
  //
  //
  //
  //    //String temperature = String(random(0xffff), HEX);
  //    snprintf (msg, BUFFER_LEN, "{\"MAC_ID\" : \"%s\", \"Temperature\" : \"%s\"}", macIdStr.c_str(), input);
  //    Serial.print("Publish message: ");
  //    Serial.println(msg);
  //    client.publish(AWS_IOT_PUBLISH_TOPIC, msg);
  //    //=============================================================================
  //    Serial.print("Heap: "); Serial.println(ESP.getFreeHeap()); //Low heap can cause problems
  //  }

  //  if (now - lastMsg > 2000) {
  //    lastMsg = now;
  //    //============================================================================
  //    String macIdStr = mac_Id;
  //    float temp = ((analogRead(A0) * resolution) * 100) + 27.3 - random(0, 2) - random(0, 50) / 100;
  //    String temperature = String(temp) + "C ";
  //    String dataPoints = String(temp + 523) + "C ";
  //    //String temperature = String(random(0xffff), HEX);
  //    snprintf (msg, BUFFER_LEN, "{\"MAC_ID\" : \"%s\", \"A\" : \"%s\", \"B\" : \"%s\"}", macIdStr.c_str(), temperature.c_str(), dataPoints.c_str());
  //    Serial.print("Publish message: ");
  //    Serial.println(msg);
  //    client.publish(AWS_IOT_PUBLISH_TOPIC, msg);
  //    //=============================================================================
  //    Serial.print("Heap: "); Serial.println(ESP.getFreeHeap()); //Low heap can cause problems
  //  }

  //LIGHT SENSOR CODE
  String macIdStr = mac_Id;
  String A = String(sensor.getCalibratedA());
  String B = String(sensor.getCalibratedB());
  String C = String(sensor.getCalibratedC());
  String D = String(sensor.getCalibratedD());
  String E = String(sensor.getCalibratedE());
  String F = String(sensor.getCalibratedF());
  String G = String(sensor.getCalibratedG());
  String H = String(sensor.getCalibratedH());
  String R = String(sensor.getCalibratedR());
  String I = String(sensor.getCalibratedI());
  String S = String(sensor.getCalibratedS());
  String J = String(sensor.getCalibratedJ());
  String T = String(sensor.getCalibratedT());
  String U = String(sensor.getCalibratedU());
  String V = String(sensor.getCalibratedV());
  String W = String(sensor.getCalibratedW());
  String K = String(sensor.getCalibratedK());
  String L = String(sensor.getCalibratedL());

  //  String A = String(123);
  //  String B = String(456);
  //  String C = String(789);
  //  String D = String(562);
  //  String E = String(745);
  //  String F = String(234);
  //  String G = String(635);
  //  String H = String(951);
  //  String R = String(125);
  //  String I = String(471);
  //  String S = String(364);
  //  String J = String(556);
  //  String T = String(698);
  //  String U = String(621);
  //  String V = String(423);
  //  String W = String(998);
  //  String K = String(811);
  //  String L = String(610);
  //


  //snprintf (msg, BUFFER_LEN, "{\"MAC_ID\" : \"%s\", \"A\" : \"%s\", \"B\" : \"%s\", \"C\" : \"%s\", \"D\" : \"%s\",\"E\" : \"%s\",\"F\" : \"%s\",\"G\" : \"%s\",\"H\" : \"%s\",\"R\" : \"%s\",\"I\" : \"%s\",\"S\" : \"%s\",\"J\" : \"%s\",\"T\" : \"%s\",\"U\" : \"%s\",\"V\" : \"%s\",\"W\" : \"%s\",\"K\" : \"%s\",\"L\" : \"%s\"}", macIdStr.c_str(), A.c_str(), B.c_str(), C.c_str(), D.c_str(), E.c_str(), F.c_str(), G.c_str(), H.c_str(), R.c_str(), I.c_str(), S.c_str(), J.c_str(), T.c_str(), U.c_str(), V.c_str(), W.c_str(), K.c_str(), L.c_str());
  snprintf (msg, BUFFER_LEN, "{\"MAC_ID\" : \"%s\", \"A\" : \"%s\", \"B\" : \"%s\", \"C\" : \"%s\", \"D\" : \"%s\",\"E\" : \"%s\",\"F\" : \"%s\",\"G\" : \"%s\",\"H\" : \"%s\",\"R\" : \"%s\",\"I\" : \"%s\",\"S\" : \"%s\",\"J\" : \"%s\",\"T\" : \"%s\",\"U\" : \"%s\",\"V\" : \"%s\",\"W\" : \"%s\",\"K\" : \"%s\", \"L\" : \"%s\"}", macIdStr.c_str(), A.c_str(), B.c_str(), C.c_str(), D.c_str(), E.c_str(), F.c_str(), G.c_str(), H.c_str(), R.c_str(), I.c_str(), S.c_str(), J.c_str(), T.c_str(), U.c_str(), V.c_str(), W.c_str(), K.c_str(), L.c_str());
  Serial.print("Publish message: ");
  Serial.println(msg);
  client.publish(AWS_IOT_PUBLISH_TOPIC, msg);
  //LIGHT SENSOR CODE
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(100); // wait for a second
  digitalWrite(LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW
  delay(100); // wait for a second
  delay(3000);
}
