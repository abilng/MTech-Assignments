#!/usr/bin/python2.7
import sys
import random

if len(sys.argv) == 1 :
	n = 50
else:
	n=int(sys.argv[1])
for i in [random.randint(0,1000) for r in xrange(n)]:
	print i,


