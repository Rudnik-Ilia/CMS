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


# s1 = SRP()
# s2 = SRP()
#
# s1_mix = s1.get_mixture()
# s1_secret = s1.get_secret()
#
# s2_mix = s2.get_mixture()
# s2_secret = s2.get_secret()
#
# print(f" s1 secret {s1_secret}")
# print(f" s1 mix {s1_mix}")
#
# print(s2_secret)
# print(s2_mix)
#
#
# print(s1.get_key_for_encode(s2_mix))
# print(s2.get_key_for_encode(s1_mix))

# print(s1.get_key_for_encode(155750))
# print(s2.get_key_for_encode(33262))

