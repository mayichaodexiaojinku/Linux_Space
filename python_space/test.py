#!/usr/bin/python
# -*- coding:UTF-8 -*-
'''
x,y=1,2
if True:
	print y
	print x
else:
	print "anwser"
  	print "false"
numbers = [12,23,23,54,65,89]
even = []
odd= []
while len(numbers) > 0 :
	number = numbers.pop()
	if(number % 2 == 0):
		even.append(number)
	else:
		odd.append(number)
print even
print odd
'''
'''
for letter in 'Python':
	print '当前字母：',letter
fruits = ['banana','apple','mango']
for fruit in fruits:
	print '当前水果：',fruit
'''
'''
fruits = ['banana','apple','mango']
for index in range(len(fruits)):
	print "当前水果：",fruits[index]
print "it`s over"
'''
'''
for num in range(10,20):
	for i in range(2,num):
		if num%i == 0:
			j = num/i;
			print "%d 等于 %d *%d"%(num,i,j)
			break
	else:
		print num,'是一个质数'
'''
'''
rows = int(raw_input('输入列数：'))
i = j = k = 1
print "等腰直角三角形"
for i in range(0,rows):
	for k in range(0,rows - i):
		print " * ",
		k += 1
	i += 1
	print '\n'
'''
'''
i = 2
while(i < 100):
	j = 2
	while(j <= (i/j)):
		if not(i%j):
			break
		j += 1
	if(j > i/j):
		print i,'是素数'
	i += 1
'''
'''

import calendar;
import time;
ticks = time.asctime(time.localtime(time.time()))
cal = calendar.month(2019,5)
print '当前时间为：',ticks
print cal

'''
'''

Money = 2000
def AddMoney():
	global Money
	Money += 1
print Money
AddMoney()
print Money

'''
import math
con = dir(math)
print con
