# Cracks passwords

import sys
import crypt


def main():
    if not len(sys.argv) == 2:
        print("Usage: python crack.py hash")
        sys.exit(1)
    salt = [sys.argv[1][0], sys.argv[1][1]]
    repo = []
    pwd = []
    hash = []
    # Creating an array of characters
    for i in range(26):
        repo.append(chr(i + 65))
    for i in range(26):
        repo.append(chr(i + 97))
    flag = 0  # To flag the matching of hash given and made up password

    # Various permutations to crack the passwords
    for i in range(52):
        pwd[0] = repo[i]
        dup = pwd
        dup = "".join(dup)
        hash = crypt.crypt(dup, salt)
        if hash == sys.argv[1]:
            flag = 1  # Indicates successful matching
            print(pwd)
            sys.exit(0)

    # Various permutations to crack the passwords
    for j in range(52):
        pwd[0] = repo[j]
        for i in range(52):
            pwd[1] = repo[i]
            dup = pwd
            dup = "".join(dup)
            hash = crypt.crypt(dup, salt)
            if hash == sys.argv[1]:
                flag = 1  # Indicates successful matching
                print(pwd)
                sys.exit(0)

    # Various permutations to crack the passwords
    for k in range(52):
        pwd[0] = repo[j]
        for j in range(52):
            pwd[1] = repo[j]
            for i in range(52):
                pwd[2] = repo[i]
                dup = pwd
                dup = "".join(dup)
                hash = crypt.crypt(dup, salt)
                if hash == sys.argv[1]:
                    flag = 1  # Indicates successful matching
                    print(pwd)
                    sys.exit(0)

    # Various permutations to crack the passwords
    for l in range(52):
        pwd[0] = repo[l]
        for k in range(52):
            pwd[1] = repo[j]
            for j in range(52):
                pwd[2] = repo[j]
                for i in range(52):
                    pwd[3] = repo[i]
                    dup = pwd
                    dup = "".join(dup)
                    hash = crypt.crypt(dup, salt)
                    if hash == sys.argv[1]:
                        flag = 1  # Indicates successful matching
                        print(pwd)
                        sys.exit(0)

    # Various permutations to crack the passwords
    for m in range(52):
        pwd[0] = repo[m]
        for l in range(52):
            pwd[1] = repo[l]
            for k in range(52):
                pwd[2] = repo[j]
                for j in range(52):
                    pwd[3] = repo[j]
                    for i in range(52):
                        pwd[4] = repo[i]
                        dup = pwd
                        dup = "".join(dup)
                        hash = crypt.crypt(dup, salt)
                        if hash == sys.argv[1]:
                            flag = 1  # Indicates successful matching
                            print(pwd)
                            sys.exit(0)


if __name__ == "__main__":
    main()