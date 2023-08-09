from config import PASSWORD, LOGIN


def check_hash(login: str, password: int):
    return login == LOGIN and password == PASSWORD
