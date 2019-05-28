import os
import random

counter = 0
while counter < 10:
    os.system("python3 generator.py Coimbra " + str(random.randint(0,10) ))
    counter+= 1