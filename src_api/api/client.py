import paho.mqtt.client as mqtt

# -------
# basado en https://www.hivemq.com/blog/mqtt-client-library-paho-python


client = mqtt.Client()


def on_subscribe(client, userdata, mid, granted_qos):
    print("Subscribed: "+str(mid)+" "+str(granted_qos))


def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.qos)+" "+str(msg.payload))


client.on_subscribe = on_subscribe
client.on_message = on_message
client.connect('localhost', 1883)
client.subscribe('AREA_RECON/#', qos=1)

#client.loop_forever()
