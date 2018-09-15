import os

broker = os.environ.get('MQTT_BROKER', None)         # MQTT broker ip address or name
broker_port = os.environ.get('MQTT_PORT', 1883)      # MQTT broker port

sub_topic = os.environ.get('SUB_TOPIC', "ETER/#")     # Subscribe topic

db_hostname = os.environ.get('POSTGRES_HOST', "db")   # Postgres host ip address or name
db_database = os.environ.get('POSTGRES_DB', "eter")   # Postgres database name
db_username = os.environ.get('POSTGRES_USER', "eter") # Postgres database user name
db_password = os.environ.get('POSTGRES_PASSWORD', "") # Postgres database password
