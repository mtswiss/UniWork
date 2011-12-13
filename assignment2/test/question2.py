#! /usr/local/bin/python
from copy import deepcopy
from common import process 
from common import Matrix
import sys
input=process(sys.argv[1])
first=input.get_first()
follow=input.get_follow()
product=input.get_production()
mx=Matrix()
ERROR='Grammar is not LL(1)!'
cons=1
trig=0
for A in product:
	for rhs in product[A]:
		f_buffer=input.se_first(rhs)
		t_f_buffer=deepcopy(f_buffer)
#		print '^^^',A,'|',rhs,'|',f_buffer
		if "epsilon" in t_f_buffer:
			t_f_buffer.remove("epsilon")
		for a in t_f_buffer:
			if mx.set(A,a,product[A][rhs])==0:
				print ERROR
				cons=0
				break
		if cons==1 and 'epsilon' in f_buffer:
			b_follow=deepcopy(follow[A])
			if "epsilon" in b_follow:
				b_follow.remove("epsilon")
			for b in b_follow:
				if mx.set(A,b,product[A][rhs])==0:
					print ERROR
					cons=0
					break
			if cons==1 and ('epsilon' in follow[A]):
				if mx.set(A,'epsilon',product[A][rhs])==0:
					print ERROR 
		if cons==0:
			break
	if cons==0:
		break

if cons==1:
	output=mx.get_matrix()
	for r in xrange(len(output)-1):
		for c in xrange(len(output[0])-1):
			rule=output[r+1][c+1]
			if rule!=-1:
				print 'R[%s, %s] = %i'%(output[r+1][0],output[0][c+1],rule)

		
			
	
