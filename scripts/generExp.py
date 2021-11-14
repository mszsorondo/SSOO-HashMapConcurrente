from creadorPalabras import WordGenerator
import os
import sys


"""
la idea es que haya una carpeta por cada nivel de inestabilidad de las muestras
No importa la letra insetable
"""
def generarExperimento(unstability, letter, folder):
	word_file = "/usr/share/dict/words"
	WORDS = open(word_file).read().splitlines()

	wg = WordGenerator(WORDS)
	wg.splitByStart()

	now = os.getcwd()
	newfold = now + "/" +folder
	if not (os.path.exists(newfold)):
		os.mkdir(newfold)
	letasc = 97
	i = 0
	reps = unstability
	while(i<26):
		let = chr(letasc)
		
		if(let=="x"):
			letasc = letasc + 1
			i = i + 1
			continue
		if(let==letter):
			now = wg.getNwordsFrom(let, 100,(unstability-reps)*100)
		else:
			now = wg.getNwordsFrom(let, 100,0)
		
		print("cantPalabras = ",len(now),"\n")
		# escribirlas en el archivo
		f = open(newfold+"/"+let+str(i)+"100", "w")
		f.writelines(["%s\n" % item  for item in now])
		i = i + 1	
		if(let != letter or ((let==letter) & (reps==1))):
			letasc = letasc + 1
		else:
			reps = reps - 1

