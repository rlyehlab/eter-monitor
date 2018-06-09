from wtforms import Form, StringField, SubmitField
from wtforms.validators import Required



class Register(Form):
    broker = StringField('Ip Broker', validators=[Required()])
    geoloc = StringField('Geoloc', validators=[Required()])
    port = StringField('Port', validators=[Required()])
    submit = SubmitField('Submit')
