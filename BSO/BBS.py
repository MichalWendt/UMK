import sympy
import random
import sys

N = 21
p = 3319
q = 839

is_prime(p)
is_prime(q)

mod(p,4)
mod(q,4)

n = p * q

s = 7919

gcd(s,n)
gcd(s,q)
gcd(s,p)

x = s*s % n

bit_output = ""

for _ in range(N):
    x = x*x % n
    b = x % 2
    bit_output += str(b)

print(bit_output)
