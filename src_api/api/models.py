from flask_sqlalchemy import SQLAlchemy
from sqlalchemy.dialects.postgresql import JSON
from sqlalchemy import  Column, Integer, JSON, DateTime



db = SQLAlchemy()


class Base(db.Model):

    __abstract__ = True

    id = db.Column(db.Integer, primary_key=True)
    date_created  = db.Column(db.DateTime,  default=db.func.current_timestamp())



class Measure(Base):

    med_sensor = db.Column(JSON)




class User(Base):

    name =  ""
    email = ""




class Device(Base):

    zone  = ""





