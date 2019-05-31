#!/usr/bin/python
# -*- coding: UTF-8 -*-
'''
import re
phone = "2003-303-292#这是一个国外电话"
num = re.sub(r'#.*$',"",phone)
print "电话号码是：",num

num = re.sub(r'\D',"",phone)
print "电话号码是：",num
'''
import re

def double(matched):
	value = int(matched.group('value'))
	return str(value*2)
s = 'A23G74H982'
print re.sub('(?P<value>\d+)',double,s)
