//#define pin D4


void dht_init() {
  pinMode(DHTPIN, INPUT);
  dht.begin();
}

dht_med dht_sensor(){

  dht_med measure; //define struct dht_med
  measure.check=false;
  measure.hum = dht.readHumidity();
  measure.tem = dht.readTemperature();
  if (isnan(measure.hum) || isnan(measure.tem)){
    measure.check=false;
    Serial.print("Error with DHT ");
  }
  measure.check=true;
  return measure;
}
