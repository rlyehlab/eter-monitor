from config import *
from db import DB, pg
import xxhash
import paho.mqtt.client as mqtt
import time
import json

def hash(content):
  return xxhash.xxh64(content).hexdigest()

MESSAGE_INSERT = "INSERT INTO messages (hash, topic, message) VALUES (%s, %s, %s);"
DATA_INSERT = "INSERT INTO measurements (hash, mac, type, data) VALUES (%s, %s, %s, %s);"


def log_msg(msg):
  hash_date = time.strftime("%Y-%m-%d %H:%M")
  payload = str(msg.payload.decode("utf-8"))
  contents = "%s %s %s" % (hash_date, msg.topic, payload)
  print(contents)
  hash_key = hash(contents)
  print(hash_key)
  db.query(MESSAGE_INSERT, (hash_key, msg.topic, payload))
  return hash_key

def log_data(hash_key, msg):
  (_, mac, type, msgid) = msg.topic.split('/', 3)
  # maybe in the future do something with the data?
  # data = json.loads(str(msg.payload.decode("utf-8")))
  data = str(msg.payload.decode("utf-8"))
  db.query(DATA_INSERT, (hash_key, mac, type, data))


db = None

def run():
  global db
  db = DB(db_hostname, db_database, db_username, db_password)
  db.connect()

  client = mqtt.Client()
  client.on_connect = on_connect
  client.on_message = on_message

  client.connect(broker, broker_port)

  # Blocking call that processes network traffic, dispatches callbacks and
  # handles reconnecting.
  client.loop_forever()

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
  print("Connected to MQTT with result code "+str(rc))

  # Subscribing in on_connect() means that if we lose the connection and
  # reconnect then subscriptions will be renewed.
  client.subscribe(sub_topic)

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
  try:
    hash_key = log_msg(msg)
    log_data(hash_key, msg)

  except Exception as e:
    print("Returning from on_message: %s %s %s" % (t.__module__, t.__name__, e))
    return
