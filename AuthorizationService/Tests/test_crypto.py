from SRP_module import SRP

srp = SRP()

original = "Hello word!"

encode_str = srp.encrypt_by_key(original, str(108969))
decode_str = srp.decrypt_by_key(encode_str, str(108969))


print(original)
print(encode_str)
print(decode_str)

assert original == decode_str