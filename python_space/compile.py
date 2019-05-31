#!/usr/bin/python
# -*- coding: UTF-8 -*-
'''
import re
patten = re.compile(r'\d+')
result1 = patten.findall('runoob 123 goolf 34')
result2 = patten.findall('runo23jhbh423324',0,10)
print result1
print result2
'''
import re
it = re.finditer(r'\d+',"12a32bc43jf3")
for match in it:
	print match.group()

