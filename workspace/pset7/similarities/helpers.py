from nltk.tokenize import sent_tokenize


def lines(a, b):
    # """Return lines in both a and b"""

    # Split each string into lines
    a = str.rsplit(a, "\n")
    b = str.rsplit(b, "\n")

    # Add lines that appear in both to the list
    inboth = []

    for x in a:
        for y in b:
            if x == y and not x in inboth:
                inboth.append(x)

    return inboth


def sentences(a, b):
    #"""Return sentences in both a and b"""

    # Split each string into lines
    a = sent_tokenize(a)
    b = sent_tokenize(b)

    # Add lines that appear in both to the list
    inboth = []

    for x in a:
        for y in b:
            if x == y and not x in inboth:
                inboth.append(x)

    return inboth


def substrings(a, b, n):
    #"""Return substrings of length n in both a and b"""

    # Split each string into substrings
    def returnss(x, n):
        # result = [x[i: j] for i in range(len(x)) for j in [i + n] ]
        result = []
        for i in range(0, len(x)-n+1):
            result.append(x[i:(i+n)])
        return result

    a = returnss(a, n)
    b = returnss(b, n)

    # Add lines that appear in both to the list
    inboth = []

    for x in a:
        for y in b:
            if x == y:
                if x not in inboth:
                    inboth.append(x)

    return inboth