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


def get_password_from_db(name: str):
    item = collection.find_one({"login": name}, {"_id": 0})
    if item is None:
        return None
    return item


def create_expiration_time(period: int = 5):
    expiration_time = datetime.datetime.utcnow() + datetime.timedelta(minutes=period)
    return int(expiration_time.timestamp())

##################################################

# @app.before_request
# def restrict_access():
#     allowed_ips = ['0.0.0.0', '127.0.0.1']
#     remote_ip = request.remote_addr
#     if remote_ip not in allowed_ips:
#         abort(403)

##################################################


@app.route("/authservice", methods=["GET"])
def check_response():
    if request.method == "GET":
        return make_response(jsonify("Im Authorization Service!"), 200)


@app.route("/check", methods=["POST"])
def check_token():
    if request.method == "POST":
        token = json.loads(request.data.decode('utf-8'))
        print(token["token"])
        if check_jwt_token(token["token"]) is ERRORS.VALID:
            return make_response(jsonify("You got it from DB Manager!!!"), 200)
        else:
            return make_response(jsonify("FORBIDDEN ACCESS"), 405)


@app.route("/authservice/signin", methods=["POST"])
def signin_and_gettoken():
    if request.method == "POST":
        try:
            result = request.json
            print(result)
            user_data = get_password_from_db(result["login"])
            if user_data is None:
                return make_response(jsonify("This user doest exist"), 406)
            if user_data["password"] == result["password"]:

                payload = {
                    "role": user_data["role"],
                    "exp": create_expiration_time()
                }
            else:
                return make_response(jsonify("This password is wrong!"), 405)
        except KeyError as e:
            return jsonify({"error": "KeyError", "message": str(e)}), 400
        return make_response(jsonify({"token": get_jwt_token(payload)}), 200)


@app.route("/authservice/users", methods=["POST"])
def insert_user():
    if request.method == "POST":
        data = request.json
        try:
            collection.insert_one(data)
            return make_response(jsonify("Done"), 200)
        except:
            return make_response(jsonify("Error"), 500)


@app.route("/authservice/users", methods=["GET"])
def get_all_users():
    if request.method == "GET":
        try:
            data = collection.find()
            user_list = [record for record in data]
            return make_response(jsonify(user_list), 200)
        except:
            return make_response(jsonify("Error get"), 500)


@app.route("/metrics", methods=["GET"])
def state():
    return make_response(jsonify("Im OK"), 200)


if __name__ == '__main__':
    app.run(host="0.0.0.0", port=8090, debug=True)
