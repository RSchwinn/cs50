from cs50 import get_string
import sys

if len(sys.argv) != 2:
    print("Usage: python caeser.py n")
    exit(1)

n = int(sys.argv[1]) % 26

plaintext = get_string("plaintext: ")

print("ciphertext: ", end="")

for c in plaintext:
    if c.isalpha():
        if c.isupper():
            c = chr((ord(c) - 65 + n) % 26 + 65)
        elif c.islower():
            c = chr((ord(c) - 97 + n) % 26 + 97)
    print(c, end="")

print("")