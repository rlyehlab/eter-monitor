from flask import Blueprint
from api.client import mqtt

#from api.background import fetch_measure


client = Blueprint('client', __name__)


@client.route('/topic/<name>')
def topic(name):
    return str(name)



