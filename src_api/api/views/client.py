from flask import Blueprint
from api.background import create_client_mqtt


client = Blueprint('client', __name__)


@client.route('/<broker_config>')
def index(broker_config):
    broker_config = {
            'topic':'AREA_RECON/#',
            'broker':'localhost',
            'port':1883}
    print(broker_config)
    task_client = create_client_mqtt.delay(broker_config)
    return str("Measure ....")






