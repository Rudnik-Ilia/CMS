from flask import Flask, request, make_response, jsonify, session, abort, g

app = Flask(__name__)
# app.config['SQLALCHEMY_DATABASE_URI'] = DB_URL
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
app.config['SECRET_KEY'] = '1234'


@app.route("/", methods=["POST"])
def start():
    if request.method == "POST":
        return (make_response(jsonify("Im Authorization Service!"), 200))


@app.route("/gettoken", methods=["POST"])
def get_token():
    if request.method == "POST":
        return make_response(jsonify("Im Authorization Service!"), 200)


if __name__ == '__main__':
    app.run(host="0.0.0.0", port=8090, debug=True)
