class Matrix(object):
	def __init__(self):
		self.matrix=[['M']]

	def add_col(self,cname):
		for i in xrange(len(self.matrix)):
			if i == 0:
				self.matrix[i].append(cname)
			else:
				self.matrix[i].append(-1)
#		print self.matrix[0]

	def add_row(self,rname):
		nrow=[rname]
		for i in xrange(len(self.matrix[0])-1):
			nrow.append(-1)
		self.matrix.append(nrow)
	
	def set(self,row,col,value):
		trig=0
#		print self.matrix[0],'---',col
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

	def get_matrix(self):
		return self.matrix
				
