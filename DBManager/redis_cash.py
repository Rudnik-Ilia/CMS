import redis

try:
    r = redis.Redis(host='localhost', port=6379, decode_responses=True)
except:
    print(Exception)


