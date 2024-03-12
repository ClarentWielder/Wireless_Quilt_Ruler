from flask import Flask, render_template
import os
import random

def create_app(test_config=None):
    app = Flask(__name__, instance_relative_config=True)
    try:
        os.makedirs(app.instance_path)
    except OSError:
        pass

    @app.route("/hello")
    def hello_world():
        return "<p>Hello, World2!</p>"
    
    @app.route("/")
    def homepage():
        return render_template('home.html')

    @app.route("/measurement/width", methods=['GET'])
    def get_width():
        width = random.randint(36,72)
        return str(width)

    @app.route("/measurement/height")
    def get_height():
        height = random.randint(48,120)
        return str(height)

    return app
