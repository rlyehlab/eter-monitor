# Dispositivo Eter

El dispositivo Eter, es un conjunto de sensores que reportan la calidad de aire mediante el uso del sensor PMS5003 y el sensor DHT22 de temperatura y humedad relativa. 

Se utiliza el microcontrolador NodeMCU que está basado en la placa ESP8266 para recibir las mediciones y enviarlas por medio del protocolo mqtt y el uso de la red wifi. 

## Requerimientos

- NodeMCU
- DHT22
- PMS5003
- Arduino IDE

## Preparación de la placa y librerías

### Instalar modelo de placa ESP8266

Si bien NodeMCU no es una placa de la marca arduino, nos valemos del ide para cargar el código, para ello debemos descargar y seleccionar la placa correspondiente a nuestro modelo.

En el menú, en la sección de archivo nos vamos a preferencias e introducimos la siguiente dirección:


```
http://arduino.esp8266.com/versions/2.4.1/package_esp8266com_index.json
```

Luego en el menú de herramientas seleccionamos placas y nos dirigimos a la parte de *Gestor de tarjetas* e instalamos el modelo **esp8266**

### Instalar librerias

Se necesitan instalar librerías adicionales para el funcionamiento de los sensores y del protocolo mqtt. Las librerías son:

- [DHT](https://github.com/adafruit/DHT-sensor-library)
- [Adafruit Unified Sensor](https://pubsubclient.knolleary.net/)
- [PubSubClient](https://pubsubclient.knolleary.net/)

Para instalar las librerías debemos ir al menú de Arduino Ide, seleccionar *Programa->incluir librerías->gestor de librerías* y luego buscarlas e instalar cada una.


## Cargando el código y configurando la placa

Clonamos el repositorio 

```git clone https://github.com/rlyehlab/eter-monitor.git
```
o podemos solo descargar la carpeta *src_sensor* en la cual se encuentra el código para el arduino. Ahí podrás ver los siguientes archivos:

- config.h
- eter-v1.0.ino
- red.cpp
- red.h

Desde Arduino Ide nos dirigimos al archivo *eter-v1.0.ino* y deberán abrirse los otros archivos en diferentes pestañas. Primero editamos la configuración de red en el archivo *config.h* 

- ssid: Nombre de la red wifi
- papssword: pass de tu wifi
- mqtt_server: 10.82.10.18 

mqtt_server corresponde a la ip del broker, que en este caso apuntaremos al nodo de [R'lyeh](https://rlab.be/).

Finalmente cargamos el código en la placa y ya debería estar midiendo y reportando. Puedes ver los mensajes en la parte superior derecha del arduino ide en el icono de la lupa, esto despliega una venta con el monitor del puerto serial.
