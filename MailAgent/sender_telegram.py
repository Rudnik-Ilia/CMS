import requests
from config import TOKEN, CHAT_ID


def send_to_telegram(message: str):
    url = f"https://api.telegram.org/bot{TOKEN}/sendMessage?chat_id={CHAT_ID}&text={message}"
    requests.get(url)
