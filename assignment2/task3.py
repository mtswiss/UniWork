#! /usr/local/bin/python
from common import table
from common import Stack
import sys
task2=table(sys.argv[1])
mx=task2.construct()
 
for line in open(sys.argv[2],'rU'):
	trig=0
	stk=Stack()
	stk.push('S $')
#	print '***',stk.prt()
#	line=line[:-1]
	line=line[:-1]+'$'
#	line+='$'
	print '++',line
	index=0
	a=line[index]
	while not stk.is_empty():
		print '--',stk.prt()
		#		print '||',a
		X=stk.top()
		if X.isupper():
#			print 'run 1','|',X,'|',a,'|',mx.get(X,a)
			if mx.get(X,a)!=-1 and mx.get(X,a)!=None:
				print mx.get(X,a)
				stk.pop()
				stk.push(mx.get(X,a)[0])
			else:
				print 'reject 1'
				trig=1
				break
		else:
#			print 'run 2','|',X,'|',a
			if X==a :
				stk.pop()
				if X!='$':
		#			stk.pop()
					index+=1
					a=line[index]
			elif X=='epsilon':
				stk.pop()
			else:
				print 'reject 2',X,'|',a
				trig=1
				break
	if trig==0:
		if a!='$':
			print 'reject 3'
		
		else:
			print 'accept'

