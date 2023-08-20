import json
import datetime
import jwt
from config import JWT_SALT, ERRORS




def get_jwt_token(payload):
    token = jwt.encode(payload, JWT_SALT, algorithm="HS256")
    return token


def check_jwt_token(token):
    try:
        jwt.decode(token, JWT_SALT, algorithms=["HS256"])
        print("TOKEN IS FINE")
        return ERRORS.VALID
    except jwt.DecodeError:
        print("INVALID TOKEN")
        return ERRORS.NOTVALID
    except jwt.exceptions.ExpiredSignatureError:
        print("JWT has expired")
        return ERRORS.EXPIRED


payload = {
    "login": "login",
    "password": "password",
    "exp": datetime.datetime.utcnow() + datetime.timedelta(minutes=10)
}

print(get_jwt_token(payload))