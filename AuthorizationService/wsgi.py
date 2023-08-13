import flask
from flask import Flask, request, make_response, jsonify, session, abort, g
from flask_pymongo import PyMongo
from config import URL_DBS, ERRORS
import json
from JWT import check_jwt_token, get_jwt_token
import datetime

app = Flask(__name__)
app.config['MONGO_URI'] = URL_DBS
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
app.config['SECRET_KEY'] = '1234'

mongo = PyMongo(app)

db = mongo.db


@app.before_request
def restrict_access():
    allowed_ips = ['127.0.0.1']
    remote_ip = request.remote_addr
    if remote_ip not in allowed_ips:
        abort(403)


@app.route("/mongo", methods=["POST"])
def mongo():
    if request.method == "POST":
        items = db.users.find()
        print(items)
        return flask.jsonify([i for i in items])


@app.route("/", methods=["POST"])
def start():
    if request.method == "POST":
        return make_response(jsonify("Im Authorization Service!"), 200)


@app.route("/gettoken", methods=["POST"])
def get_token():
    if request.method == "POST":
        return make_response(jsonify("Im Authorization Service!"), 200)


@app.route("/check", methods=["POST"])
def check_token():
    if request.method == "POST":
        token = request.headers.get("authorization")
        if check_jwt_token(token) is ERRORS.VALID:
            return make_response(jsonify("You got it!!!"), 200)
        else:
            return make_response(jsonify("NOT"))


@app.route("/signin", methods=["POST"])
def _signin():
    if request.method == "POST":
        result = request.json

        payload = {
            "login": result["login"],
            "password": result["password"],
            "exp": datetime.datetime.utcnow() + datetime.timedelta(minutes=10)
        }

        return make_response(jsonify({"token": get_jwt_token(payload)}), 200)


if __name__ == '__main__':
    app.run(host="0.0.0.0", port=8090, debug=True)
