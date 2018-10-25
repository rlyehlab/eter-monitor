const int PMArrayLength=31;
//unsigned char buf2[PMArrayLength];

pmsData pm_sensor_bck(){
  pmsData pm_measure;
  pm_measure.check = false; 
  if (Serial.find(0x42)) {
    pm_measure.pm10_env=0;



    Serial.readBytes(buf, PMArrayLength);
    if (buf[0] == 0x4d) {
      if (checkValue(buf, PMArrayLength)) {
        pm_measure.check = true; 
        //----------------------------- STANDARD -----------------------------------------------//
        pm_measure.pm10_standard = getData(3,4,buf);
        pm_measure.pm25_standard = getData(5,6,buf);
        pm_measure.pm100_standard  = getData(7,8,buf);
        //------------------------------------ ENVIRONMENT --------------------------------//
        pm_measure.pm10_env  = getData(9,10,buf);
        pm_measure.pm25_env  = getData(11,12,buf);
        pm_measure.pm100_env  = getData(13,14,buf);
        
        /**el broker que estamos usando no nos deja mandar un json tan largo, cuando migremos, descomentar.
        //------------------------------ PARTICLES NUMBER ----------------------------------//
        pm_measure.particles_03um  = getData(15,16,buf);
        pm_measure.particles_05um  = getData(17,18,buf);
        pm_measure.particles_10um  = getData(19,20,buf);
        pm_measure.particles_25um  = getData(21,22,buf);
        pm_measure.particles_50um  = getData(23,24,buf);
        pm_measure.particles_100um  = getData(25,26,buf);
       **/
     }
    }
  }
  return pm_measure;
}

pmsData pm_sensor(){
  pmsData pm_measure;
  pm_measure.check = false; 

//buscamos el 42
if( Serial.find(0x42) ){
    Serial.println("encontrado");
    if( Serial.available() > 30 ){
      uint8_t buffer[32];
      uint16_t sum = 0;
      Serial.readBytes(buffer,32);
      if (checkValue(buffer, PMArrayLength)) {
        pm_measure.check = true;
        //----------------------------- STANDARD -----------------------------------------------//
        pm_measure.pm10_standard = getData(3,4,buffer);
        pm_measure.pm25_standard = getData(5,6,buffer);
        pm_measure.pm100_standard  = getData(7,8,buffer);
        //------------------------------------ ENVIRONMENT --------------------------------//
        pm_measure.pm10_env  = getData(9,10,buffer);
        pm_measure.pm25_env  = getData(11,12,buffer);
        pm_measure.pm100_env  = getData(13,14,buffer);
        return pm_measure;
      }else{
        Serial.print("checksum failed");
      }
    }else{
      Serial.print("menos de 32 bytes");
    }

}


  return pm_measure;
}


unsigned int getData(char high, char low, unsigned char *thebuf){
  float val;
  val = ((thebuf[high] << 8) + thebuf[low]);
  return val;
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
