import dotenv
import os
from enum import Enum

dotenv.load_dotenv()

URL_DBS = os.environ.get("URL_DB")
JWT_SALT = os.environ.get("JWT_SALT")


class ERRORS(Enum):
    VALID = 0
    NOTVALID = 1
    EXPIRED = 2
