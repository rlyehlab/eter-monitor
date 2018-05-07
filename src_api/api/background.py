from celery import Celery
from api.client import client


BACKEND = BROKER = 'redis://localhost:6379'

celery = Celery(__name__, backend=BACKEND, broker=BROKER)

@celery.task
def fetch_measure():
    client.loop_forever()
    return True


