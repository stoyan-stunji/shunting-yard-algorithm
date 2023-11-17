#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <limits>

class Token 
{
    public:
    enum class Type 
    {
        UNKNOWN,
        NUMBER,
        OPERATOR,
        LEFT_BRACKET,
        RIGHT_BRACKET,
    };

    private:
        Type type;
        std::string string;
        int priority;
        bool rightAssociative;
        bool unary;

    public:
        Token()
        {
            this->type = Type::UNKNOWN;
            this->string = " ";
            this->priority = -1;
            this->rightAssociative = false;
            this->unary = false;
        }

        Token(Type type, const std::string& string, const int& priority, 
            const bool& rightAssociative, const bool& unary)
        {
            this->type = type;
            this->string = string;
            this->priority = priority;
            this->rightAssociative = rightAssociative;
            this->unary = unary;
        }

        Token(Type type, const std::string& string)
        {
            this->type = type;
            this->string = string;
            this->priority = -1;
            this->rightAssociative = false;
            this->unary = false;
        }

        const Type getType() { return this->type; };
        const std::string getString() { return this->string; };
        const int getPriority() { return this->priority; };
        const bool getRightAssociativity() { return this->rightAssociative; };
        const bool getUnary() { return this->unary; };

        void setType(const Type& type)
        {
            this->type = type;
        }

        void setString(const std::string& string)
        {
            this->string = string;
        }

        void setPriority(const int priority)
        {
            this->priority = priority;
        }

        void setRightAssociativity(const bool rightAssociative)
        {
            this->rightAssociative = rightAssociative;
        }

        void setUnary(const bool unary)
        {
            this->unary = unary;
        }
};

double power(double base, double exponent) 
{
    double result = 1.0;
    
    while (exponent > 0) 
    {
        result *= base;
        --exponent;
    }
    
    return result;
}

#endif