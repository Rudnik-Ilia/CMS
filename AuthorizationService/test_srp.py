from DH import SRP

s1 = SRP()

print(f"secret : {s1.get_secret()}")
print(f"mix : {s1.get_mixture()}")

res = int(input())
print(s1.get_key_for_encode(res))
