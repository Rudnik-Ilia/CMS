from flask import Flask, request, redirect, make_response, jsonify, session
from flask_sqlalchemy import SQLAlchemy
from flask_migrate import Migrate
from config import DB_URL

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = DB_URL
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
app.config['SECRET_KEY'] = '1234'

db = SQLAlchemy(app)
migrate = Migrate(app, db)


