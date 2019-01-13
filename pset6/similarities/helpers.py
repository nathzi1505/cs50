from enum import Enum


class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())


Op = 0
s1 = ""
s2 = ""


def cost_t(i, j):
    """To find the cost of transformation"""
    if i == 0:
        return j  # Base Case
    elif j == 0:
        return i  # Base Case
    valueD = cost_t(i - 1, j) + 1
    valueI = cost_t(i, j - 1) + 1
    valueS = cost_t(i - 1, j - 1)
    if s1[i - 1] == s2[j - 1]:
        valueS += 0
    else:
        valueS += 1
    value = min(valueD, valueI, valueS)  # Finds the minimum value
    global Op  # Makes the global variable accessible
    if value == valueD:
        Op = Operation.DELETED
    elif value == valueI:
        Op = Operation.INSERTED
    elif value == valueS:
        Op = Operation.SUBSTITUTED
    return value


def distances(a, b):
    """Calculate edit distance from a to b"""
    global s1  # Makes the global variable accessible
    s1 = a
    global s2  # Makes the global variable accessible
    s2 = b
    matrix = [[0 for x in range(len(b) + 1)] for y in range(len(a) + 1)]  # List comprehension
    matrix[0][0] = (0, None)
    for i in range(1, len(a) + 1):
        matrix[i][0] = (i, None)
    for j in range(1, len(b) + 1):
        matrix[0][j] = (j, None)
    for i in range(1, len(a) + 1):
        for j in range(1, len(b) + 1):
            matrix[i][j] = (cost_t(i, j), Op)  # Inserts into the matrix the necessary values
    return matrix