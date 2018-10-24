#define DHTPIN D2  //DHT 
#define DHTTYPE DHT22  //DHT 


struct pmsData {
  bool check;
  uint16_t pm10_standard, pm25_standard, pm100_standard;
  uint16_t pm10_env, pm25_env, pm100_env;
  uint16_t particles_03um, particles_05um, particles_10um, particles_25um, particles_50um, particles_100um;
  uint16_t checksum;
};

struct dht_med{
  bool check;
  float tem;
  float hum;
};
DHT dht(DHTPIN, DHTTYPE); 
