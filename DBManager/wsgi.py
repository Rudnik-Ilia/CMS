from flask import request, make_response, jsonify, session, abort, g
import json
from db import db, app
from models import Employees
from request_for_currency import request_for_currency
from config import APP_TOK, SQL_REQUEST_DELETE_SEQ, SQL_REQUEST_TRUNCATE_TABLE
from rabbit import rabbit_connect_add
from redis_cash import connection_redis
import subprocess


@app.route('/dbmanager', methods=['GET'])
def get_check():
    if request.method == "GET":
        return make_response(jsonify("Im DB manager!"), 200)


@app.route('/dbmanager/run_migrations', methods=['POST'])
def run_migrations():
    if request.method == 'POST':
        try:
            init_command = "flask db init"
            migrate_command = "flask db migrate -m 'Create Employees table'"
            upgrade_command = "flask db upgrade"

            subprocess.run(init_command, shell=True)
            subprocess.run(migrate_command, shell=True)
            subprocess.run(upgrade_command, shell=True)

            return jsonify(message="Migrations executed successfully"), 200
        except Exception as e:
            return jsonify(message="Error: " + str(e)), 500
    else:
        return jsonify(message="Method is not allowed"), 405


#####################################################################################

@app.route('/dbmanager/employees', methods=['GET'])
def get_all_records():
    if request.method == "GET":
        employees = Employees.query.all()
        if len(employees) == 0:
            return make_response(jsonify(message="Empty"), 201)
        list_of_employees = list()
        for i in employees:
            list_of_employees.append(
                {"worker": {"id:": i.id, "name": i.name, "surname": i.surname, "salary": i.salary}})
        return make_response(jsonify(list_of_employees), 200)
    else:
        return jsonify(message="Method is not allowed"), 405


@app.route('/dbmanager/employees/<string:name>', methods=['GET'])
def get_item(name: str):
    if request.method == "GET":
        user = Employees.query.filter_by(name=name.capitalize()).first_or_404()
    return jsonify({"name": user.name, "surname": user.surname, "salary": user.salary})


@app.route('/dbmanager/employees', methods=['POST'])
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


@app.route('/dbmanager/employees/<string:name>', methods=['DELETE'])
def remove_by_id(name: str):
    if request.method == "DELETE":
        item = Employees.query.filter_by(name=name.capitalize()).first_or_404()
        try:
            item.delete()
            rabbit_connect_add(f"{item.name}, you are fired! Get back the laptop!")
            return make_response(jsonify("Done"), 200)
        except:
            db.session.rollback()
            return make_response(jsonify("Error"), 500)


@app.route('/dbmanager/employees', methods=['DELETE'])
def remove_all():
    if request.method == "DELETE":
        users_from_table = Employees.query.all()
        if len(users_from_table) == 0:
            return make_response(jsonify("Empty table"), 202)
        try:
            Employees.sql_query(SQL_REQUEST_TRUNCATE_TABLE)
            Employees.sql_query(SQL_REQUEST_DELETE_SEQ)
            return make_response(jsonify("Done"), 200)
        except:
            db.session.rollback()
            return make_response(jsonify("Error"), 500)


@app.route('/dbmanager/employees/salary/<string:name>', methods=['GET'])
def get_salary_name(name: str):
    print("Enter method")
    reply = None
    if request.method == "GET":
        item = Employees.query.filter_by(name=name.capitalize()).first_or_404()
        try:
            reply = connection_redis().get("rate")
            connection_redis().close()
            if reply is None:
                reply = request_for_currency()
                return make_response(jsonify({"Salary is (DB)": f"{round((float(item.salary) / float(reply)), 2)} $"}), 200)
            else:
                return make_response(jsonify({"Salary is (CASH)": f"{round((float(item.salary) / float(reply)), 2)} $"}), 200)
        except:
            return make_response(jsonify({"Error": reply}, 300))


@app.route('/dbmanager/employees/<int:id>/<int:salary>', methods=['PUT'])
def remove_by_name(id: int, salary: int):
    if request.method == "PUT":
        user = Employees.query.get_or_404(id)
        user.salary = salary
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
