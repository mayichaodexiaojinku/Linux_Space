#!/usr/bin/python

class JustCounter:
	__privateCount = 1
	publicCount = 2
	def count(self):
		self.__privateCount += 1
		self.publicCount += 1
		print self.__privateCount

counter = JustCounter()
counter.count()
print counter.publicCount
print counter._JustCounter__privateCount
