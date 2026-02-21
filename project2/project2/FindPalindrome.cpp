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
	// CutTest2 Implementation: if candidate and remaining don't satisfy property 2, kill
	if (!candidateSentence.empty() && !cutTest2(candidateSentence, remainingWords))
		return;

	
	// Words left
	for (std::size_t j = 0; j < (int)remainingWords.size(); j++){
		std::vector<std::string> newCandidate = candidateSentence;
		newCandidate.push_back(remainingWords[j]);

		std::vector<std::string> newRemaining;
		for(std::size_t k = 0; k < (int)remainingWords.size(); k++){
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
	// Nothing to default construct
}

FindPalindrome::~FindPalindrome()
{
	// Nothing to destroy
}

int FindPalindrome::number() const
{
	return (int)palindromes_.size();
}

void FindPalindrome::clear()
{
	words_.clear();
	palindromes_.clear();
}

bool FindPalindrome::cutTest1(const std::vector<std::string> & wordVector)
{
	int counts[26] = {0};
	for (std::size_t i = 0; i < wordVector.size(); i++){
    	for (std::size_t j = 0; j < wordVector[i].size(); j++){
        	counts[tolower(wordVector[i][j]) - 'a']++;
		}
	}

	// Check for odd counts
	int oddCount = 0;
	for (std::size_t i = 0; i < 26; i++){
		if (counts[i] % 2 != 0){
			oddCount++;
		}
	}

	return (oddCount <= 1);
}

bool FindPalindrome::cutTest2(const std::vector<std::string> & wordVector1,
                              const std::vector<std::string> & wordVector2)
{
	int counts1[26] = {0};
	for (std::size_t i = 0; i < wordVector1.size(); i++){
    	for (std::size_t j = 0; j < wordVector1[i].size(); j++){
        	counts1[tolower(wordVector1[i][j]) - 'a']++;
		}
	}

	int counts2[26] = {0};
	for (std::size_t i = 0; i < wordVector2.size(); i++){
    	for (std::size_t j = 0; j < wordVector2[i].size(); j++){
        	counts2[tolower(wordVector2[i][j]) - 'a']++;
		}
	}

	// Check for fewer total characters
	std::size_t total1 = 0, total2 = 0;
	for (std::size_t i = 0; i < 26; i++){
		total1 += counts1[i];
		total2 += counts2[i];
	}

	// Set smaller and larger substrings
	const int* smaller;
	const int* larger;

	if (total1 <= total2){
    	smaller = counts1;
    	larger  = counts2;
	} else {
    	smaller = counts2;
    	larger  = counts1;
	}

	// Every char in the smaller must appear as often in the larger
	for (int i = 0; i < 26; i++){
		if (smaller[i] > larger[i]){
			return false;
		}
	}
		
	return true;
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
	palindromes_.clear();
	if (cutTest1(words_)){
		recursiveFindPalindromes({}, words_);
	}
	return true;
}

bool FindPalindrome::add(const std::vector<std::string> & wordVector)
{
	// Return false if vector is empty or character isn't in the alphabet
	for (std::size_t i = 0; i < wordVector.size(); i++){
   		if (wordVector[i].empty()){
			return false;
		}
    	for (std::size_t j = 0; j < wordVector[i].size(); j++){
        	if (!isalpha(wordVector[i][j])){
				return false;
			}
    	}
	}

	// Return false if words inside vector are duplicates
	for (std::size_t i = 0; i < (int)wordVector.size(); i++){
		std::string lowerI = wordVector[i];
		convertToLowerCase(lowerI);
		for (std::size_t j = i + 1; j < (int)wordVector.size(); j++){
			std::string lowerJ = wordVector[j];
			convertToLowerCase(lowerJ);
			if (lowerI == lowerJ){
				return false;
			}
		}
	}

	// Return false if words inside vector already exist outside vector
	for (std::size_t i = 0; i < wordVector.size(); i++){
    	std::string lowerNew = wordVector[i];
    	convertToLowerCase(lowerNew);
    	for (std::size_t j = 0; j < words_.size(); j++){
        	std::string lowerW = words_[j];
        	convertToLowerCase(lowerW);
        	if (lowerW == lowerNew){
				return false;
			}     	
    	}
	}

	for (std::size_t i = 0; i < wordVector.size(); i++){
    	words_.push_back(wordVector[i]);
	}

	palindromes_.clear();
	if (cutTest1(words_)){
		recursiveFindPalindromes({}, words_);
	}
	return true;
}

std::vector< std::vector<std::string> > FindPalindrome::toVector() const
{
	return palindromes_;
}