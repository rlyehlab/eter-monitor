# Eter MQTT to Postgresql Bridge

## Run

    docker-compose up -d

### Check logs

    docker-compose logs mqttpg


## Setup

### Create tables

  docker exec -it eter_db /sql/import.sh

### Delete database data

  docker-compose down -v


## Config

Configure via environment variables in .env file.

`MQTT_BROKER` IP address or name. Required, no default.

`MQTT_PORT` Default 1883.

`SUB_TOPIC` Topic base for subscription. Default ETER/#

`POSTGRES_HOST` Ip address or name. Default db.

`POSTGRES_DB` Default eter.

`POSTGRES_USER` Default eter.

`POSTGRES_PASSWORD` Default empty string.
