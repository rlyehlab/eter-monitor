/*
 * Eter v1.0
 * https://github.com/rlyehlab/eter-monitor
 * 
 *
*/
#include <Arduino.h>
#include <DHT.h>
#include "red.h"

#define PMArrayLenth 31
#define pin D4
#define DHTPIN D2  //DHT 
#define DHTTYPE DHT22  //DHT 

char *lugar = "AREA_RECON";
unsigned char buf[PMArrayLenth];

int PM01Value = 0; //define PM1.0 value
int PM2_5Value = 0; //define PM2.5 value
int PM10Value = 0; //define PM10 value


DHT dht(DHTPIN, DHTTYPE); 

struct dht_med{
  float tem;
  float hum;
};


struct pm_med{
  int check;
  float pm_1;
  float pm_2_5;
  float pm_10;
};


WiFiClient espClient;
PubSubClient client(espClient);

char *topico = "";



void setup() {
  Serial.begin(9600); //configure the baudrate pm5003
  //Serial.setTimeout(1500); //set the Timeout to 1500ms
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(DHTPIN, INPUT);
  //dht.begin();

}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  pm_med pm_measure = pm_sensor();
  if (pm_measure.check){
      char TEM_measure[6]= "";
      char HUM_measure[6]= "";
      char PM1_measure[6]= "";
      char PM2_5_measure[6]= "";
      char PM10_measure[6]= "";
  
      dht_med dht_measure = dht_sensor();
      
      float tem_med = dht_measure.tem;
      float hum_med = dht_measure.hum;
      float pm1 = pm_measure.pm_1;
      float pm2_5 = pm_measure.pm_2_5;    
      float pm10 = pm_measure.pm_10;
          
  
      // Publicar mediciones de sensores ........
      sprintf(TEM_measure, "%.02f", tem_med); //convertir a char*
      sprintf(HUM_measure, "%.02f", hum_med); //convertir a char*
      sprintf(PM1_measure, "%.02f", pm1); //convertir a char*
      sprintf(PM2_5_measure, "%.02f", pm2_5); //convertir a char*
      sprintf(PM10_measure, "%.02f", pm10); //convertir a char*
      pub("AREA_RECON/DHT22/TEM", TEM_measure);
      pub("AREA_RECON/DHT22/HUM", HUM_measure);
      pub("AREA_RECON/PM5003/PM1", PM1_measure);
      pub("AREA_RECON/PM5003/PM2.5", PM2_5_measure );
      pub("AREA_RECON/PM5003/PM10", PM10_measure );
    delay(30000);
   }
}

pm_med pm_sensor(){

  pm_med pm_measure;
  pm_measure.check = 0; 
  if (Serial.find(0x42)) {
    Serial.readBytes(buf, PMArrayLenth);
    if (buf[0] == 0x4d) {
      if (checkValue(buf, PMArrayLenth)) {
        pm_measure.check = 1;         
        pm_measure.pm_1 = transmitPM01(buf); 
        pm_measure.pm_2_5 = transmitPM2_5(buf);
        pm_measure.pm_10 = transmitPM10(buf);
      }
    }
  }
  return pm_measure;
}


void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}




void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}


void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      client.publish("outTopic", "hello world");
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

dht_med dht_sensor(){

  dht_med measure; //define struct dht_med

  measure.hum = dht.readHumidity();
  measure.tem = dht.readTemperature();
  if (isnan(measure.hum) || isnan(measure.tem)){
    Serial.println();
    Serial.print("Error DHT:");
    Serial.println();    
  }
  return measure;
}

char checkValue(unsigned char *thebuf, char leng) {
  char receiveflag = 0;
  int receiveSum = 0;
  for (int i = 0; i < (leng - 2); i++) {
    receiveSum = receiveSum + thebuf[i];
  }
  receiveSum = receiveSum + 0x42;
  if (receiveSum == ((thebuf[leng - 2] << 8) + thebuf[leng - 1])){ 
    //check the serial data
    receiveSum = 0;
    receiveflag = 1;
  }
  return receiveflag;
} 


//count PM1.0 value of the air detector module
int transmitPM01(unsigned char *thebuf) {
  float PM01Val;
  PM01Val = ((thebuf[3] << 8) + thebuf[4]);
  Serial.print("PM01: ");
  Serial.println(PM01Val);
  return PM01Val;
}


int transmitPM2_5(unsigned char *thebuf) {
  float PM2_5Val;
  PM2_5Val = ((thebuf[5] << 8) + thebuf[6]);
  Serial.print("PM2.5: ");
  Serial.println(PM2_5Val);
  return PM2_5Val;
}

  
//count PM10 value of the air detector module
int transmitPM10( unsigned char *thebuf) {
  float PM10Val;
  PM10Val = (( thebuf[7] << 8) + thebuf[8]);
  Serial.print("PM10: ");
  Serial.println(PM10Val);
  return PM10Val;
}

void pub(char *topico, char *msg){
  
  Serial.print("Publish message: ");
  Serial.print(topico);
  Serial.print(":");
  Serial.println(msg);
  client.publish(topico, msg);

}
