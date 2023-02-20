import os
import random

string = None
num = None
negative_numbers = None
tests = None

os.system("make -C ../ && make clean -C ../")

while not tests or not tests.isdigit():
    tests = input("\nhow many tests you want: ")

tests = int(tests)
i = 0
while i < tests:
    print("\ntest " + str(i))
    i += 1
    while not string or not string.isdigit():
        string = input("how many generated numbers you need: ")
    if num is None: num = int(string)

    while negative_numbers != 'y' and negative_numbers != 'n':
        negative_numbers = input("\nwith negative numbers ? [y/n]: ")

    if negative_numbers == 'y':
        numbers = random.sample(range(-10*num, 10 * num), num)
    if negative_numbers == 'n':
        numbers = random.sample(range(10 * num), num)
    
    print("\nGenerated numbers are :")
    [print(i, end=' ') for i in numbers]

    test = input("\n\nDo you want to run the test ? [y/n]: ")

    if test == 'y':
        os.system("./tester " + ' '.join(str(x) for x in numbers))
