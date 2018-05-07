from flask import Blueprint
from api.background import fetch_measure


client = Blueprint('client', __name__)

@client.route('/')
def index():
    print("ruta:/")
    measure = fetch_measure.delay()
    return str("fetch measure")
