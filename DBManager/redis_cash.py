import redis


def connection_redis():
    try:
        redis_conn = redis.Redis(host='redis', port=6379, decode_responses=True)
        return redis_conn
    except:
        print(Exception)
        return ...


