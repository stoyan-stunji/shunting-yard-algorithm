#ifndef IMPLEMENTATION_H
#define IMPLEMENTATION_H

#include "Token.h"

std::deque<Token> tokenize(const std::string& expression) 
{
    std::deque<Token> tokens;

    for(const char* i = expression.c_str(); *i; ++i) 
    {
        if(isblank(*i)) 
        {
            continue;
        } 
        else if(isdigit(*i)) 
        {
            const char* c = i;
            while(isdigit(*i)) 
            {
                ++i;
            }
            std::string string(c, i);

            Token temporary;
            temporary.setString(string);
            temporary.setType(Token::Type::NUMBER);

            tokens.push_back(temporary);
            --i;
        } 
        else 
        {
            Token::Type type = Token::Type::UNKNOWN;
            int precedence = -1;
            bool rightAssociative = false;
            bool unary = false;
            char c = *i;

            switch(c) 
            {
                case '(':
                        type = Token::Type::LEFT_BRACKET;
                        break;
                case ')':
                        type = Token::Type::RIGHT_BRACKET;
                        break;
                case '^':
                        type = Token::Type::OPERATOR;
                        precedence = 4; 
                        rightAssociative = true; 
                        break;
                case '*':  
                        type = Token::Type::OPERATOR;
                        precedence = 3;
                        break;
                case '/':
                        type = Token::Type::OPERATOR;
                        precedence = 3; 
                        break;
                case '+':
                        type = Token::Type::OPERATOR;
                        precedence = 2; 
                        break;
                case '-':
                        // If the current token is '-' and if it is the first token, or preceded by another operator, or by left bracket (&)
                        if(tokens.empty() || tokens.back().getType() == Token::Type::OPERATOR 
                        || tokens.back().getType() == Token::Type::LEFT_BRACKET)                   
                        {                                                                                               
                            // (&) then it is an unary '-'.
                            // '#' is a special operator name for unary '-' and it has the highest priority than any of the infix operators;
                            unary = true;
                            c = '#';
                            type = Token::Type::OPERATOR;
                            precedence = 5;
                        } 
                        else 
                        {
                            // Otherwise, it's binary '-';
                            type = Token::Type::OPERATOR;
                            precedence = 2;
                        }
                        break;
                default:
                        break;
            }
            std::string string(1, c);

            Token temporary;
            temporary.setPriority(precedence);
            temporary.setRightAssociativity(rightAssociative);
            temporary.setString(string);
            temporary.setType(type);
            temporary.setUnary(unary);

            tokens.push_back(temporary);
        }
    }

    return tokens;
}

std::deque<Token> shuntingYard(std::deque<Token>& tokens) 
{
    std::deque<Token> deque;
    std::vector<Token> vector;

    for (std::size_t i = 0; i < tokens.size(); ++i)
    {
        Token token = tokens[i];

        switch (token.getType()) 
        {
            // If the token is a number, add it to the output queue;
            case Token::Type::NUMBER:
                deque.push_back(token);
                break;

            case Token::Type::OPERATOR:
                {
                    Token firstOperator = token;

                    while(!vector.empty())
                    {
                        // The second operator is at the top of "stack" (&&)
                        Token secondOperator = vector.back();
                        if((!firstOperator.getRightAssociativity() 
                            && firstOperator.getPriority() <= secondOperator.getPriority())
                        || (firstOperator.getRightAssociativity() 
                            && firstOperator.getPriority() <  secondOperator.getPriority())
                        ) 
                        {
                            // (&&) then we pop secondOperator off the stack and onto the output deque;
                            vector.pop_back();
                            deque.push_back(secondOperator);
                            continue;
                        }
                        // Otherwise, we exit;
                        break;
                    }

                    // Push firstOperator onto the stack;
                    vector.push_back(firstOperator);
                }
                break;

            case Token::Type::LEFT_BRACKET:
                vector.push_back(token);
                break;

            case Token::Type::RIGHT_BRACKET:
                {
                    bool match = false;
                    // Until the token at the top of the "stack" is a left parenthesis, (&&&)
                    while(! vector.empty() && vector.back().getType() != Token::Type::LEFT_BRACKET) 
                    {
                        // (&&&) pop operators off the stack and onto the output deque;
                        deque.push_back(vector.back());
                        vector.pop_back();
                        match = true;
                    }

                    if(!match && vector.empty()) 
                    {
                        // If the "stack" runs out without finding a left bracket, then there are mismatched parentheses;
                        throw "No right bracket found! //shuntingYard(), case::RIGHT_BRACKET\n";
                    }

                    // Pop the left bracket from the "stack", but do not place it onto the output deque.
                    vector.pop_back();
                }
                break;

            default:
                throw "Error! //shuntingYard(), case::default\n";
            }
        }

        // When there are not any more tokens to read, but there are still operators in the "stack" (&&&&)
        while(!vector.empty()) 
        {
            // (&&&&) if the operator token on the top of the stack is a bracket, then there are mismatched brackets;
            if(vector.back().getType() == Token::Type::LEFT_BRACKET) 
            {
                throw "Mismatched brackets! //shuntingYard(), while(!vector.empty())\n";
            }

            // Pop the operator onto the output deque;
            deque.push_back(std::move(vector.back()));
            vector.pop_back();
    }
    return deque;
}


int evaluate(const std::string& expression) 
{
    std::deque<Token> tokens = tokenize(expression);
    std::deque<Token> deque = shuntingYard(tokens);
    std::vector<int> vector;

    while(!deque.empty()) 
    {
        Token token = deque.front();
        deque.pop_front();

        switch(token.getType()) 
        {
            case Token::Type::NUMBER:
                vector.push_back(std::stoi(token.getString()));
                break;

            case Token::Type::OPERATOR:
                {
                    if(token.getUnary()) 
                    {
                        int right = vector.back(); // Unary operators;
                        vector.pop_back();

                        switch(token.getString()[0]) 
                        {
                            case '#':
                                vector.push_back(-right);
                                break;
                            default:
                                throw "Error! // compute(), switch(token.getString()[0])\n";
                                break;
                        }
                    } 
                    else // Binary operators;
                    {
                        int right = vector.back();
                        vector.pop_back();
                        int left = vector.back();
                        vector.pop_back();

                        switch(token.getString()[0])
                        {
                            case '^':
                                vector.push_back(power(left, right));
                                break;
                            case '*':
                                vector.push_back(left * right);
                                break;
                            case '/':
                                    if(abs(right) <= std::numeric_limits<double>::epsilon())
                                    {
                                        throw "Cannot divide by zero! // compute(), switch(token.getString()[0])\n";
                                    }
                                vector.push_back(left / right);
                                break;
                            case '+':
                                vector.push_back(left + right);
                                break;
                            case '-':
                                vector.push_back(left - right);
                                break;
                            default:
                                throw "Error! // compute(), switch(token.getString()[0])\n";
                                break;
                        }
                    }
                }
                break;
            default:
                throw "Error! // compute(), switch::default\n";
        }
    }
    return vector.back();
}

#endif