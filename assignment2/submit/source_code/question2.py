#! /usr/local/bin/python
from common import table
import sys
task2=table(sys.argv[1])
mx=task2.construct()
if mx is not None:
	task2.table_print(mx)
else:
	print 'Grammar is not LL(1)!'

	
