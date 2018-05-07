/*
 * Eter v1.0
 * https://github.com/rlyehlab/eter-monitor
 * 
*/


#include <DHT.h>
#include "red.h"

char *lugar = "AREA_RECON";


#define DHTPIN D2  //DHT 
#define DHTTYPE DHT22  //DHT 

DHT dht(DHTPIN, DHTTYPE); 

struct dht_med{
  float tem;
  float hum;
};


WiFiClient espClient;
PubSubClient client(espClient);

//topic : "AREA_RECON/DHT22/HUM/"
char *topico = "";



void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(DHTPIN, INPUT);
  //dht.begin();

}


void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
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
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}



int dust_sensor(){
  //function for dust sensor
  return 0;
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



void pub(char *topico, char *msg){
  
  Serial.print("Publish message: ");
  Serial.print(topico);
  Serial.print(":");
  Serial.println(msg);
  client.publish(topico, msg);

}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
    char TEM_measure[6]= "";
    char HUM_measure[6]= "";

    dht_med measure = dht_sensor();
    float tem_med = measure.tem;
    float hum_med = measure.hum;
    
    Serial.println(".......................");
    Serial.print("temp:");
    Serial.println(tem_med);
    Serial.print("hum:");
    Serial.println(hum_med);
    Serial.println(".......................");

    // Publicar mediciones de sensores ........
    //sprintf(DUS_measure, "%.02f", dust_med); //convertir a char*
    sprintf(TEM_measure, "%.02f", tem_med); //convertir a char*
    sprintf(HUM_measure, "%.02f", hum_med); //convertir a char*
    //pub("AREA_RECON/DUST_SENSOR/DUS", DUS_measure);
    pub("AREA_RECON/DHT22/TEM", TEM_measure);
    pub("AREA_RECON/DHT22/HUM", HUM_measure);
    //

  delay(5000);
}
