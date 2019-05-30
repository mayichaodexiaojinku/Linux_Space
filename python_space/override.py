#!/usr/bin/python
class Vector:
	def __init__(self,a,b):
		self.a = a
		self.b = b
	def __str__(self):
		return "vector(%d %d)" % (self.a,self.b)
	def __add__(self,other):
		return Vector(self.a+other.a,self.b+other.b)

v1 = Vector(2,10)
v2 = Vector(1,5)
print v1+v2
