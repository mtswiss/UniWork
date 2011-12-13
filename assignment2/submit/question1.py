#! /usr/local/bin/python
from common import process
import sys
task1=process(sys.argv[1])
print 'First:'
task1.dic_print(task1.get_first())
print 'Follow:'
#task1.dic_print(task1.get_follow())
