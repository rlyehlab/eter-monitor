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
int secmil;

byte buf[26];  //serial read buffer



char topic_dht[110];
char topic_pms[110];
char sec[10];

void setup() {
  Serial.begin(9600); 
  Serial.setTimeout(1500); 
  setup_wifi();
  macadd = WiFi.macAddress();
  Serial.print(macadd);
  dht_init();
  delay(30000);//pms5003 necesita 30 segundos para empezar a medir.
  
}


void loop() {
  //delay(TIME_DELAY);


  if (!check_connection()) {
    reconnect();
  }  else {
     client.loop();
           pm_measure = pm_sensor();

         if (pm_measure.check){
           pm_json=generatePmJson(pm_measure); 
           
             // Create a topic string and publish data to ThingSpeak channel feed. 
            int length=pm_json.length();
            char pmjBuffer[length];
            pm_json.toCharArray(pmjBuffer,length+1);
 
           Serial.println(pmjBuffer);
           secmil=millis();
           //limpiar array
           memset(sec, 0, sizeof(sec));
           memset(topic_pms, 0, sizeof(topic_pms));

           sprintf(sec, "%d", secmil);
           strcpy(topic_pms, TOPICO_PMS);
           strcat(topic_pms,sec);
           Serial.println(topic_pms);
           client.publish(topic_pms, pmjBuffer);
         }


 
                dht_measure = dht_sensor();
             // mido dht despues de publicar pm
           if (pm_measure.check && dht_measure.check){
               dht_json= generateDhtJson(dht_measure);
               int length=dht_json.length();
               char dhtjBuffer[length];
               dht_json.toCharArray(dhtjBuffer,length+1);
               Serial.println(dhtjBuffer);

              //arreglar que si no mide tira excepcion el pub
               //limpiar array
               memset(sec, 0, sizeof(sec));
               memset(topic_dht, 0, sizeof(topic_dht));
               secmil=millis();
               sprintf(sec, "%d", secmil);
               strcpy(topic_dht, TOPICO_DHT);
               strcat(topic_dht,sec);
               Serial.println(topic_dht);

                client.publish(topic_dht, dhtjBuffer);

                //queremos un delay solo justo despues de enviar
                delay(30000);
                
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
