from flask import Blueprint, render_template
from api.background import create_client_mqtt
from api.forms import Register

client = Blueprint('client', __name__)


@client.route('/register')
def register():
    form = Register()
    if form.validate_on_submit():
        broker = form.broker.data
        geoloc = form.geoloc.data
        port = form.port.data
    broker_config = {
            'topic':geoloc,
            'broker':broker,
            'port':port}
    print(broker_config)
    task_client = create_client_mqtt.delay(broker_config)
    return render_template('register.html', form=form)






