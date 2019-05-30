#!/usr/bin/python
# -*- coding: UTF-8 -*-
class Employee:
	'员工'
	empCount = 0;
	def __init__(self,name,salary):
		self.name = name
		self.salary = salary
		Employee.empCount += 1
	def displayCount(self):
		print "Total Employee %d" % Employee.empCount
	def displayEmployee(self):
		print "name :",self.name,",Salary:",self.salary

'''
emp1 = Employee("zara",2200)
emp2 = Employee("Manni",3200)
emp1.displayEmployee()
emp2.displayEmployee()
emp2.displayCount()
'''
print "Employee.__doc__:",Employee.__doc__
print "Employee.__name__:",Employee.__name__
print "Employee.__module__:",Employee.__module__
print "Employee.__bases__",Employee.__bases__
print "Employee.__dict__",Employee.__dict__


