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

#### MQTT Broker
IP address or name. Required, no default.-

MQTT_BROKER


#### MQTT Broker Port
Default 1883

MQTT_PORT


#### Subscribe Topic
Topic base for subscription. Default RL/#

SUB_TOPIC    


#### DB Host
Ip address or name. Default db.

POSTGRES_HOST


#### DB Name
Default eter.

POSTGRES_DB


#### DB User
Default eter.

POSTGRES_USER


#### DB Pass
Default empty string

POSTGRES_PASSWORD
