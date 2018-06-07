from celery import Celery
from api.client import ClientMqtt
from api.models import db, Measure, Device, Sensor
import time


BACKEND = BROKER = 'redis://localhost:6379'


celery = Celery(__name__, backend=BACKEND, broker=BROKER)


@celery.task
def create_client_mqtt(broker_config):
    from api.app import create_app
    app = create_app()
    db.init_app(app)
    with app.app_context():
        client2mqtt = client_mqtt(broker_config)
        client2mqtt.loop_start()
        while True:
            if client2mqtt._state_msg:
                data_mqtt = client2mqtt._data_payload
                measure_save(data_mqtt)
                client2mqtt._state_msg = False
    return True


def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+ str(rc))
    client.subscribe(client._data_topic)


def on_message(client, userdata, msg):

    client._state_msg = True
    print(msg.topic + ' : '+ msg.payload.decode('utf-8'))
    time.sleep(1)
    client.process_msg(msg)


def client_mqtt(broker_config):
    topic_name = broker_config['topic']
    broker_name = broker_config['broker']
    port_name = broker_config['port']
    #port_name = 1883
    client = ClientMqtt()
    client.on_connect = on_connect
    client.on_message = on_message
    client._data_topic = topic_name
    client.connect(broker_name, port_name)
    return client


def measure_db(data):
    measure = Measure()
    measure.sensor_id = data['id_sensor']
    measure.device_id = data['id_device']
    measure.value = data['value']
    return measure


def measure_save(data_mqtt):
    data = dict()
    if data_mqtt:

        q_device = db.session.query(Device).filter(
                Device.geolocation == data_mqtt['geoloc']
                ).first()
        q_sensor = db.session.query(Sensor).filter(
                Sensor.name.like(data_mqtt['sensor']+'%'),
                Sensor.variable.like(data_mqtt['variable']+'%')
                ).first()

        data['id_device'] = q_device.id
        data['id_sensor'] = q_sensor.id
        data['value'] = data_mqtt['value']
        db.session.add(measure_db(data))
    db.session.commit()
    return True
