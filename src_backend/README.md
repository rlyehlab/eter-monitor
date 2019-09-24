# Eter - Puente MQTT a Postgresql

## Correr

    docker-compose up -d

### Ver registro

    docker-compose logs mqttpg


### Apagar

    docker-compose down

### Borrar volúmenes de datos

  docker-compose down -v


## Instalación

### Crear tablas

  docker exec -it eter_db /sql/import.sh

## Configurar

El servidor se configura por medio de variables de entorno cargadas desde el archivo `.env`.
El servidor ya funciona con la configuración default.

`MQTT_BROKER` Dirección IP o nombre del servidor MQTT. Sin default. Requerido.

`MQTT_PORT` Default 1883.

`SUB_TOPIC` Topico MQTT base para la subscripción. Default ETER/#

`POSTGRES_HOST` Dirección IP o nombre del servidor de base de datos. Default db.

`POSTGRES_DB` Base de datos. Default eter.

`POSTGRES_USER` Usuario. Default eter.

`POSTGRES_PASSWORD` Contraseña. Default empty string.
