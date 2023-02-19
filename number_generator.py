import os
import random
num = int(input("how many random numbers you need : "))
negative_numbers = input("with negative numbers ? [y/n]: ")

if negative_numbers is 'y':
    numbers = random.sample(range(-10*num, 10 * num), num)
if negative_numbers is 'n':
    numbers = random.sample(range(10 * num), num)

[print(i, end=' ') for i in numbers]
# os.system("make fclean && make && ./push_swap " + ' '.join(str(x)
#           for x in numbers) )
