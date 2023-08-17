import requests
from SRP_module import SRP

URL_MIX = "http://localhost:9090/mix"
URL_SIGNIN = "http://localhost:9090/signin"

srp = SRP()

data = {"mixture": str(srp.get_mixture())}


response = requests.post(URL_MIX, json=data)
srp.set_key_for_encode(int(response.text))
print(f"key :{srp.get_key()}")

user = {
    "role": f"{srp.encrypt_by_key('admin', srp.get_key())}",
    "login": f"{srp.encrypt_by_key('ilia', srp.get_key())}",
    "password": f"{srp.encrypt_by_key('12345', srp.get_key())}"
}

print(user)


# response = requests.post(URL_MIX, json=user)
