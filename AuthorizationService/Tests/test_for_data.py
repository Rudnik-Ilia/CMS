import requests
from SRP_module import SRP


URL_SIGNIN = "http://localhost:9090/signin"
user = {
    "mixture": "88888",
    "role": "admin",
    "login": "ilia",
    "password": "12345"
}

response = requests.post(URL_SIGNIN, json=user)

print(response.text)