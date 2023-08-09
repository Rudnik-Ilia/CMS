import freecurrencyapi

from redis_cash import r

from config import KEY_FOR_OUTER_API
def request_for_currency():
    try:
        client = freecurrencyapi.Client(KEY_FOR_OUTER_API)
        rate_from_db = str(round(client.latest(currencies=['ILS'])["data"]['ILS'], 2))
        r.set("rate", rate_from_db, 86400)
        r.close()
        return rate_from_db
    except:
        return "Redirect is failed!"


def perfom_convert():
    try:
        request_for_currency()
    except:
        return "Redirect is failed!"