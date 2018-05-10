from flask_sqlalchemy import SQLAlchemy
from sqlalchemy.dialects.postgresql import JSON
from sqlalchemy import  Column, Integer, JSON, DateTime
from sqlalchemy.orm import relationship


db = SQLAlchemy()


class Base(db.Model):

    __abstract__ = True

    id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    date_created  = db.Column(db.DateTime,  default=db.func.current_timestamp())



class User(Base):

    __tablename__ = 'user'

    name = db.Column(db.Unicode(128))
    email = db.Column(db.Unicode(128), nullable=False)
    password = db.Column(db.Unicode(128))



class Sensor(Base):

    __tablename__ = 'sensor'

    name = db.Column(db.Unicode(30), nullable=False)
    variable = db.Column(db.Unicode(30), nullable=False)
    description = db.Column(db.Unicode(128))



class Measure(Base):

    __tablename__ = 'measure'

    sensor_id = db.Column(db.Integer, db.ForeignKey('sensor.id'))
    sensor = relationship('Sensor')
    device_id = db.Column(db.Integer, db.ForeignKey('device.id'))
    device = relationship('Device')
    value = db.Column(db.Unicode(10), nullable=False)




class Device(Base):

    __tablename__ = 'device'

    state = db.Column(db.Boolean, default=False)
    geolocation = db.Column(db.Unicode(128))
    user_id = db.Column(db.Integer, db.ForeignKey('user.id'))
    user = relationship('User')


