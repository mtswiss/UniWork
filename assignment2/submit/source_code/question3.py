#! /usr/local/bin/python
import sys
from common import Parser
pre_parser=Parser(sys.argv[1])
if pre_parser.is_LL():
	for line in open(sys.argv[2],'rU'):
		input=line[:-1]+'$'
		print pre_parser.parsing(input)
else:
	print 'Grammar is not LL(1)!'
