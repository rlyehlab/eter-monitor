from celery import Celery
from api.client import ClientMqtt
from api.models import db, Measure, Device, Sensor
import time


BACKEND = BROKER = 'redis://localhost:6379'


celery = Celery(__name__, backend=BACKEND, broker=BROKER)


@celery.task
def create_client_mqtt():
    from api.app import create_app
    app = create_app()
    db.init_app(app)
    with app.app_context():
        client2mqtt = client_mqtt()
        client2mqtt.loop_start()
        while True:
            if client2mqtt._state_msg:
                data_mqtt = client2mqtt._data_payload
                print("save....")
                measure_save(data_mqtt)
                client2mqtt._state_msg = False
    return True


def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe('AREA_RECON/#')


def on_message(client, userdata, msg):
    client._state_msg = True
    print(msg.topic)
    time.sleep(1)
    client.process_msg(msg)
    print("process.....")
    #client._state_msg = False


def client_mqtt():
    client = ClientMqtt()
    client.on_connect = on_connect
    client.on_message = on_message
    client.connect("localhost", 1883)
    return client


def measure_db(data):
    print("almacenando data")
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
                Sensor.name == data_mqtt['sensor'],
                Sensor.variable.like(data_mqtt['variable']+'%')
                ).first()

        data['id_device'] = q_device.id
        data['id_sensor'] = q_sensor.id
        data['value'] = data_mqtt['value']
        print(data)
        db.session.add(measure_db(data))
    db.session.commit()
    return True
