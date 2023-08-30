import requests
from SRP_module import SRP

URL_MIX = "http://localhost:9090/mix"
URL_SIGNIN = "http://localhost:9090/signin"

srp = SRP()

data = {"mixture": str(srp.get_mixture())}
my_mix = str(srp.get_mixture())

response = requests.post(URL_MIX, json=data)

if response.status_code == 200:
    srp.set_key_for_encode(int(response.text))
    print(f"mix:{str(srp.get_mixture())} key :{srp.get_key()}")

    user = {
        "mixture": f"{my_mix}",
        # "role": f"{srp.encrypt_by_key('admin', srp.get_key())}",
        "login": f"{srp.encrypt_by_key('ilia', srp.get_key())}",
        "password": f"{srp.encrypt_by_key('12345', srp.get_key())}"
    }

    print(user)

    response = requests.post(URL_SIGNIN, json=user)
    print(response.text)
    result = response.json()
    print(result["token"])

    """
        SECOND REQUEST WITH THE SAME MIXTURE
    """

    response = requests.post(URL_SIGNIN, json=user)
    print(response.text)
    # result = response.json()
    # print(result["token"])



else:
    print(response.text)
