import paho.mqtt.client as mqtt



def on_connect(client, userdata, flags, rc):
    print(“CONNACK received with code %d.” % (rc))




client = mqtt.Client()
client.on_connect = on_connect
client.connect(“localhost”, 1883)
