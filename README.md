## README

### Compilation Instructions
Compile the program using any standard C++ compiler (e.g., g++):

g++ ExpressionProcessor.cpp -o expr

This will generate an executable file named `expr`.

---

### Usage Instructions
Run the program as follows:

On Windows:
expr.exe

On Linux / Mac:
./expr

After running the program:
- Enter a valid infix mathematical expression (e.g., a + b * (c - d))
- If the expression contains variables, the program will ask for their values
- The program will then:
  - Convert the expression into postfix form
  - Evaluate the expression
  - Display the postfix expression and final result
