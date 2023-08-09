from flask import request, make_response, jsonify, session, abort, g
import json
from db import db, app
from models import Employees
from request_for_currency import request_for_currency
from hash_check import check_hash
from config import APP_TOK, SQL_REQUEST_DELETE_SEQ, SQL_REQUEST_TRUNCATE_TABLE
from rabbit import rabbit_connect_add
from redis_cash import r


class CustomEncoder(json.JSONEncoder):
    def default(self, obj):
        if isinstance(obj, Employees):
            return {"worker": {"id:": obj.id, "name": obj.name, "surname": obj.surname, "salary": obj.salary}}


@app.route('/items/login', methods=['POST'])
def login(g):
    if request.method == "POST":
        if check_hash(request.json['login'], request.json['password']):
            session["token"] = APP_TOK
            res = make_response(jsonify(message="LOGIN is OK"), 200)
            return res
        else:
            return make_response("WRONG LOGIN OR PASSWORD", 505)


@app.route('/items/all', methods=['GET'])
def get_all_records():
    if request.method == "GET":
        users = Employees.query.all()
        if len(users) == 0:
            Employees.sql_query(SQL_REQUEST_DELETE_SEQ)
            return make_response(jsonify(message="Empty"), 201)
        list_of_users = list()
        for i in users:
            list_of_users.append({"worker": {"id:": i.id, "name": i.name, "surname": i.surname, "salary": i.salary}})
        return make_response(jsonify(list_of_users), 200)
    else:
        abort(401)


@app.route('/items', methods=['GET'])
def get_():
    if request.method == "GET":
        return make_response(jsonify("Everythink works"), 200)


@app.route('/items/<int:id>', methods=['GET'])
def get_item(id: int):
    if request.method == "GET":
        user = Employees.query.get_or_404(id)
    return jsonify({"name": user.name, "surname": user.surname, "salary": user.salary})


@app.route('/items/create', methods=['POST'])
def create():
    if request.method == "POST":
        result = request.json
        item = Employees(name=(result["name"]).capitalize(), surname=result["surname"].capitalize(),
                         salary=result["salary"])
        try:
            item.save()
            rabbit_connect_add(f"We have a new guy called {item.name} in our team!")
            return make_response(jsonify("Done"), 200)
        except:
            db.session.rollback()
            return make_response(jsonify("Error"), 500)


@app.route('/items/delete/<int:id>', methods=['DELETE'])
def remove_by_id(id: int):
    if request.method == "DELETE":
        item = Employees.query.get_or_404(id)
        try:
            item.delete()
            rabbit_connect_add(f"{item.name}, you are fired! Get back the laptop!")
            return make_response(jsonify("Done"), 200)
        except:
            db.session.rollback()
            return make_response(jsonify("Error"), 500)


@app.route('/items/delete/all', methods=['DELETE'])
def remove_all():
    if request.method == "DELETE":
        users_from_table = Employees.query.all()
        if len(users_from_table) == 0:
            return make_response(jsonify("Empty table"), 202)
        try:
            Employees.sql_query(SQL_REQUEST_TRUNCATE_TABLE)
            return make_response(jsonify("Done"), 200)
        except:
            db.session.rollback()
            return make_response(jsonify("Error"), 500)


@app.route('/items/get_salary/<int:id>', methods=['GET'])
def get_salary_id(id: int):
    reply = " "
    if request.method == "GET":
        item = Employees.query.get_or_404(id)
        try:
            reply = request_for_currency()
            return make_response(jsonify({"Salary is": f"{round((float(item.salary) / float(reply)), 2)} $"}), 200)
        except:
            return make_response(jsonify({"Error": reply}, 300))


@app.route('/items/get_salary/<string:name>', methods=['GET'])
def get_salary_name(name: str):
    reply = " "
    if request.method == "GET":
        item = Employees.query.filter_by(name=name.capitalize()).first_or_404()
        try:
            reply = r.get("rate")
            r.close()
            if reply is None:
                reply = request_for_currency()
                print("DB")
                return make_response(jsonify({"Salary is": f"{round((float(item.salary) / float(reply)), 2)} $"}), 200)
            else:
                print("REDIS")
                return make_response(jsonify({"Salary is": f"{round((float(item.salary) / float(reply)), 2)} $"}), 200)
        except:
            return make_response(jsonify({"Error": reply}, 300))


@app.route('/items/update_name/<int:id>', methods=['PATCH'])
def remove_by_name(id: int):
    if request.method == "PATCH":
        user = Employees.query.get_or_404(id)
        req = request.json
        user.salary = req["salary"]
        try:
            db.session.commit()
            return make_response(jsonify("Done"), 200)
        except:
            db.session.rollback()
            return make_response(jsonify("Error"), 500)


@app.errorhandler(404)
def error_404(error):
    return make_response("Something wrong!Don't worry and try again!)", 404)


@app.errorhandler(401)
def error_401(error):
    return make_response("You don't have permission!)", 404)


@app.teardown_request
def after_request(g):
    ...


@app.teardown_appcontext
def after_appcontext(g):
    db.session.close()


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8000, debug=True)
