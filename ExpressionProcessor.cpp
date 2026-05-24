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

       return c == '+' ||
           c == '-' ||
           c == '*' ||
           c == '/';
   }

   int precedence(char c) {

       if (c == '+' || c == '-') {
           return 1;
       }

       if (c == '*' || c == '/') {
           return 2;
       }

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


   bool variableExists(string var) {

       for (int i = 0; i < variables.size(); i++) {

           if (variables[i] == var) {
               return true;
           }
       }

       return false;
   }

   
   bool matching(char open, char close) {

       return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
   }

   
   bool validateParentheses() {

       stack<char> s;

       for (int i = 0; i < infix.length(); i++) {

           char c = infix[i];

           if (c == '(' || c == '[' || c == '{') {

               s.push(c);
           }

           else if (c == ')' || c == ']' || c == '}') {

               if (s.empty()) {

                   cerr << "Error: Unmatched closing parenthesis" << endl;
                   return false;
               }

               char top = s.top();
               s.pop();

               if (!matching(top, c)) {

                   cerr << "Error: Mismatched parentheses" << endl;
                   return false;
               }
           }
       }

       if (!s.empty()) {

           cerr << "Error: Unmatched opening parenthesis" << endl;
           return false;
       }

       return true;
   }

   
   bool infixToPostfix() {

       stack<char> s;

       for (int i = 0; i < infix.length(); i++) {

           char c = infix[i];

    
           if (c == ' ' || c == '\t') {
               continue;
           }


           if (isDigit(c)) {

               string num;

               while (i < infix.length() &&
                   (isDigit(infix[i]) || infix[i] == '.')) {

                   num += infix[i];
                   i++;
               }

               i--;

               if (num == ".") {

                   cerr << "Error: Invalid number format" << endl;
                   return false;
               }

               postfix.push_back(num);
           }

    
           else if (isAlpha(c)) {

               string var;

               while (i < infix.length() &&
                   (isAlphaNumeric(infix[i]) || infix[i] == '_')) {

                   var += infix[i];
                   i++;
               }

               i--;

               postfix.push_back(var);

               if (!variableExists(var)) {
                   variables.push_back(var);
               }
           }

        
           else if (c == '(' || c == '[' || c == '{') {

               s.push(c);
           }

           
           else if (c == ')' || c == ']' || c == '}') {

               while (!s.empty() &&
                   s.top() != '(' &&
                   s.top() != '[' &&
                   s.top() != '{') {

                   string op(1, s.top());
                   postfix.push_back(op);
                   s.pop();
               }

               if (s.empty()) {

                   cerr << "Error: Mismatched parentheses" << endl;
                   return false;
               }

               s.pop();
           }

        
           else if (isOperator(c)) {

               
               int j = i - 1;

               while (j >= 0 &&
                   (infix[j] == ' ' || infix[j] == '\t')) {

                   j--;
               }

               if (j >= 0 && isOperator(infix[j])) {

                   cerr << "Error: Consecutive operators" << endl;
                   return false;
               }

               while (!s.empty() &&
                   isOperator(s.top()) &&
                   precedence(s.top()) >= precedence(c)) {

                   string op(1, s.top());
                   postfix.push_back(op);
                   s.pop();
               }

               s.push(c);
           }

           else {

               cerr << "Error: Invalid character" << endl;
               return false;
           }
       }

       
       while (!s.empty()) {

           if (s.top() == '(' ||
               s.top() == '[' ||
               s.top() == '{') {

               cerr << "Error: Mismatched parentheses" << endl;
               return false;
           }

           string op(1, s.top());
           postfix.push_back(op);

           s.pop();
       }

       return true;
   }

   
   void inputVariables() {

       for (int i = 0; i < variables.size(); i++) {

           double val;

           cerr << "Enter value for "
               << variables[i]
               << ": ";

           cin >> val;

           values[variables[i]] = val;
       }
   }


   void printPostfix() {

       for (int i = 0; i < postfix.size(); i++) {

           cout << postfix[i];

           if (i != postfix.size() - 1) {
               cout << " ";
           }
       }

       cout << endl;
   }

   
   bool evaluate(double& result) {

       stack<double> s;

       for (int i = 0; i < postfix.size(); i++) {

           string token = postfix[i];

        
           if (token == "+" ||
               token == "-" ||
               token == "*" ||
               token == "/") {

               if (s.size() < 2) {

                   cerr << "Error: Invalid expression" << endl;
                   return false;
               }

               double b = s.top();
               s.pop();

               double a = s.top();
               s.pop();

               double ans;

               if (token == "+") {
                   ans = a + b;
               }

               else if (token == "-") {
                   ans = a - b;
               }

               else if (token == "*") {
                   ans = a * b;
               }

               else {

                   if (b == 0) {

                       cerr << "Error: Division by zero" << endl;
                       return false;
                   }

                   ans = a / b;
               }

               s.push(ans);
           }

        
           else if (isDigit(token[0])) {

               try {

                   s.push(stod(token));
               }

               catch (...) {

                   cerr << "Error: Invalid number" << endl;
                   return false;
               }
           }

           
           else {

               if (values.find(token) == values.end()) {

                   cerr << "Error: Variable value missing" << endl;
                   return false;
               }

               s.push(values[token]);
           }
       }

       if (s.size() != 1) {

           cerr << "Error: Invalid expression" << endl;
           return false;
       }

       result = s.top();

       return true;
   }

public:

   int process(string expression) {

       infix = expression;

    
       if (!validateParentheses()) {
           return 3;
       }

       
       if (!infixToPostfix()) {
           return 1;
       }

    
       inputVariables();


       printPostfix();


       double result;

       if (!evaluate(result)) {
           return 2;
       }


       cout << result << endl;

       return 0;
   }
};

int main() {

   string expression;

   getline(cin, expression);

   if (expression.empty()) {

       cerr << "Error: Empty input" << endl;
       return 1;
   }

   ExpressionProcessor ep;

   return ep.process(expression);
}