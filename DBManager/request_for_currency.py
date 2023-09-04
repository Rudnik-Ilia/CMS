import freecurrencyapi
from redis_cash import connection_redis
from config import KEY_FOR_OUTER_API


def request_for_currency():
    try:
        client = freecurrencyapi.Client(KEY_FOR_OUTER_API)
        rate_from_db = str(round(client.latest(currencies=['ILS'])["data"]['ILS'], 2))
        # rate_from_db = str(3.17)
        conn = connection_redis()
        conn.set("rate", rate_from_db, 86400)
        conn.close()

        return rate_from_db
    except Exception as e:
        print(e)
        return "Redirect is failed!"


def perfom_convert():
    try:
        request_for_currency()
    except:
        return "Redirect is failed!"




perfom_convert()