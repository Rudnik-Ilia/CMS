import random

ROOT = 3
PRIME = 166771

MIN_VAL = 100
MAX_VAL = 999


class SRP:
    def __init__(self):
        self._secret = random.randint(MIN_VAL, MAX_VAL)
        self._m_key = 0

    def get_mixture(self):
        return (ROOT ** self._secret) % PRIME

    def set_key_for_encode(self, mix):
        self._m_key = str((mix ** self._secret) % PRIME)

    def get_secret(self):
        return self._secret

    def get_key(self):
        if self._m_key != 0:
            return self._m_key
        return "The key has not been set!"

    def encrypt_by_key(self, plaintext: str, key: str):
        encrypt_string = bytearray(plaintext, 'ascii')
        key = bytearray(key, 'ascii')

        for i in range(len(encrypt_string)):
            encrypt_string[i] ^= key[i % len(key)]

        return encrypt_string.decode('utf-8')

    def decrypt_by_key(self, encrypt_text: str, key: str):
        return self.encrypt_by_key(encrypt_text, key)
