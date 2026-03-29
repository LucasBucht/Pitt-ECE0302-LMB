#include <stdexcept>
#include "XMLParser.hpp"

// Helper functions

static bool isNameStartChar(unsigned char c)
{
	// XML name start character must be a letter, underscore, or colon
	// isNameStartChar checks for valid start character
	return (std::isalpha(c) || c == '_' || c == ':');
}

static bool isNameChar(unsigned char c)
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
		if (std::isspace((unsigned char)name[i])){
			return false;
		}
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

XMLParser::XMLParser() : tokenizedFlag(false), parsedFlag(false)
{
} 

bool XMLParser::tokenizeInputString(const std::string &inputString)
{
	// Reset state for every call
	tokenizedInputVector.clear();
	while (!parseStack.isEmpty()){
		parseStack.pop();
	}
	elementNameBag.clear();
	tokenizedFlag = false;
	parsedFlag = false;

	size_t i = 0;
	size_t len = inputString.size();

	while (i < len){
		if (inputString[i] == '>'){
			return false;
		}
		if (inputString[i] == '<'){
			// Find closing >
			size_t closePos = inputString.find('>', i + 1);
			if (closePos == std::string::npos){
				// Unclosed
				return false;
			}
			
			// Body text between < and >
			std::string body = inputString.substr(i + 1, closePos - i - 1);
			
			if (body.find('<') != std::string::npos){
				// Reject if multiple <
				return false;
			}

			// A newline inside a tag body is invalid
			for (char c : body){
				if (c == '\n' || c == '\r'){
					return false;
				}
			}

			TokenStruct tok;

			// <? ... ?>
			if (!body.empty() && body[0] == '?'){
				if (closePos < 1 || inputString[closePos - 1] != '?'){
					// Return false is closing is not ?>
					return false;				
				}

				// Get rid of leading and trailing ?
				std::string inner = body.substr(1, body.size() - 2);
				
				if (inner.empty()){
					// Inner should not be empty
					return false;
				}

				tok.tokenType = DECLARATION;
				tok.tokenString = inner;
			}

			// </name>
			else if (body.size() >= 1 && body[0] == '/'){
				std::string name = extractName(body, 1);
				if (!isValidName(name)){
					return false;
				}

				size_t afterName = name.size() + 1;

				while (afterName < body.size() && std::isspace(body[afterName])){
					afterName++;
				}

				if (afterName != body.size()){
					// Return false if extra characters
					return false;
				}

				tok.tokenType = END_TAG;
				tok.tokenString = name;
			}

			// <name ... />
			else if (!body.empty() && body.back() == '/'){
				std::string nameBody = body.substr(0, body.size() - 1);
                std::string name = extractName(nameBody, 0);

                if (!isValidName(name)){
					return false;
				}

                tok.tokenType = EMPTY_TAG;
                tok.tokenString = name;
			}

			// <name ... >
			else{
				if (body.empty() || std::isspace(body[0])){
					// Return false if empty or start with a space
					return false;
				}

                std::string name = extractName(body, 0);

				size_t afterName = name.size();
				if (afterName < body.size() && !std::isspace(body[afterName])){
					return false;
				}

                if (!isValidName(name)){
					return false;
				}

                tok.tokenType = START_TAG;
                tok.tokenString = name;
			}

			tokenizedInputVector.push_back(tok);
			i = closePos + 1;
		}
		else{
            size_t nextAngle = inputString.find_first_of("<>", i);
			size_t nextTag = nextAngle;
			if (nextAngle != std::string::npos && inputString[nextAngle] == '>'){
				return false;
			}
    
            std::string content;
			if (nextTag == std::string::npos){
    			content = inputString.substr(i);
			} 
			else{
    			content = inputString.substr(i, nextTag - i);
			}
            bool allSpace = true;
            for (char c : content)
                if (!std::isspace(c)){ 
					allSpace = false; 
					break; 
				}

            if (!allSpace)
            {
                TokenStruct tok;
                tok.tokenType = CONTENT;
                tok.tokenString = content;
                tokenizedInputVector.push_back(tok);
            }

            if (nextTag == std::string::npos){
    			i = len;
			} 
			else{
    			i = nextTag;
			}
        }
	}

	if (tokenizedInputVector.empty()){
		return false;
	}

	tokenizedFlag = true;
    return true;
} 

bool XMLParser::parseTokenizedInput()
{
	// Reset parse flag
	parsedFlag = false;

	if (!tokenizedFlag || tokenizedInputVector.empty()){
		// Return false if not tokenized or empty
		return false;
	}

	while (!parseStack.isEmpty()){
		// Clear out parseStack
		parseStack.pop();
	}
	elementNameBag.clear();

	// Check if root element has been open or closed
	bool rootOpened = false;
	bool rootClosed = false;
	
	for (const TokenStruct& tok : tokenizedInputVector){
		switch (tok.tokenType){
			case DECLARATION:
				if (rootOpened){
					return false;
				}
				break;
			
			case CONTENT:
				if (parseStack.isEmpty()){
					return false;
				}
				break;
			
			case EMPTY_TAG:
				if (!rootOpened){
					rootOpened = true;
					rootClosed = true;
				}
				else if (rootClosed){
					return false;
				}
				elementNameBag.add(tok.tokenString);
				break;

			case START_TAG:
				if (rootClosed){
					return false;
				}
				if (!rootOpened){
					rootOpened = true;
				}
				parseStack.push(tok.tokenString);
				elementNameBag.add(tok.tokenString);
				break;

			case END_TAG:
				if (parseStack.isEmpty()){
					return false;
				}
				if (parseStack.peek() != tok.tokenString){
					return false;
				}
				parseStack.pop();
				if (parseStack.isEmpty()){
					rootClosed = true;
				}
				break;
		}
	}

	if (!rootOpened || !rootClosed || !parseStack.isEmpty()){
		return false;
	}

	parsedFlag = true;
	return true;
}

void XMLParser::clear()
{
	tokenizedInputVector.clear();
	while (!parseStack.isEmpty()){
		parseStack.pop();
	}
	elementNameBag.clear();
	tokenizedFlag = false;
	parsedFlag = false;
}

std::vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector;
}

bool XMLParser::containsElementName(const std::string &inputString) const
{
	if (!tokenizedFlag || !parsedFlag){
        throw std::logic_error("containsElementName: input not tokenized/parsed");
	}
	return elementNameBag.contains(inputString);
}

int XMLParser::frequencyElementName(const std::string &inputString) const
{
	if (!tokenizedFlag || !parsedFlag){
        throw std::logic_error("frequencyElementName: input not tokenized/parsed");
	}
    return elementNameBag.getFrequencyOf(inputString);
}

