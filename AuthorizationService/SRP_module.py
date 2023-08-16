import random

ROOT = 3
PRIME = 166771

MIN_VAL = 100
MAX_VAL = 999


class SRP:
    def __init__(self):
        self._secret = random.randint(MIN_VAL, MAX_VAL)
        # self._secret = 3840
    def get_mixture(self):
        return (ROOT ** self._secret) % PRIME

    def get_key_for_encode(self, mix):
        return (mix ** self._secret) % PRIME

    def get_secret(self):
        return self._secret

