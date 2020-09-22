import paho.mqtt.client as mqtt
import json

# Speaking the ETER protocol 
# Usage Example 
#
# # Connect ( MQTT Server, port )
# e = eter('broker.hivemq.com', 1883)
# 
# # Publish ( Mac address, data type, value )
# e.publish('MAC0000', 'integer', 42)
#
# # Listen (Edit on_connect and on_message)
# e.listen_blocking()

class eter:
    """Report to the ETER"""

    def __init__(self, broker, port, qos=0):
        self.client = mqtt.Client()
        self.mqtt_qos = qos
        self.client.on_connect = self.on_connect
        self.client.on_message = self.on_message
        self.client.connect(broker, port)
        self.counter = 0

    def listen_blocking(self):
        """Blocking call that processes network traffic, dispatches callbacks and
        handles reconnecting."""

        return self.client.loop_forever()
    
    def on_connect(client, userdata, flags, rc):
        """Callback called on each connection to MQTT"""
        # Subscribe to topics here
        # client.subscribe(sub_topic)
        pass
    
    def on_message(client, userdata, msg):
        """Callback called on each message received for subscribed topics"""
        pass
    
    def publish(self, mac, msg_type, data):
        self.counter += 1
        topic = self.topic(mac, msg_type)
        msg = json.dumps(data)
        return self.mqtt_pub(topic, msg)
    
    def topic(self, mac, msg_type):
        return "ETER/%s/%s/%s" % (mac, msg_type, self.counter)

    def mqtt_pub(self, t, m):
        return self.client.publish(t, m, self.mqtt_qos)
