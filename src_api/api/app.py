#!/usr/bin/env python3
from flask import Flask
from api.views import blueprints
from api.views.client import mqtt
from api.models import db, Measure


app = Flask(__name__)


app.config['MQTT_BROKER_URL'] = 'localhost'
app.config['MQTT_BROKER_PORT'] = 1883
app.config['MQTT_USERNAME'] = ''
app.config['MQTT_PASSWORD'] = ''
app.config['MQTT_KEEPALIVE'] = 5  # set the time interval for sending a ping to the broker to 5 seconds
app.config['MQTT_TLS_ENABLED'] = False  # set TLS to disabled for testing purposes
app.config['SQLALCHEMY_DATABASE_URI'] = 'postgresql://admin:eter2018@localhost/eter'



db.init_app(app)
mqtt.init_app(app)

for bp in blueprints:
    app.register_blueprint(bp)



db.create_all(app=app)






