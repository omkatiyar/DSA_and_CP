#include <iostream>
#include <stack>
#include <cctype> // For isdigit and isalpha functions

bool isValidExpression(const std::string& expression) {
    std::stack<char> s;
    char top;

    for (char ch : expression) {
        switch (ch) {
            // Opening brackets
            case '(':
            case '{':
            case '[':
                s.push(ch);
                break;

            // Closing brackets
            case ')':
            case '}':
            case ']':
                if (s.empty())
                    return false;
                
                top = s.top();
                s.pop();
                if ((ch == ')' && top != '(') ||
                    (ch == '}' && top != '{') ||
                    (ch == ']' && top != '['))
                    return false;
                break;

            // Check for valid characters (numbers, alphabets, or specific operators)
            default:
                if (!isdigit(ch) && !isalpha(ch) && ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '%') {
                    if (ch != ' ' && ch != ',' && ch != '.') // Allow space, comma, and dot for numbers
                        return false;
                }
                break;
        }
    }

    return s.empty(); // True if all brackets are closed
}

int main() {
    std::string expression;
    std::cout << "Enter an expression: ";
    std::getline(std::cin, expression);

    if (isValidExpression(expression))
        std::cout << "The expression is valid.\n";
    else
        std::cout << "The expression is invalid.\n";

    return 0;
}
