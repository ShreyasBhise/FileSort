import random
import string
import sys

def generateTestInput(mode, fn):
	n = int(mode)
	fname=fn
#	print(n)
	with open(fname, "w") as f:
		for i in range (1, 100000):
			if i % 50 == 0:
				f.write('\n')
			p = random.random();
			if p < 0.05:
				f.write(",")
			elif n == 0:
				randLetter = random.choice(string.ascii_lowercase)
				f.write('%c'%randLetter)
			elif n == 1:
				sign = int(random.random() + 0.5)
				randDigit = int(random.uniform(0, sys.maxint) +0.5)
				if sign == 0:
					randDigit *= -1
				f.write('%d,'%randDigit)
				
		f.write('\n')
