#! /usr/local/bin/python
import sys
temp={}
first={}
follow={}
n_line=0
for line in open(sys.argv[1],"rU"):
	if line[0] not in temp:
		temp[line[0]]=[]
		follow[line[0]]=[]
	elif line[0] not in follow:
		follow[line[0]]=[]
	rhs=line[:-1].split("=")[1].strip()
	temp[line[0]].append(rhs)
	if n_line==0:
		follow[line[0]].append("epsilon")
		first[line[0]]=[]
	n_line=n_line+1

print 'temp',temp



print first
def cur_first(input):
	print '****',input
	print 'temp:',temp
	if not(isinstance(input,list)):
		print '[][]',input
		input=input.split(' ')
	buffer=[]
	print '+++'
	if len(input[0])==1 and input[0].islower():
		print 'termainal',input
		buffer.append(input[0])
		print 'termainal',buffer
	elif " " in input[0]:
#		for ii in input[0].split(' '):
#			if ii in temp:
#				print '&&&&',input[0].split(' ')
#				buffer.extend(cur_first(temp[ii]))
#			else:
#				buffer.append(cur_first(ii))
		buffer.extend(cur_first(input[0].split(' ')))
	elif input[0]=="epsilon":
		buffer.append("epsilon")
	else:
		print temp[input[0]],'--	--'
		buffer.extend(cur_first(temp[input[0]]))
		for i in xrange(len(input)-1):
			print 'running ',input[i+1]
			if input[i+1].islower() and len(input[i])==1:
				buffer.append(input[i+1])
			elif input[i+1]!="epsilon":
				if (input[i].islower() and len(input)==1) or ("epsilon" not in cur_first(temp[input[i]])):
					print 'if',input, buffer,cur_first(temp[input[i]])
					break	
				else:
					print 'else', input,buffer,input[i],'---',cur_first(temp[input[i]])
					buffer.extend(cur_first(input[1:]))
	#	print 'input[-1]',input[-1],cur_first(temp[input[-1]])
		if (input[-1] in temp) and ("epsilon" in cur_first(temp[input[-1]])):
			print '$$$'
			buffer.append("epsilon")
	print '^^^^^^^^',input,'--',buffer,'--',first
	return buffer

for v in temp:
	for lv in temp[v]:
		print '-=-=-=',lv
		if v not in first:
			first[v]=[]
		first[v].extend(cur_first(lv))
			



print "First:"
def print_list(dict):
	for v in dict:
			cons="  %s ->"%v
			for lv in dict[v]:
				cons=cons+" %s"%lv
			print cons

print_list(first)

#
#for v in temp:
#	for lvv in temp[v]:
#		if lvv!="epsilon":
#			lvv=lvv.split(" ")
#			for i in xrange(len(lvv)-1):
#				follow[lvv[i]].extend(first[lvv[i+1]])
#				if "epsilon" in follow[lvv[i]]:
#					follow[lvv[i]].remove("epsilon")
#for v in temp:
#	for lvv in temp[v]:
#		if lvv!="epsilon" and lvv[-1].isupper():
#			follow[lvv[-1]].extend(follow[v])
#

#print "Follow:"
#print_list(follow)
