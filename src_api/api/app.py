#!/usr/bin/env python3
from flask import Flask
from api.views import blueprints
from api.client import mqtt
from api.models import db Measure


app = Flask(__name__)

app.config['MQTT_BROKER_URL'] = 'localhost'
app.config['MQTT_BROKER_PORT'] = 1883
app.config['MQTT_USERNAME'] = ''
app.config['MQTT_PASSWORD'] = ''
app.config['MQTT_KEEPALIVE'] = 5  # set the time interval for sending a ping to the broker to 5 seconds
app.config['MQTT_TLS_ENABLED'] = False  # set TLS to disabled for testing purposes
app.config['SQLALCHEMY_DATABASE_URI'] = 'postgresql://admin:eter2018@localhost/eter'



db.init_app(app)

for bp in blueprints:
    app.register_blueprint(bp)




mqtt.init_app(app)

@mqtt.on_connect()
def handle_connect(client, userdata, flags, rc):
    mqtt.subscribe('AREA_RECON/#')

@mqtt.on_message()
def handle_mqtt_message(client, userdata, message):
    data = dict(
            topic=message.topic,
            payload=message.payload.decode()
            )
    print(data)
    return data



db.create_all(app=app)
