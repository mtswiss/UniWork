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

	def sq_first(self,string):
		output={'buffer':[],'flag':0}
		for toke in string.split(' '):
			trig=0
			if toke in self.first:
				fy1=deepcopy(self.first[toke])
				if 'epsilon' in fy1:
					trig=1
					fy1.remove('epsilon')
				output['buffer']=self.union(output['buffer'],fy1)
				if trig==0:
					break				
			elif toke.islower():
				if toke not in output['buffer']:
					output['buffer'].append(toke)
				break
			else:
				output['flag']=1
				break
		if trig==1:
			if 'epsilon' not in output['buffer']:
				output['buffer'].append('epsilon')
		return output	

	def wl_first(self):
		flag=1
		while(flag):
			flag=0
			for V in self.temp:
				if V not in self.first:
					self.first[V]=[]
					flag=1
				for rhs in self.temp[V]:
					if (len(rhs)==1 and rhs.islower()) or rhs=='epsilon':
						if rhs not in self.first[V]:
							self.first[V].append(rhs)
							flag=1
					else:
						cache=self.sq_first(rhs)
						l0=len(self.first[V])
						self.first[V]=self.union(self.first[V],cache['buffer'])
						if l0!=len(self.first[V]) or cache['flag']==1:
							flag=1

	def se_follow(self):
		flag=1
		while (flag):
			flag=0
			for V in self.temp:
				if V not in self.follow:	
					self.follow[V]=[]
					flag=1
					if V==self.get_start():
						self.follow[V].append('$')
				else:
					for _V in self.temp:
						rhs=self.temp[_V]
						for S in rhs:
							if S!='epsilon':
								S=S.replace(' ','')
								l0=len(self.follow[V])
								for i in xrange(len(S)-1):
									if S[i]==V:
										buf_fir=self.sq_first(' '.join(S[i+1:]))['buffer']
										if 'epsilon' in buf_fir:
											buf_fir.remove('epsilon')
											self.follow[V]=self.union(self.follow[V],self.follow[_V])
										self.follow[V]=self.union(self.follow[V],buf_fir)
								if S[-1]==V:
									self.follow[V]=self.union(self.follow[V],self.follow[_V])
								if l0!=len(self.follow[V]):
									flag=1

	def __init__(self,fname):
		self.temp={}
		self.first={}
		self.follow={}
		non_start=[]
		count=0
		for line in open(fname,"rU"):
			rhs=line[:-1].split('=')[1].strip()
			if line[0] not in self.temp:
				self.temp[line[0]]={}
			if rhs!='epsilon' and (not rhs.islower()):
				for toke in rhs.split(' '):
					if toke.isupper() and toke!=line[0] and (toke not in non_start):
						non_start.append(toke)
			self.temp[line[0]][rhs]=count
			count=count+1
		non_terminal=deepcopy(self.temp.keys())
		self.start=list(set(non_terminal)-set(non_start))[0]
		self.wl_first()
		self.se_follow()
	
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
		self.start=self.input.get_start()

	def get_start(self):
		return self.start
		
	def construct(self):
		mx=Matrix()
		for A in self.product:
			for rhs in self.product[A]:
				f_buffer=self.input.sq_first(rhs)['buffer']
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
		self.start=self.pre_table.get_start()

	def is_LL(self):
		return (self.par_table is not None)

	def parsing(self,input):
		stk=Stack()
		stk.push('$')
		stk.push(self.start)
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
