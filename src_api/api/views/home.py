from flask import Blueprint
from api.background import create_client_mqtt


home = Blueprint('home', __name__)


@client.route('/')
def index():
    return str("Measure ....")



