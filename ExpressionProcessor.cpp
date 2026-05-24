#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <map>

using namespace std;

class ExpressionProcessor {

private:

    string infix;
    vector<string> postfix;
    vector<string> variables;
    map<string, double> values;

    bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    int precedence(char c) {
        if (c == '+' || c == '-') return 1;
        if (c == '*' || c == '/') return 2;
        return 0;
    }

    bool isAlpha(char c) {
        return (c >= 'a' && c <= 'z') ||
               (c >= 'A' && c <= 'Z') ||
               c == '_';
    }

    bool isDigit(char c) {
        return c >= '0' && c <= '9';
    }

    bool isAlphaNumeric(char c) {
        return isAlpha(c) || isDigit(c);
    }

    bool matching(char open, char close) {
        return (open == '(' && close == ')') ||
               (open == '[' && close == ']') ||
               (open == '{' && close == '}');
    }

    bool variableExists(string var) {
        for (int i = 0; i < variables.size(); i++) {
            if (variables[i] == var) return true;
        }
        return false;
    }

    bool validateParentheses() {
        stack<char> s;

        for (int i = 0; i < infix.length(); i++) {
            char c = infix[i];

            if (c == '(' || c == '[' || c == '{')
                s.push(c);

            else if (c == ')' || c == ']' || c == '}') {
                if (s.empty()) return false;

                char top = s.top();
                s.pop();

                if (!matching(top, c)) return false;
            }
        }

        return s.empty();
    }

public:

    int process(string expression) {
        infix = expression;
        if (!validateParentheses()) return 3;
        return 0;
    }
};

int main() {
    string expression;
    getline(cin, expression);

    if (expression.empty()) return 1;

    ExpressionProcessor ep;
    return ep.process(expression);
}