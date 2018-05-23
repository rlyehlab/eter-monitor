from flask import Blueprint
from api.background import create_client_mqtt


client = Blueprint('client', __name__)


@client.route('/')
def index():
    task_client = create_client_mqtt.delay()
    return str("Measure ....")








