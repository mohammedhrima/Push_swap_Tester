import os
import random
num = None
negative_numbers = None

while not num or not num.isdigit():
    num = input("how many random numbers you need : ")
num = int(num)


while negative_numbers != 'y' and negative_numbers != 'n':
    negative_numbers = input("with negative numbers ? [y/n]: ")

if negative_numbers == 'y':
    numbers = random.sample(range(-10*num, 10 * num), num)
if negative_numbers == 'n':
    numbers = random.sample(range(10 * num), num)

[print(i, end=' ') for i in numbers]
print("\n")
# os.system("make fclean && make && ./push_swap " + ' '.join(str(x)
#           for x in numbers) )
