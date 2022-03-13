#!/usr/bin/env python3

import sys
import string
import random

def generate_pair():
    key_len = 32
    hex_sis_letters = 'abcdef'
    key = "".join([random.choice(hex_sis_letters + string.digits) for _ in range(key_len)])


    string_len = random.randint(0,1)
    value = "".join([random.choice(string.ascii_letters + string.digits) for _ in range(string_len)])

    return(key, value)

def main():
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <test dir> <counting of tests>")
        sys.exit(1)
    test_dir = sys.argv[1]
    count_of_tests = int(sys.argv[2])

    for num in range(1, count_of_tests+1):
        test_name = f"{test_dir}/{num:02d}"
        with open(f"{test_name}.t", 'w') as raw_fd, \
             open(f"{test_name}.a", 'w') as ans_fd:
            data = list()
            line_count = random.randint(0,1000)
            for _ in range(line_count):
                data.append(generate_pair())
                key, value = data[-1]
                raw_fd.write(f"{key}\t{value}\n")

            result = sorted(data, key=lambda x: x[0])
            for elem in result:
                key, value = elem
                ans_fd.write(f"{key}\t{value}\n")

main()
'''
#!/usr/bin/env python3

import sys
import string
import random

def generate_pair():
    key = random.randint(0, 10)
    string_len = random.randint(1,100)
    value = "".join([random.choice(string.ascii_letters + string.digits) for _ in range(string_len)])
    return(key, value)

def main():
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <test dir> <counting of tests>")
        sys.exit(1)
    test_dir = sys.argv[1]
    count_of_tests = int(sys.argv[2])

    for num in range(1, count_of_tests+1):
        test_name = f"{test_dir}/{num:02d}"
        with open(f"{test_name}.t", 'w') as raw_fd, \
             open(f"{test_name}.a", 'w') as ans_fd:
            data = list()
            line_count = random.randint(0,10)
            for _ in range(line_count):
                data.append(generate_pair())
                key, value = data[-1]
                raw_fd.write(f"{key} {value}\n")

            result = sorted(data, key=lambda x: x[0])
            for elem in result:
                key, value = elem
                ans_fd.write(f"{key} {value}\n")


main()
'''