#include <Arduino.h>
#define PMArrayLenth 31
#define pin D4

unsigned char buf[PMArrayLenth];

int PM01Value = 0; //define PM1.0 value
int PM2_5Value = 0; //define PM2.5 value
int PM10Value = 0; //define PM10 value



void setup() {
  Serial.begin(9600); //configure the baudrate
  Serial.setTimeout(1500); //set the Timeout to 1500ms
}

void loop() {
  
  if (Serial.find(0x42)) {
    Serial.readBytes(buf, PMArrayLenth);
    if (buf[0] == 0x4d) {
      if (checkValue(buf, PMArrayLenth)) {
        PM01Value = transmitPM01(buf);
        Serial.println("--");
        PM2_5Value = transmitPM2_5(buf);
        Serial.println("--"); 
        PM10Value = transmitPM10(buf);
        Serial.println("--");  
      }
    }
  }

  delay(5000);
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
