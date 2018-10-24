/*
 * Eter v1.0
 * https://github.com/rlyehlab/eter-monitor
 * 
 *
*/

#include <Arduino.h>
#include <DHT.h>
#include "config.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <TimeLib.h>

void dht_init();
void setup_wifi();
bool check_connection();
pmsData pm_measure;
dht_med dht_measure;
WiFiClient espClient;
PubSubClient client(espClient);
String pm_json;
String dht_json;
String macadd;
int secint;

byte buf[26];  //serial read buffer



char topic_dht[90];
char topic_pms[90];
char sec[3];

void setup() {
  Serial.begin(9600); 
  Serial.setTimeout(1500); 
  setup_wifi();
  macadd = WiFi.macAddress();
  Serial.print(macadd);
  dht_init();
  delay(5000);//pms5003 necesita 30 segundos para empezar a medir.
  
}


void loop() {
  delay(TIME_DELAY);
  pm_measure = pm_sensor();
  dht_measure = dht_sensor();
  if (!check_connection()) {
    reconnect();
  }
  
  else {
     client.loop();
         if (dht_measure.check){
             dht_json= generateDhtJson(dht_measure);
            //arreglar que si no mide tira excepcion el pub
           //limpiar array
           memset(sec, 0, sizeof(sec));
           memset(topic_dht, 0, sizeof(topic_dht));
           secint=second();
           sprintf(sec, "%d", secint);
           strcpy(topic_dht, TOPICO_DHT);
           strcat(topic_dht,sec);
           Serial.println(topic_dht);
           pub(topic_dht, dht_json);
          }
         
         if (pm_measure.check){
           pm_json=generatePmJson(pm_measure); 
           Serial.println(pm_json);
           secint=second();
           //limpiar array
           memset(sec, 0, sizeof(sec));
           memset(topic_pms, 0, sizeof(topic_pms));

           sprintf(sec, "%d", secint);
           strcpy(topic_pms, TOPICO_PMS);
           strcat(topic_pms,sec);
           Serial.println(topic_pms);
           pub(topic_pms, pm_json);
        }

    }
}

String generatePmJson(pmsData measure){

StaticJsonBuffer<300> jsonBuffer;
JsonObject& pms = jsonBuffer.createObject();

  pms["10_std"] = measure.pm10_standard;
  pms["25_std"] = measure.pm25_standard;
  pms["100_std"] = measure.pm100_standard;
  pms["10_env"] = measure.pm10_env;
  pms["25_env"] = measure.pm25_env;
  pms["100_env"] = measure.pm100_env;
  
/** El broker no acepta un mensajetan largo, cuando migremos descomentar
  pms["particles_03um"] = measure.particles_03um;
  pms["particles_05um"] = measure.particles_05um;
  pms["particles_10um"] = measure.particles_10um;
  pms["particles_25um"] = measure.particles_25um;
  pms["particles_50um"] = measure.particles_50um;
  pms["particles_100um"] = measure.particles_100um;
**/

  String bufS;
  pms.printTo(bufS);
  return bufS;
}


String generateDhtJson(dht_med measure){
  
  StaticJsonBuffer<300> jsonBuffer;
  JsonObject& j_dht = jsonBuffer.createObject();

  j_dht["temperatura"] = measure.tem;
  j_dht["humedad"] = measure.hum;


  String bufS;
  j_dht.printTo(bufS);
  return bufS;
}
