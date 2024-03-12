from flask import Flask, render_template, request
import os
import random
import QuiltFunctions as Quilt

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
        user_agent = request.headers.get('User-Agent').lower()
        if ("iphone" in user_agent) or ("android" in user_agent):
            return render_template('mobile.index.html')
        else:
            return render_template('desktop.index.html')

    @app.route("/measurement/width", methods=['GET'])
    def get_width():
        width = Quilt.get_width_measurement()
        return str(width)

    @app.route("/measurement/height")
    def get_height():
        height = Quilt.get_height_measurement()
        return str(height)

    return app
