#include <stdexcept>
#include "XMLParser.hpp"

// Helper functions

static bool isNameStartChar(char c)
{
	// XML name start character must be a letter, underscore, or colon
	// isNameStartChar checks for valid start character
	return (std::isalpha(c) || c == '_' || c == ':');
}

static bool isNameChar(char c)
{
	// XML name must contain only letters, underscores, colons, dashes, or periods
	// isNameChar checks for valid name characters throughout the name
	return (std::isalnum(c) || c == '_' || c == ':' || c == '-' || c == '.');
}

static bool isValidName(const std::string& name)
{
	if (name.empty()){
		// Check if empty
		return false;
	}

	if (!isNameStartChar(name[0])){
		// Check starting character
		return false;
	}

	for (size_t i = 1; i < name.size(); i++){
		if (!isNameChar(name[i])){
			// Check all name characters after starting character
			return false;
		}
	}

	// Return true if no issues
	return true;
}

static std::string extractName(const std::string& body, size_t start = 0)
{
	size_t i = start;
	while (i < body.size() && !std::isspace(body[i]) && body[i] != '/'){
		i++;
	}
	// Extracts tag name from text between < and >
	// Stops at first space or /
	return body.substr(start, i - start);
}





// Main functions

XMLParser::XMLParser()
{
	// TODO
} 

bool XMLParser::tokenizeInputString(const std::string &inputString)
{
	// TODO
	return false;
} 

bool XMLParser::parseTokenizedInput()
{
	// TODO
	return false;
}

void XMLParser::clear()
{
	// TODO
}

std::vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector;
}

bool XMLParser::containsElementName(const std::string &inputString) const
{
	// TODO
	return false;
}

int XMLParser::frequencyElementName(const std::string &inputString) const
{
	// TODO
	return -1;
}

