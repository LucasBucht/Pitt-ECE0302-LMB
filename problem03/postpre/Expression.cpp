#include <string>
#include <cctype> // for isalpha
#include <stdexcept>

#include "Expression.hpp"

/* Default constructor */
Expression::Expression() 
{}

/* Public member functions */
void Expression::setFromPrefix(const std::string &pre)
{
   if (!isPre(pre))
        throw std::invalid_argument("Invalid prefix expression: " + pre);
    prefix_ = pre;
    postfix_.clear();
    prefixToPostfix(pre, postfix_);

}

void Expression::setFromPostfix(const std::string &post)
{
  if (!isPost(post))
        throw std::invalid_argument("Invalid postfix expression: " + post);
    postfix_ = post;
    prefix_.clear();
    postfixToPrefix(post, prefix_);

}

std::string Expression::getPrefix() const
{
    return prefix_;
}

std::string Expression::getPostfix() const
{
    return postfix_;
}

/* Private member functions */
void Expression::prefixToPostfix(const std::string &prefix, std::string &postfix) const {
  // from textbook section 6.3.3
  int end1, end2;
  char first_char = prefix[0];
  if(isOperator(first_char)) {
    // recursively parse expression
    end1 = endPre(prefix,1);
    end2 = endPre(prefix,end1+1);
    // operand/subexpression
    prefixToPostfix(prefix.substr(1,end1), postfix);
    // operand/subexpression
    prefixToPostfix(prefix.substr(end1+1,end2-end1), postfix);
    // operator
    postfix += first_char;
  } else {
    // operand
    postfix += first_char;
  }
}

void Expression::postfixToPrefix(const std::string &postfix, std::string &prefix) const {

  int last = (int)postfix.size() - 1;
    char last_char = postfix[last];
    if (isOperator(last_char)) {
        // find boundary of the two sub-expressions
        int end2 = endPost(postfix, last - 1);      
        // end of second subexpr
        int end1 = endPost(postfix, end2 - 1);       
        // end of first subexpr

        // first subexpr: [end1 .. end2-1), second subexpr: [end2 .. last-1]
        std::string sub1 = postfix.substr(end1, end2 - end1);
        std::string sub2 = postfix.substr(end2, last - end2);

        prefix += last_char;
        postfixToPrefix(sub1, prefix);
        postfixToPrefix(sub2, prefix);
    } else {
        prefix += last_char;
    }

}


