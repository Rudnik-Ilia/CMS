root = 5
prime = 1000000007

secretA = 6767


secretB = 157568

mixA = (2 ** secretA) % prime
mixB = (2 ** secretB) % prime

print(mixA)
print(mixB)

print((mixA ** secretB) % prime)
print((mixB ** secretA) % prime)



