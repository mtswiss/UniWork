#! /usr/local/bin/python
import sys
 
class task1(object):
	def union(self,l1,l2):
		for i in l2:
			if i not in l1:
				l1.append(i)
		return l1

	def dic_print(self,dic):
		for i in dic:
			cons="  %s ->"%i
			for ii in dic[i]:
				cons=cons+" %s"%ii
			print cons

	def cur_first(self,input):
		buffer=[]
		print '|||',input,self._trig
		if len(input)!=1 and input!="epsilon":
			self._trig=1
		if (self._trig==0) and (input not in self.temp):
			print 'entre',input
			if input=="epsilon" or (input.islower() and len(input)==1):
				return [input]
		elif input!="epsilon":
			if self._trig==0:
				input=self.temp[input]
			self._trig=0
			print "runing",input
			for y in input:
				if y=="epsilon" or (y.islower() and len(y)==1):
					buffer=self.union(buffer,[y])
				elif y!=' ': #
					buffer=self.first_sen(y)
		return buffer

	def first_sen(self,input):
#		print '||||||',input,input.strip().split(' '),self.cur_first("epsilon")
		buffer=[]
		e=1
		for yx in input.strip().split(' '):
			fy1=self.cur_first(yx)
#			print "||||",fy1
			if "epsilon" in fy1:
				fy1.remove("epsilon")
			buffer=self.union(buffer,fy1)
			if "epsilon" not in self.cur_first(yx):
				e=0
				break
		print e,input
		if e==1:
			buffer=self.union(buffer,["epsilon"])
		return buffer
		


	def cur_follow(self,input):
		buffer=[]
		for V in self.temp:
			rhs=self.temp[V]
#			print '^^^',input,rhs
			for S in rhs:
				if S!="epsilon":
					for i in xrange(len(S)-1):
						if S[i]==input: 
							if (S[i+1:] in self.temp) and ("epsilon" in self.temp[S[i+1:]]):
								buffer=self.union(buffer,self.cur_follow(V))
								buffer=self.union(buffer,self.follow[V])
							else:
								self._trig=1
								buffer=self.union(buffer,self.curr_first([S[i+1:].strip()]))
					if S[-1]==input:
						buffer=self.union(buffer,self.cur_follow(V))
						buffer=self.union(buffer,self.follow[V])
		return buffer

	def __init__(self,fname):
		self.temp={}
		self.first={}
		self.follow={}
		self._trig=0
		self._start=1
		for line in open(fname,"rU"):
			if line[0] not in self.temp:
				self.temp[line[0]]=[]
				self.follow[line[0]]=[]
			if self._start==1:
				self.follow[line[0]].append("epsilon")
				self._start=0
			rhs=line[:-1].split("=")[1].strip()
			self.temp[line[0]].append(rhs)
		print 'temp',self.temp
		for V in self.temp:
			self.first[V]=self.curr_first(V)
			self.follow[V].extend(self.curr_follow(V))

	def get_first(self):
		return self.first
	
	def get_follow(self):
		return self.follow 

	def get_production(self):
		return self.temp

input=task1(sys.argv[1])
print "First:"
input.dic_print(input.get_first())

print "Follow:"
input.dic_print(input.get_follow())
