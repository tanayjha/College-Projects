import sys, re, collections
from PyQt4 import QtCore, QtGui, uic

qtCreatorFile = "spellchecker.ui"
Ui_MainWindow, QtBaseClass = uic.loadUiType(qtCreatorFile)

# Seperates out all the words from the file in lowercase
def seperateWords(text): 
	return re.findall('[a-z]+', text.lower()) 

# Creates the language model based on the words in the dictionary
def createModel(features):
	model = collections.defaultdict(lambda: 1)
	for f in features:
		model[f] += 1
	return model

# Returns set of all words having edit distance of one from the original word
def editDistanceOne(word):
	# Tuple containing splits of the original word at every index
	splits = [(word[:i], word[i:]) for i in range(len(word) + 1)]

	# Set of all words formed by deleting one letter from the original word
	deletes    = [a + b[1:] for a, b in splits if b]

	# Set of all words formed by swapping two adjacent letters in the original word
	transposes = [a + b[1] + b[0] + b[2:] for a, b in splits if len(b)>1]

	# Set of all words formed by replacing one letter from the original word by any letter
	replaces   = [a + c + b[1:] for a, b in splits for c in alphabet if b]

	# Set of all words formed by inserting one letter in the original word
	inserts    = [a + c + b     for a, b in splits for c in alphabet]

	# Returns the combined set of all the above words
	return set(deletes + transposes + replaces + inserts)

# Returns set of all known words having edit distance of two from the original word
def editDistanceTwo(word):
	return set(e2 for e1 in editDistanceOne(word) for e2 in editDistanceOne(e1) if e2 in allWords)

# Returns set of words is in the dictionary
def knownWord(words): 
	return set(w for w in words if w in allWords)

# Main function which calls other functions and displays the suggestions 
def correctSpelling(word):
	# print("trained")

	lst = [] # Stores the list of suggestions
	if knownWord([word]):
		possibleSuggestions = knownWord([word])
		a = max(possibleSuggestions, key=allWords.get) # Picking out the word with maximum frequency
		lst.append(a)
		possibleSuggestions.remove(a)
	# All possible known words that can be formed from the original word
	possibleSuggestions = knownWord(editDistanceOne(word)) or editDistanceTwo(word) or [word]
	# print ("possibleSuggestions", possibleSuggestions)
	print (possibleSuggestions)

	# Forming the list of top three suggestions 
	a = max(possibleSuggestions, key=allWords.get) # Picking out the word with maximum frequency
	lst.append(a) # First Suggestion
	possibleSuggestions.remove(a)
	if len(possibleSuggestions) == 0:  # Only one suggestion
		return lst
	a = max(possibleSuggestions, key=allWords.get)
	lst.append(a) # Second Suggestion
	possibleSuggestions.remove(a)
	if len(possibleSuggestions) == 0:  # Only two suggestions
		return lst
	a = max(possibleSuggestions, key=allWords.get)
	lst.append(a) # Third Suggestion
	possibleSuggestions.remove(a)
	return list(set(lst)) # Return the list of all sugges0tions

# Function to create the user interface
class MyApp(QtGui.QMainWindow, Ui_MainWindow):
	def __init__(self):
		QtGui.QMainWindow.__init__(self)
		Ui_MainWindow.__init__(self)
		self.setupUi(self)
		self.check_button.clicked.connect(self.CorrectWord)
		self.setWindowTitle("Spell Checker")

	def CorrectWord(self):
		word = self.entered_word.text()
		word = correctSpelling(word)  # Call to the main function
		# print (lst)
		suggestions = ""
		for i in word:  # Dislaying all the suggestions
			suggestions = suggestions + i + "\n"
		self.corrections.setText(suggestions)

# Function to initialise the user interface
if __name__ == "__main__":
	app = QtGui.QApplication(sys.argv)
	window = MyApp()
	b = QtGui.QLabel(window)
	b.setText("          Enter word:")
	window.setGeometry(300,500,410,300)
	b.move(0,-3)
	c = QtGui.QLabel(window)
	c.setText("         Suggestions:")
	window.setGeometry(300,500,410,300)
	c.move(0,120)
	window.show()
	allWords = createModel(seperateWords(open('trainingdata.txt').read()))
	alphabet = 'abcdefghijklmnopqrstuvwxyz'
	sys.exit(app.exec_())