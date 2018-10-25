#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* MQTT_SERVER= "....";
const uint16_t MQTT_PORT = 1883;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting");
  Serial.println(SSID_W);
  WiFi.begin(SSID_W, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);
}


void reconnect() {
  while (!client.connected()) {
    Serial.print("Trying to connect");
    if (client.connect("ESP8266Client")) {
      Serial.println("Connected");
      client.subscribe("inTopic");
    } else {
      Serial.print("Failed connection");
      Serial.print(client.state());
      Serial.println(" trying again ...");
     }
  }
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

bool check_connection(){
    if (!client.connected()) {
    reconnect();
  }else{
    return true;
  }
}


void pub(char* topico, String msg){
  char mbuffer[msg.length() + 1];
  msg.toCharArray(mbuffer, msg.length()+1);
  Serial.print(msg);

  if (! client.publish(topico, mbuffer)) {
      Serial.println("\n We had a problem publishing");
    } else {
      Serial.println("\n Message sent!");
    }

  
  
}
