from flask_mqtt import Mqtt



mqtt = Mqtt()


#@mqtt.on_message()
#def handle_mqtt_message(client, userdata, message):
#    data = dict(
#            topic=message.topic,
#            payload=message.payload.decode()
#            )
#    print(data)
#    topic = data['topic'].split('/')
#    lugar = topic[0]
#    sensor = topic[1]
#    variable = topic[2]
#    value = data['payload']
#    if variable == 'TEMP':
#        #print(value)
#        med_db = Measure(sensor_id=sensor, device_id=1, value=value)
#    elif variable == 'HUM':
#        #print(value)
#        med_db = Measure(sensor_id=sensor, device_id=2, value=value)
#    db.session.add(med_db)
#    db.session.commit()
#
#    return data
#

