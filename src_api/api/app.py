#!/usr/bin/env python3
from flask import Flask
from api.views import blueprints
from api.models import db, Measure




def create_app():

    app = Flask(__name__)


    app.config['MQTT_KEEPALIVE'] = 5  # set the time interval for sending a ping to the broker to 5 seconds
    app.config['MQTT_TLS_ENABLED'] = False  # set TLS to disabled for testing purposes
    app.config['SQLALCHEMY_DATABASE_URI'] = 'postgresql://admin:eter2018@localhost/eter'



    for bp in blueprints:
        app.register_blueprint(bp)


    db.init_app(app)
    db.create_all(app=app)

    #with app.app_context():
    #    measure = Measure(sensor_id=1, device_id=1, value=30)
    #    db.session.add(measure)
    #    db.session.commit()


    return app
