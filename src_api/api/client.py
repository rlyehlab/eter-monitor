from paho.mqtt.client import *



class ClientMqtt(Client):


    def __init__(self):
        Client.__init__(self, client_id="", clean_session=True, userdata=None,
                protocol=MQTTv311, transport="tcp")
        self._data_payload = dict()
        self._data_topic = ""
        self._state_msg = None


    def process_msg(self, msg):
        topic = msg.topic
        geoloc = topic.split('/')[0]
        sensor = topic.split('/')[1]
        variable = topic.split('/')[2]
        value = msg.payload.decode("utf-8")
        self._data_payload = {
                'geoloc':geoloc,
                'sensor':sensor,
                'variable':variable,
                'value':value
                       }
        #self._state_msg = True
        return True


