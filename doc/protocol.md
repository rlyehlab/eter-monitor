# Protocolo Eter

La versión 1.0 del dispositivo Eter se comunica por MQTT pero podria hacerlo por cualquier medio, en preferencia que soporte 
tópicos (canales, asuntos).

## Tópico

Es una cadena de texto separada por barras `/` compuesto de 4 partes. De mas general al principio a mas especifico hacia el final.

- Proyecto o canal general. Por default `RL`. El backend ignora todos los mensajes que no tengan este canal.

- Dirección MAC única del dispositivo. Identifica al dispositivo que reporta los datos. Si el dispositivo estuviera asociado a una ubicación esto seriviría para geo-localizar esos datos. Ejemplo `00004444BBBBFFFF`

- Tipo de dato. Cada tipo de dato tiene un formato asociado. Describe el formato del contenido del mensaje. Aunque en Eter todos los mensajes son JSON diferentes tipos de datos pueden tener diferentes campos. Ejemplo `PMS` o `DHT` para Eter 1.0.

- Contador. Un identificador único para el mensaje en el corto plazo. Sirve para desambiguar los mensajes con los mismos valores y mantener el orden en caso de que se dupliquen o desordenen los mensajes. 


## Datos

Los datos en la primer versión de Eter estan formateados como JSON. En principio podrian tener cualquier formato que soporte MQTT o el canal por el que se comuniquen dejando a quien decodifica leer como corresponse según el tipo de dato, pero el servidor asume que es JSON. Ejemplo `{"temperature":"38.76", "humidity":"0.97"}`

## Identificador Único de Mensaje

Con la fecha de recepción, el tópico y el mensaje concatenados, separados por un único espacio se calcula un hash que sirve para identificar y desambiguar el mensaje. Formato `2019-12-13 23:45 ETER/0/TEST/0 {"test":"1"}`. El servidor de Eter utiliza la representación hexadecimal del [xxhash](https://github.com/Cyan4973/xxHash) de 64 bits para mayor velocidad. 

El formato de la fecha debe ser lo suficientemente amplio para que una pequeña variacion en la recepción no la afecte pero no tanto como para que el contador se desborde y vuelva a repetirse. En el caso de Eter es `%Y-%m-%d %H:%M`. Es posible que esto de lugar a hashes diferentes y mensajes duplicados pero pueden identificarse comparando el tiempo de recepcion y el contador del mensaje.

## Implementación de Ejemplo

Una implementación del [protocolo Eter en Python](/src_backend/example/eter.py) esta disponible en este mismo repositorio.