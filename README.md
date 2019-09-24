# Dispositivo Eter

El dispositivo Eter, es un conjunto de sensores que reportan la calidad de aire mediante el uso del sensor PMS5003 y el sensor DHT22 de temperatura y humedad relativa. 

Se utiliza el microcontrolador NodeMCU que está basado en la placa ESP8266 para recibir las mediciones y enviarlas por medio del protocolo MQTT y el uso de la red wifi.

Uno o varios servidores reciben los mensajes MQTT y los almacenan en una base de datos para posterior procesamiento.

# [¿Cómo instalar el dispositivo?](src_sensor/README.md)
# [¿Cómo instalar el servidor?](src_backend/README.md)
# [¿Qué formato tienen los mensajes MQTT?](doc/protocol.md)