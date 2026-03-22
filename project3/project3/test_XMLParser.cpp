#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

#include "catch.hpp"
#include "XMLParser.hpp"

/* Provided test cases */

TEST_CASE("XMLParser: Test int Stack push and size", "[Stack]")
{
	Stack<int> intStack;
	int testSize = 3;
	int stackSize;
	bool correctPush, correctSize;
	for (int i = 0; i < testSize; i++)
	{
		correctPush = intStack.push(i);
		stackSize = intStack.size();
		correctSize = (stackSize == (i + 1));
		if (!correctPush || !correctSize)
		{
			break;
		}
	}
	REQUIRE(correctPush);
	REQUIRE(correctSize);
}

TEST_CASE("XMLParser: Test int Stack peek, pop", "[Stack]")
{
	Stack<int> intStack;
	int testSize = 10;
	int stackSize;
	bool correctSizeAfterPush;
	for (int i = 0; i < testSize; i++)
	{
		intStack.push(i);
		stackSize = intStack.size();
		correctSizeAfterPush = (stackSize == (i + 1));
		if (!correctSizeAfterPush)
		{
			break;
		}
	}
	REQUIRE(correctSizeAfterPush);
	bool notEmptyYetAfterPop, correctItem, notEmptyYetAfterPeek;
	for (int i = testSize - 1; i >= 0; i--)
	{
		notEmptyYetAfterPop = !intStack.isEmpty();
		int elem = intStack.peek();
		correctItem = (elem == i);
		notEmptyYetAfterPeek = !intStack.isEmpty();
		intStack.pop();
		if (!notEmptyYetAfterPop || !correctItem || !notEmptyYetAfterPeek)
		{
			break;
		}
	}
	REQUIRE(notEmptyYetAfterPop);
	REQUIRE(correctItem);
	REQUIRE(notEmptyYetAfterPeek);
	REQUIRE(intStack.isEmpty() == true);
}


TEST_CASE("XMLParser: Test tokenize <test>stuff</test>", "[XMLParser]")
{
	// You can assume that the beginning and the end of CONTENT will not be filled with whitespace
	XMLParser myXMLParser;
	std::string testString = "<test>stuff</test>";
	REQUIRE(myXMLParser.tokenizeInputString(testString));
	std::vector<TokenStruct> result = {TokenStruct{StringTokenType::START_TAG, std::string("test")},
									   TokenStruct{StringTokenType::CONTENT, std::string("stuff")},
									   TokenStruct{StringTokenType::END_TAG, std::string("test")}};
	std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput();
	REQUIRE(result.size() == output.size());
	bool correctType, correctString;
	for (int i = 0; i < result.size(); i++)
	{
		correctType = (result[i].tokenType == output[i].tokenType);
		correctString = (result[i].tokenString.compare(output[i].tokenString) == 0);
		if (!correctType || !correctString) {
			break;
		}
	}
	REQUIRE(correctType);
	REQUIRE(correctString);
}


TEST_CASE("XMLParser: Test tokenize more elements", "[XMLParser]")
{
	XMLParser myXMLParser;
	std::string testString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><Note src='gmail'>  <From>Tom</From> <To>Alice</To> </Note>";
	REQUIRE(myXMLParser.tokenizeInputString(testString));
	std::vector<TokenStruct> result = {TokenStruct{StringTokenType::DECLARATION, std::string("xml version=\"1.0\" encoding=\"UTF-8\"")},
									   TokenStruct{StringTokenType::START_TAG, std::string("Note")},
									   TokenStruct{StringTokenType::START_TAG, std::string("From")},
									   TokenStruct{StringTokenType::CONTENT, std::string("Tom")},
									   TokenStruct{StringTokenType::END_TAG, std::string("From")},
									   TokenStruct{StringTokenType::START_TAG, std::string("To")},
									   TokenStruct{StringTokenType::CONTENT, std::string("Alice")},
									   TokenStruct{StringTokenType::END_TAG, std::string("To")},
									   TokenStruct{StringTokenType::END_TAG, std::string("Note")}};
	std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput();

	REQUIRE(result.size() == output.size());
	bool correctType, correctString;
	for (int i = 0; i < result.size(); i++)
	{
		correctType = (result[i].tokenType == output[i].tokenType);
		correctString = (result[i].tokenString.compare(output[i].tokenString) == 0);
		if (!correctType || !correctString) {
			break;
		}
	}
	REQUIRE(correctType);
	REQUIRE(correctString);
}

TEST_CASE("XMLParser: Test parseTokenizedInput", "[XMLParser]")
{
	XMLParser myXMLParser;
	std::string testString = "<test myattr='abcdef'>stuff<this_is_empty_tag/></test>";
	REQUIRE(myXMLParser.tokenizeInputString(testString));
	std::vector<TokenStruct> result = {TokenStruct{StringTokenType::START_TAG, std::string("test")},
									   TokenStruct{StringTokenType::CONTENT, std::string("stuff")},
									   TokenStruct{StringTokenType::EMPTY_TAG, std::string("this_is_empty_tag")},
									   TokenStruct{StringTokenType::END_TAG, std::string("test")}};
	std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput();
	REQUIRE(result.size() == output.size());
	REQUIRE(myXMLParser.parseTokenizedInput());
	output = myXMLParser.returnTokenizedInput();
	REQUIRE(result.size() == output.size());
	bool correctType, correctString;
	for (int i = 0; i < result.size(); i++)
	{
		correctType = (result[i].tokenType == output[i].tokenType);
		correctString = (result[i].tokenString.compare(output[i].tokenString) == 0);
		if (!correctType || !correctString) {
			break;
		}
	}
	REQUIRE(correctType);
	REQUIRE(correctString);
}


TEST_CASE("XMLParser: Test XMLParser parse, contains and frequency", "[XMLParser]")
{
	XMLParser myXMLParser;
	std::ifstream myfile("../project3/TestFile.txt"); // File was pointing to the wrong spot so no file was being opened
	std::string inputString((std::istreambuf_iterator<char>(myfile)), (std::istreambuf_iterator<char>()));

	REQUIRE(myXMLParser.tokenizeInputString(inputString));
	REQUIRE(myXMLParser.parseTokenizedInput());
	REQUIRE(myXMLParser.containsElementName("catalog"));
	REQUIRE(myXMLParser.frequencyElementName("catalog") == 1);
	REQUIRE(myXMLParser.containsElementName("product"));
	REQUIRE(myXMLParser.frequencyElementName("product") == 1);
	REQUIRE(myXMLParser.containsElementName("catalog_item"));
	REQUIRE(myXMLParser.frequencyElementName("catalog_item") == 2);
	REQUIRE(myXMLParser.containsElementName("item_number"));
	REQUIRE(myXMLParser.frequencyElementName("item_number") == 2);
	REQUIRE(myXMLParser.containsElementName("size"));
	REQUIRE(myXMLParser.frequencyElementName("size") == 6);
	REQUIRE(myXMLParser.containsElementName("color_swatch"));
	REQUIRE(myXMLParser.frequencyElementName("color_swatch") == 15);
}

/* Your test cases here */


// Stack Tests
TEST_CASE("Stack: push returns true and increases size", "[Stack]")
{
    Stack<int> s;
    REQUIRE(s.push(10) == true);
    REQUIRE(s.size() == 1);
    REQUIRE(s.push(20) == true);
    REQUIRE(s.size() == 2);
    REQUIRE(s.push(30) == true);
    REQUIRE(s.size() == 3);
}

TEST_CASE("Stack: push onto empty stack makes it non-empty", "[Stack]")
{
    Stack<int> s;
    REQUIRE(s.isEmpty() == true);
    s.push(42);
    REQUIRE(s.isEmpty() == false);
}

TEST_CASE("Stack: most recent item accessible using peek", "[Stack]")
{
    Stack<std::string> s;
	REQUIRE_THROWS_AS(s.peek(), std::logic_error);
    s.push("hello");
    REQUIRE(s.peek() == "hello");
    s.push("world");
    REQUIRE(s.peek() == "world");
}

TEST_CASE("Stack: pop returns false on empty stack", "[Stack]")
{
    Stack<int> s;
    REQUIRE(s.pop() == false);
}

TEST_CASE("Stack: isEmpty is false after push, true after all pops", "[Stack]")
{
    Stack<int> s;
    s.push(1);
    s.push(2);
    REQUIRE(s.isEmpty() == false);
    s.pop();
    REQUIRE(s.isEmpty() == false);
    s.pop();
    REQUIRE(s.isEmpty() == true);
}

TEST_CASE("Stack: clear empties a full stack", "[Stack]")
{
    Stack<int> s;
    for (int i = 0; i < 5; i++) {
		s.push(i);
	} 
    REQUIRE(s.isEmpty() == false);
    s.clear();
    REQUIRE(s.isEmpty() == true);
    REQUIRE(s.size() == 0);
}

TEST_CASE("Stack: clear on already empty stack is safe", "[Stack]")
{
    Stack<int> s;
    REQUIRE_NOTHROW(s.clear());
    REQUIRE(s.isEmpty() == true);
}


// XMLParser Helper Function Tests
TEST_CASE("XMLParser Helper: checking tag name validity", "[XMLParser][helpers]")
{
    XMLParser p;
	SECTION("Valid: Letters, Underscores, Colons")
	{
		REQUIRE(p.tokenizeInputString("<note></note>"));
		REQUIRE(p.tokenizeInputString("<_tag></_tag>"));
    	REQUIRE(p.tokenizeInputString("<:tag></:tag>"));
	}
    
	SECTION("Invalid: Numbers, Hyphens, Periods")
	{
		REQUIRE_FALSE(p.tokenizeInputString("<1tag></1tag>"));
		REQUIRE_FALSE(p.tokenizeInputString("<-tag></-tag>"));
		REQUIRE_FALSE(p.tokenizeInputString("<.tag></.tag>"));
	}
}


// XMLParser tokenizeInputString Tests

TEST_CASE("XMLParser: checking invalid tokenize cases", "[XMLParser]")
{
    XMLParser p;
    REQUIRE_FALSE(p.tokenizeInputString("<start"));
	REQUIRE_FALSE(p.tokenizeInputString("<>"));
	REQUIRE_FALSE(p.tokenizeInputString("< /end>"));
	REQUIRE_FALSE(p.tokenizeInputString("<start <end>>"));
	REQUIRE_FALSE(p.tokenizeInputString("<test>invalid</test/>"));
}


// XMLParser returnTokenizedInput Tests

TEST_CASE("XMLParser: tag name correctly extracted when attributes present", "[XMLParser]")
{
    XMLParser p;
    REQUIRE(p.tokenizeInputString("<note src='x'></note>"));
    auto tokens = p.returnTokenizedInput();
    REQUIRE(tokens.size() == 2);
    REQUIRE(tokens[0].tokenString == "note");
	REQUIRE(tokens[1].tokenString == "note");
}

TEST_CASE("XMLParser: empty tag name extracted correctly before slash", "[XMLParser]")
{
    XMLParser p;
    REQUIRE(p.tokenizeInputString("<self/>"));
    auto tokens = p.returnTokenizedInput();
    REQUIRE(tokens.size() == 1);
    REQUIRE(tokens[0].tokenType == EMPTY_TAG);
    REQUIRE(tokens[0].tokenString == "self");
}

TEST_CASE("XMLParser: name extracted correctly for end tag", "[XMLParser]")
{
    XMLParser p;
    REQUIRE(p.tokenizeInputString("<root></root>"));
    auto tokens = p.returnTokenizedInput();
    REQUIRE(tokens.size() == 2);
    REQUIRE(tokens[0].tokenType == START_TAG);
    REQUIRE(tokens[0].tokenString == "root");
    REQUIRE(tokens[1].tokenType == END_TAG);
    REQUIRE(tokens[1].tokenString == "root");
}


// XMLParser parseTokenizedInput Tests
 TEST_CASE("XMLParser: checking tokenize validity", "[XMLParser]")
{
    XMLParser p;
	SECTION("Invalid Input Tests"){
    	REQUIRE_FALSE(p.tokenizeInputString("<start"));
    	REQUIRE_FALSE(p.tokenizeInputString("<>"));
    	REQUIRE_FALSE(p.tokenizeInputString("< /end>"));
    	REQUIRE_FALSE(p.tokenizeInputString("<start <stuff>>"));
   		REQUIRE_FALSE(p.tokenizeInputString("<test>invalid</test/>"));
	}
	SECTION("Valid But Unparseable Input Tests"){
		REQUIRE(p.tokenizeInputString("<onetag>"));
    	REQUIRE_FALSE(p.parseTokenizedInput());

		REQUIRE(p.tokenizeInputString("</test>invalid<test>"));
    	REQUIRE_FALSE(p.parseTokenizedInput());

		REQUIRE(p.tokenizeInputString(" just some content"));
    	REQUIRE_FALSE(p.parseTokenizedInput());
	}
}


// XMLParser Overarching Tests
TEST_CASE("XMLParser: empty tag as root is valid", "[XMLParser]")
{
    XMLParser p;
    REQUIRE(p.tokenizeInputString("<selfclose/>"));
    REQUIRE(p.parseTokenizedInput());
    REQUIRE(p.containsElementName("selfclose"));
    REQUIRE(p.frequencyElementName("selfclose") == 1);
}

TEST_CASE("XMLParser: declaration before root is valid", "[XMLParser]")
{
    XMLParser p;
    REQUIRE(p.tokenizeInputString("<?xml version=\"1.0\"?><root><child/></root>"));
    REQUIRE(p.parseTokenizedInput());
}

TEST_CASE("XMLParser: declaration after root start is invalid", "[XMLParser]")
{
    XMLParser p;
    REQUIRE(p.tokenizeInputString("<root><?xml version=\"1.0\"?></root>"));
    REQUIRE_FALSE(p.parseTokenizedInput());
}

TEST_CASE("XMLParser: content outside root is invalid", "[XMLParser]")
{
    XMLParser p;
    REQUIRE(p.tokenizeInputString("<root>ok</root>trailing"));
    REQUIRE_FALSE(p.parseTokenizedInput());
}


// XMLParser Contains/Frequency Tests

TEST_CASE("XMLParser: contains/frequency throw if not parsed", "[XMLParser]")
{
    XMLParser p;
    REQUIRE_THROWS_AS(p.containsElementName("anything"), std::logic_error);
    REQUIRE_THROWS_AS(p.frequencyElementName("anything"), std::logic_error);
}


// XMLParser Clear Tests

TEST_CASE("XMLParser: clear resets all state", "[XMLParser]")
{
    XMLParser p;
    REQUIRE(p.tokenizeInputString("<root/>"));
    REQUIRE(p.parseTokenizedInput());
    p.clear();
    REQUIRE(p.returnTokenizedInput().empty());
    REQUIRE_THROWS_AS(p.containsElementName("root"), std::logic_error);
}