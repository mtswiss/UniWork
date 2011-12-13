#! /usr/local/bin/python
import sys
from copy import deepcopy
  
class process(object):
	def union(self,l1,l2):
		for i in l2:
			if i not in l1:
				l1.append(i)
		return l1

	def dic_print(self,dic):
		for i in sorted(dic):
			cons="  %s ->"%i
			for ii in sorted(dic[i]):
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
		if input==self.get_start():
			buffer.append('$')
		for V in self.temp:
			rhs=self.temp[V]
			for S in rhs:
				if S!='epsilon':
					S=S.replace(' ','')
					for i in xrange(len(S)-1):
						if S[i]==input:
							buf_fir=self.se_first(' '.join(S[i+1:]))
							if (' '.join(S[i+1:]) in self.temp) and ('epsilon' in self.temp[' '.join(S[i+1:]) ]):
								buffer=self.union(buffer,self.se_follow(V))
							if 'epsilon' in buf_fir:
								buf_fir.remove('epsilon')
							buffer=self.union(buffer,buf_fir)
					if S[-1]==input:
						buffer=self.union(buffer,self.se_follow(V))
		return buffer

	def __init__(self,fname):
		self.temp={}
		self.first={}
		self.follow={}
		self.start=''
		count=0
		for line in open(fname,"rU"):
			rhs=line[:-1].split('=')[1].strip()
			if line[0] not in self.temp:
				self.temp[line[0]]={}
				self.follow[line[0]]=[]
				if count==0:
					self.start=line[0]
			self.temp[line[0]][rhs]=count
			count=count+1
#		print 'temp',self.temp
		for V in self.temp:
			self.first[V]=self.se_first(V)
			self.follow[V].extend(self.se_follow(V))
	
	def get_start(self):
		return self.start

	def get_first(self):
		return self.first
	
	def get_follow(self):
		return self.follow 

	def get_production(self):
		return self.temp
		
class Stack(object):
	def __init__(self):
		self.core=[]
	
	def top(self):
		return self.core[0]

	def push(self,value):
		temp=value.split(' ')
		temp.extend(self.core)
		self.core=temp
	
	def pop(self):
		temp=self.core[0]
		self.core=self.core[1:]
		return self.core

	def prt(self):
		return self.core

	def is_empty(self):
		return len(self.core)==0

class Matrix(object):
	def __init__(self):
		self.matrix=[['M']]

	def add_col(self,cname):
		for i in xrange(len(self.matrix)):
			if i == 0:
				self.matrix[i].append(cname)
			else:
				self.matrix[i].append(-1)

	def add_row(self,rname):
		nrow=[rname]
		for i in xrange(len(self.matrix[0])-1):
			nrow.append(-1)
		self.matrix.append(nrow)
	
	def set(self,row,col,value):
		trig=0
		if col not in self.matrix[0]:
			self.add_col(col)
		for i in xrange(len(self.matrix[0])-1):
			if (self.matrix[0][i+1]==col):
				for r in self.matrix:
					if r[0]==row:
						if r[i+1]!=-1:
							return 0
						else:
							r[i+1]=value
							trig=1
							return 1
				if trig==0:
					self.add_row(row)
					return self.set(row,col,value)
	
	def get(self,row,col):
		for r in xrange(len(self.matrix)-1):
			if self.matrix[r+1][0]==row:
				for c in xrange(len(self.matrix[0])-1):
					if self.matrix[0][c+1]==col:
						return self.matrix[r+1][c+1]


	def get_matrix(self):
		return self.matrix
				
class table(object):
	def __init__(self,fname):
		self.input=process(sys.argv[1])
		self.first=self.input.get_first()
		self.follow=self.input.get_follow()
		self.product=self.input.get_production()
		
	def construct(self):
		mx=Matrix()
		for A in self.product:
			for rhs in self.product[A]:
				f_buffer=self.input.se_first(rhs)
				t_f_buffer=deepcopy(f_buffer)
				if "epsilon" in t_f_buffer:
					t_f_buffer.remove("epsilon")
				for a in t_f_buffer:
					if mx.set(A,a,(rhs,self.product[A][rhs]))==0:
						return None
				if 'epsilon' in f_buffer:
					b_follow=deepcopy(self.follow[A])
					if "epsilon" in b_follow:
						b_follow.remove("epsilon")
					for b in b_follow:
						if mx.set(A,b,(rhs,self.product[A][rhs]))==0:
							return None
					if 'epsilon' in self.follow[A]:
						if mx.set(A,'epsilon',(rhs,self.product[A][rhs]))==0:
							return None
		return mx

	def table_print(self,matrix):
		if matrix is not None:
			output=matrix.get_matrix()
			for r in xrange(len(output)-1):
				for c in xrange(len(output[0])-1):
					rule=output[r+1][c+1]
					if rule!=-1:
						print 'R[%s, %s] = %i'%(output[r+1][0],output[0][c+1],rule[1])


class Parser(object):
	def __init__(self,fname):
		self.pre_table=table(fname)
		self.par_table=self.pre_table.construct()

	def is_LL(self):
		return (self.par_table is not None)

	def parsing(self,input):
		stk=Stack()
		stk.push('S $')
		index=0
		a=input[index]
		while not stk.is_empty():
			a=input[index]
			X=stk.top()
			if X.isupper():
				if self.par_table.get(X,a)!=-1 and self.par_table.get(X,a)!=None:
					stk.pop()
					stk.push(self.par_table.get(X,a)[0])
				else:
					return 'reject'
			else:
				if X==a or X=='epsilon':
					stk.pop()
					if X!='$' and X!='epsilon':
						index+=1
				else:
					return 'reject'
		if a!='$':
			return 'reject'
		else:
			return 'accept'

































