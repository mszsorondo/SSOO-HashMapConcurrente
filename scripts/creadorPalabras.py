import math
from random_word import RandomWords

class WordGenerator:
	def __init__(self, source_dict):
		self.source_dict = source_dict
		self.split = None
	def getAllStartingWith(self,fstLet, srcDict, start):
		i = start
		res = []
		while(i<len(srcDict)):
			currentW = srcDict[i]
			if(currentW[0]==fstLet):
				res.append(currentW)
			i = i + 1
		return res

	def splitByStart(self):
		byFstLet = {}
		ascii_current = 97
		while(ascii_current <123):
			byFstLet[chr(ascii_current)] = self.getAllStartingWith(chr(ascii_current), self.source_dict, 0)
			ascii_current = ascii_current+1;
		self.split = byFstLet
	def getNwordsFrom(self,fstLet, N,fro):
		""" Get N words starting with some given letter """
		res = []
		count = N
		last = min(fro+N, len(self.split[fstLet])-1)
		return self.split[fstLet][fro:last]


