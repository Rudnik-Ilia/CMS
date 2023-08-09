from dotenv import load_dotenv
import os

load_dotenv()

DB_HOST = os.environ.get("DB_HOST")
DB_NAME = os.environ.get("DB_NAME")
DB_USER = os.environ.get("DB_USER")
DB_PASSWORD = os.environ.get("DB_PASSWORD")
DB_PORT = os.environ.get("DB_PORT")
DB_URL = os.environ.get("DSN_DB_TEST")

APP_TOK = os.environ.get("APP_TOKEN")
PASSWORD = os.environ.get("PASSWORD")
LOGIN = os.environ.get("LOGIN")
KEY_FOR_OUTER_API=os.environ.get("KEY_FOR_OUTER_API")

SQL_REQUEST_DELETE_SEQ=os.environ.get("SQL_REQUEST_DELETE_SEQ")
SQL_REQUEST_TRUNCATE_TABLE=os.environ.get("SQL_REQUEST_TRUNCATE_TABLE")