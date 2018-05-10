from flask import Blueprint
#from api.client import mqtt
from flask_mqtt import Mqtt

#from api.background import fetch_measure
mqtt = Mqtt()

client = Blueprint('client', __name__)


@client.route('/topic/<name>')
def topic(name):
    mqtt.subscribe('AREA_RECON/#')
    return str(name)



@mqtt.on_topic('AREA_RECON/#')
def handle_mytopic(client, userdata, message):
    print('Received message on topic {}: {}'
            .format(message.topic, message.payload.decode()))



