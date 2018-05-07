#!/usr/bin/env python3
from flask import Flask
from api.views import blueprints



app = Flask(__name__)

for bp in blueprints:
    app.register_blueprint(bp)


#if __name__ == '__main__':
#    app.run(debug=True)
