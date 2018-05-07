from flask_sqlalchemy import SQLAlchemy

db = SQLAlchemy()

class measure_sensor(db.Model):

    id = db.Column(db.Integer)

