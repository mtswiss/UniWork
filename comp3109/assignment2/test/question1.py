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

	def se_first(self,input):
		buffer=[]
		if len(input)==1 or input=='epsilon':
			if input in self.temp:
				for rhs in self.temp[input]:
					buffer=self.union(buffer,self.se_first(rhs))
			elif input.islower() or input=="epsilon":
				buffer.append(input)
		else:
			e_in_all=1
			for yx in input.split(' '):
				fy1=self.se_first(yx)
				if 'epsilon' in fy1:
					fy1.remove('epsilon')
					buffer=self.union(buffer,fy1)
				else:
					buffer=self.union(buffer,fy1)
					e_in_all=0
					break
			if e_in_all==1:
				buffer=self.union(buffer,['epsilon'])
		return buffer

	def se_follow(self,input):
		buffer=[]
		for V in self.temp:
			rhs=self.temp[V]
			for S in rhs:
	#			print '|||',input,'|',V,'|',S
				if S!='epsilon':
					S=S.replace(' ','')
					for i in xrange(len(S)-1):
						if S[i]==input:
							buf_fir=self.se_first(' '.join(S[i+1:]))
	#						print '##',input,'|',S[i:],'|',buf_fir
							if (' '.join(S[i+1:]) in self.temp) and ('epsilon' in self.temp[' '.join(S[i+1:]) ]):
								buffer=self.union(buffer,self.se_follow(V))
								buffer=self.union(buffer,self.follow[V])
							if 'epsilon' in buf_fir:
								buf_fir.remove('epsilon')
							buffer=self.union(buffer,buf_fir)
					if S[-1]==input:
						buffer=self.union(buffer,self.se_follow(V))
						buffer=self.union(buffer,self.follow[V])
		return buffer

	def __init__(self,fname):
		self.temp={}
		self.first={}
		self.follow={}
		count=0
		for line in open(fname,"rU"):
			rhs=line[:-1].split('=')[1].strip()
			if line[0] not in self.temp:
				self.temp[line[0]]={}
				self.follow[line[0]]=[]
				if count==0:
					self.follow[line[0]].append("epsilon")
			self.temp[line[0]][rhs]=count
			count=count+1
		print 'temp',self.temp
		for V in self.temp:
			self.first[V]=self.se_first(V)
			self.follow[V].extend(self.se_follow(V))

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
