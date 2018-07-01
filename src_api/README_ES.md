# Eter-Monitor

Eter-monitor corresponde a la aplicación que se encarga de tomar las mediciones del dispositivo y almacenar en la base de datos.

El sistema usa el protocolo mqtt para la comunicación del dispositivo (sensores) y la base de datos donde esta ubicado el broker. La aplicación está en python y se utiliza [mosquitto](https://mosquitto.org/) en la implementación del protocolo mqtt y la base de datos que se utiliza es postgresql.

## Instalación y requerimientos

