from cs50 import get_string
import sys

if len(sys.argv) != 2:
    print("Usage: python bleep.py dictionary")
    exit(1)

dictionary = sys.argv[1]

banned = set()

file = open(dictionary, "r")
for line in file:
    banned.add(line.rstrip("\n"))

rawmessage = get_string("What message would you like to censor?\n")
message = rawmessage.split(" ")

censoredmessage = ""
for word in message:
    if word.lower() in banned:
        censoredmessage += ("*" * len(word)) + " "
    else:
        censoredmessage += word + " "

print(censoredmessage)

