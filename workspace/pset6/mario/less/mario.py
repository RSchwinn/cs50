import sys
from cs50 import get_int

if len(sys.argv) != 1:
    sys.exit("Usage: python mario1.py")

height = get_int("Height: ")

if height < 1:
    height = get_int("Height: ")

if height > 8:
    height = get_int("Height: ")

for i in range(height):
    spaces = height - i
    for j in range(spaces - 1):
        print(" ", end='')
        j = j + 1
    for k in range(height - spaces + 1):
        print("#", end='')
        k = k + 1
    print("")
    i = i + 1