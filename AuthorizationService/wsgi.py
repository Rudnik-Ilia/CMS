import flask
from flask import Flask, request, make_response, jsonify, session, abort, g
from pymongo import MongoClient
from config import URL_DBS, ERRORS
import json
from JWT import check_jwt_token, get_jwt_token
import datetime

app = Flask(__name__)
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
app.config['SECRET_KEY'] = '1234'

cluster = MongoClient(URL_DBS)

db = cluster["CMS"]
collection = db["users"]


#################################################
def get_password(name: str):
    item = collection.find_one({"name": name}, {"_id": 0})
    if item is None:
        return None
    return str(item["password"])


##################################################

@app.before_request
def restrict_access():
    allowed_ips = ['127.0.0.1']
    remote_ip = request.remote_addr
    if remote_ip not in allowed_ips:
        abort(403)


##################################################


@app.route("/", methods=["POST"])
def check_response():
    if request.method == "POST":
        # return make_response(jsonify("Im Authorization Service!"), 200)
        return {"k": "d"}


@app.route("/check", methods=["POST"])
def check_token():
    if request.method == "POST":
        token = json.loads(request.data.decode('utf-8'))
        print(token["token"])
        # token = request.headers.get("authorization")
        if check_jwt_token(token["token"]) is ERRORS.VALID:
            return make_response(jsonify("You got it from DB Manager!!!"), 200)
        else:
            return make_response(jsonify("FORBIDDEN ACCESS"), 405)


@app.route("/signin", methods=["POST"])
def _signin_and_gettoken():
    if request.method == "POST":
        try:
            result = request.json
            password = get_password(result["login"])
            if password is None:
                return make_response(jsonify("This user doest exist"), 406)
            if password == result["password"]:
                payload = {
                    "login": result["login"],
                    "password": result["password"],
                    "exp": datetime.datetime.utcnow() + datetime.timedelta(minutes=10)
                }
            else:
                return make_response(jsonify("This password is wrong!"), 405)
        except KeyError as e:
            return jsonify({"error": "KeyError", "message": str(e)}), 400
        return make_response(jsonify({"token": get_jwt_token(payload)}), 200)


if __name__ == '__main__':
    app.run(host="0.0.0.0", port=8090, debug=True)
