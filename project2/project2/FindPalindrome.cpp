#include <string>
#include <vector>
#include "FindPalindrome.hpp"

//------------------- HELPER FUNCTIONS -----------------------------------------

// non-class helper functions go here, should be declared as "static" so that
// their scope is limited

/** Helper function to convert string to lower case */
static void convertToLowerCase(std::string & value)
{
	for (int i=0; i<value.size(); i++) {
		value[i] = tolower(value[i]);
	}
}

//------------------- PRIVATE CLASS METHODS ------------------------------------

void FindPalindrome::recursiveFindPalindromes(std::vector<std::string>
        candidateSentence, std::vector<std::string> remainingWords)
{
	// No words left
	if (remainingWords.empty()){
		std::string fullSentence;
		for (std::size_t i = 0; i < candidateSentence.size(); i++){
			fullSentence += candidateSentence[i];
		}
		if (isPalindrome(fullSentence)){
			palindromes_.push_back(candidateSentence);
		}
		return;
	}
	


	// Words left
	for (int j = 0; j < (int)remainingWords.size(); j++){
		std::vector<std::string> newCandidate = candidateSentence;
		newCandidate.push_back(remainingWords[j]);

		std::vector<std::string> newRemaining;
		for(int k = 0; k < (int)remainingWords.size(); k++){
			if (k != j){
				newRemaining.push_back(remainingWords[k]);
			}
		}

		recursiveFindPalindromes(newCandidate, newRemaining);
	}
}

bool FindPalindrome::isPalindrome(std::string testString) const
{
	// make sure that the string is lower case
	convertToLowerCase(testString);
	// see if the characters are symmetric
	int stringLength = testString.size();
	for (int i=0; i<stringLength/2; i++) {
		if (testString[i] != testString[stringLength - i - 1]) {
			return false;
		}
	}
	return true;
}

//------------------- PUBLIC CLASS METHODS -------------------------------------

FindPalindrome::FindPalindrome()
{
	// Default Constructor
}

FindPalindrome::~FindPalindrome()
{
	// Destructor
}

int FindPalindrome::number() const
{
	return (int)palindromes_.size();
}

void FindPalindrome::clear()
{
	// TODO 
}

bool FindPalindrome::cutTest1(const std::vector<std::string> & wordVector)
{
	
	return false;
}

bool FindPalindrome::cutTest2(const std::vector<std::string> & wordVector1,
                              const std::vector<std::string> & wordVector2)
{
	// TODO 
	return false;
}

bool FindPalindrome::add(const std::string & newWord)
{
	// Return false if string is empty
	if(newWord.empty()){
		return false;
	}
	
	// Return false if character isn't in the alphabet
	for (std::size_t i = 0; i < newWord.size(); i++){
		if (!isalpha(newWord[i])){
			return false;
		}
	}

	// Return false if string is not unique
	std::string lowerNew = newWord;
	convertToLowerCase(lowerNew);
	for (std::size_t i = 0; i < words_.size(); i++){
    	std::string lowerW = words_[i];
    	convertToLowerCase(lowerW);
    	if (lowerW == lowerNew){
			return false;
		}
	}

	words_.push_back(newWord);
	recursiveFindPalindromes({}, words_);
	return true;
}

bool FindPalindrome::add(const std::vector<std::string> & wordVector)
{
	// TODO 
	return false;
}

std::vector< std::vector<std::string> > FindPalindrome::toVector() const
{
	// TODO
	return std::vector< std::vector<std::string> >();
}

