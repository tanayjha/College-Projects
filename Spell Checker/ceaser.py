import sys, re, collections
import operator 


# Seperates out all the words from the file in lowercase
def seperateWords(text): 
	return re.findall('[a-z]+', text.lower()) 

# Creates the language model based on the words in the dictionary
def createModel(features):
	model = collections.defaultdict(lambda: 1)
	for f in features:
		for j in range(len(f)):
			model[f[j]] += 1
	return model

# Function to initialise the user interface
if __name__ == "__main__":
	allWords = createModel(seperateWords(open('trainingdata.txt').read()))
	alphabet = 'abcdefghijklmnopqrstuvwxyz'
	

	s = 0
	for i in alphabet:
		s += allWords[i]
	dicte = {}
	for i in alphabet:
		dicte[i] = (allWords[i]/s)*100
	sortedVal = sorted(dicte.items(), key=operator.itemgetter(1))
	for (i, j) in sortedVal:
		print(i, j)