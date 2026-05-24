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

    if (!infixToPostfix()) return 1;

    return 0;
}

    bool infixToPostfix() {

    stack<char> s;

    for (int i = 0; i < infix.length(); i++) {

        char c = infix[i];

        if (c == ' ') continue;

        if (isDigit(c)) {
            string num;

            while (i < infix.length() && (isDigit(infix[i]) || infix[i] == '.')) {
                num += infix[i];
                i++;
            }
            i--;
            postfix.push_back(num);
        }

        else if (isAlpha(c)) {
            string var;

            while (i < infix.length() && isAlphaNumeric(infix[i])) {
                var += infix[i];
                i++;
            }
            i--;

            postfix.push_back(var);

            if (!variableExists(var))
                variables.push_back(var);
        }

        else if (c == '(' || c == '[' || c == '{') {
            s.push(c);
        }

        else if (c == ')' || c == ']' || c == '}') {

            while (!s.empty() && s.top() != '(' && s.top() != '[' && s.top() != '{') {
                string op(1, s.top());
                postfix.push_back(op);
                s.pop();
            }

            if (!s.empty()) s.pop();
        }

        else if (isOperator(c)) {

            while (!s.empty() && isOperator(s.top()) &&
                   precedence(s.top()) >= precedence(c)) {

                string op(1, s.top());
                postfix.push_back(op);
                s.pop();
            }

            s.push(c);
        }
    }

    while (!s.empty()) {
        string op(1, s.top());
        postfix.push_back(op);
        s.pop();
    }

    return true;
}
   
};

int main() {
    string expression;
    getline(cin, expression);

    if (expression.empty()) return 1;

    ExpressionProcessor ep;
    return ep.process(expression);
}