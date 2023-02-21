import os
import random
import signal

string = None
num = None
negative_numbers = None
tests = None

def handler(signum, frame):
    os.system("make fclean -C ../ && rm -rf tester")
    exit(0)

os.system("make -C ../ && make clean -C ../")

signal.signal(signal.SIGINT, handler)
while not tests or not tests.isdigit():
    tests = input("\nhow many tests you want: ")

tests = int(tests) # number of tests

while not string or not string.isdigit():
    string = input("how many generated numbers you need: ")

num = int(string) # test of 100 or 500 for example

while negative_numbers != 'y' and negative_numbers != 'n':
    negative_numbers = input("with negative numbers ? [y/n]: ")

i = 0
while i < tests:
    print("\ntest " + str(i + 1))
    i += 1
    if negative_numbers == 'y':
        numbers = random.sample(range(-10*num, 10 * num), num)
    if negative_numbers == 'n':
        numbers = random.sample(range(10 * num), num)
    
    print("Generated numbers are :")
    [print(i, end=' ') for i in numbers]

    test = input("\n\nPress Enter to start the test...")
    if test == "":
        os.system("./tester " + ' '.join(str(x) for x in numbers))
