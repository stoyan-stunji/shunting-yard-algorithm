Shunting Yard Algorithm

Introduction:
> The shunting yard algorithm is a method for parsing arithmetical or logical expressions, or a combination of both, specified in infix notation. It can produce either a postfix notation string, also known as Reverse Polish notation (RPN), or an abstract syntax tree (AST). The algorithm was invented by Edsger Dijkstra and named the "shunting yard" algorithm because its operation resembles that of a railroad shunting yard. 

How It Works:
> The shunting yard algorithm is stack-based (like the evaluation of RPN). Infix expressions are the form of mathematical notation most people are used to, for instance "3 + 4" or "3 + 4 × (2 − 1)". For the conversion there are two text variables (strings), the input and the output. There is also a stack that holds operators not yet added to the output queue. To convert, the program reads each symbol in order and does something based on that symbol. The result for the above examples would be (in RPN) "3 4 +" and "3 4 2 1 − × +", respectively.
> The shunting yard algorithm will correctly parse all valid infix expressions, but does not reject all invalid expressions. For example, "1 2 +" is not a valid infix expression, but would be parsed as "1 + 2". The algorithm can however reject expressions with mismatched parentheses.

Example:
> 1. Input: "3 + 4";
> 2. Push "3" to the output queue (whenever a number is read it is pushed to the output);
> 3. Push "+"  onto the operator stack;
> 4. Push "4" to the output queue;
> 5. After reading the expression, pop the operators off the stack and add them to the output;
>    In this case there is only one, "+";
> 6. Output: "3 4 +";
>
> All numbers are pushed to the output when they are read.
> At the end of reading the expression, pop all operators off the stack and onto the output.

Inspiration:
> https://gist.github.com/t-mat/b9f681b7591cdae712f6

General Information From:
> https://en.wikipedia.org/wiki/Shunting_yard_algorithm
