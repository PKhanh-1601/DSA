//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Part 2 - Homework 5
//Notes or Remarks:

#include <iostream>
#include <cctype>
#include <memory>
#include <stdexcept>
#include <vector>

using namespace std;
enum class TokenType
{
    NUMBER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LPAREN,
    RPAREN,
    END
};

struct Token
{
    TokenType type;
    double value;
    Token(TokenType type) : type(type), value(0) {}
    Token(TokenType type, double value) : type(type), value(value) {}
};

class Tokenizer
{
private:
    string expression;
    size_t pos;
    Token currentToken;

public:
    Tokenizer(const string &expr) : expression(expr), pos(0), currentToken(TokenType::END)
    {
        advance();
    }
    void advance()
    {
        while (pos < expression.length() && isspace(expression[pos]))
        {
            pos++;
        }

        if (pos >= expression.length())
        {
            currentToken = Token(TokenType::END);
            return;
        }

        char currentChar = expression[pos];

        if (isdigit(currentChar) || currentChar == '.')
        {
            size_t startPos = pos;
            bool hasDecimal = false;
            while (pos < expression.length() && (isdigit(expression[pos]) || expression[pos] == '.'))
            {
                if (expression[pos] == '.')
                {
                    if (hasDecimal)
                    {
                        throw runtime_error("Invalid number format with multiple decimals.");
                    }
                    hasDecimal = true;
                }
                pos++;
            }
            double number = stod(expression.substr(startPos, pos - startPos));
            currentToken = Token(TokenType::NUMBER, number);
            return;
        }
        switch (currentChar)
        {
        case '+':
            currentToken = Token(TokenType::PLUS);
            break;
        case '-':
            currentToken = Token(TokenType::MINUS);
            break;
        case '*':
            currentToken = Token(TokenType::MULTIPLY);
            break;
        case '/':
            currentToken = Token(TokenType::DIVIDE);
            break;
        case '(':
            currentToken = Token(TokenType::LPAREN);
            break;
        case ')':
            currentToken = Token(TokenType::RPAREN);
            break;
        default:
            throw runtime_error(string("Unknown character: ") + currentChar);
        }
        pos++;
    }
    Token getCurrentToken() const
    {
        return currentToken;
    }
};

class ASTNode
{
public:
    virtual ~ASTNode() {}
    virtual double evaluate() const = 0;
};

class NumberNode : public ASTNode
{
public:
    double value;

    NumberNode(double val) : value(val) {}

    double evaluate() const override
    {
        return value;
    }
};

class BinaryOpNode : public ASTNode
{
public:
    char op;
    unique_ptr<ASTNode> left;
    unique_ptr<ASTNode> right;

    BinaryOpNode(char oper, unique_ptr<ASTNode> lhs, unique_ptr<ASTNode> rhs)
        : op(oper), left(move(lhs)), right(move(rhs)) {}

    double evaluate() const override
    {
        double leftVal = left->evaluate();
        double rightVal = right->evaluate();

        switch (op)
        {
        case '+':
            return leftVal + rightVal;
        case '-':
            return leftVal - rightVal;
        case '*':
            return leftVal * rightVal;
        case '/':
            if (rightVal == 0)
            {
                throw runtime_error("Division by zero.");
            }
            return leftVal / rightVal;
        default:
            throw runtime_error(string("Unknown operator: ") + op);
        }
    }
};

class Parser
{
private:
    Tokenizer tokenizer;
    unique_ptr<ASTNode> parseExpression()
    {
        unique_ptr<ASTNode> node = parseTerm();

        while (tokenizer.getCurrentToken().type == TokenType::PLUS ||
               tokenizer.getCurrentToken().type == TokenType::MINUS)
        {
            Token token = tokenizer.getCurrentToken();
            tokenizer.advance();
            unique_ptr<ASTNode> right = parseTerm();
            if (token.type == TokenType::PLUS)
            {
                node = make_unique<BinaryOpNode>('+', move(node), move(right));
            }
            else
            {
                node = make_unique<BinaryOpNode>('-', move(node), move(right));
            }
        }
        return node;
    }

    unique_ptr<ASTNode> parseTerm()
    {
        unique_ptr<ASTNode> node = parseFactor();

        while (tokenizer.getCurrentToken().type == TokenType::MULTIPLY ||
               tokenizer.getCurrentToken().type == TokenType::DIVIDE)
        {
            Token token = tokenizer.getCurrentToken();
            tokenizer.advance();
            unique_ptr<ASTNode> right = parseFactor();
            if (token.type == TokenType::MULTIPLY)
            {
                node = make_unique<BinaryOpNode>('*', move(node), move(right));
            }
            else
            {
                node = make_unique<BinaryOpNode>('/', move(node), move(right));
            }
        }
        return node;
    }

    unique_ptr<ASTNode> parseFactor()
    {
        Token token = tokenizer.getCurrentToken();

        if (token.type == TokenType::NUMBER)
        {
            tokenizer.advance();
            return make_unique<NumberNode>(token.value);
        }
        else if (token.type == TokenType::LPAREN)
        {
            tokenizer.advance();
            unique_ptr<ASTNode> node = parseExpression();
            if (tokenizer.getCurrentToken().type != TokenType::RPAREN)
            {
                throw runtime_error("Expected closing parenthesis.");
            }
            tokenizer.advance();
            return node;
        }
        else if (token.type == TokenType::MINUS)
        {
            tokenizer.advance();
            unique_ptr<ASTNode> node = parseFactor();
            return make_unique<BinaryOpNode>('-', make_unique<NumberNode>(0), move(node));
        }
        else
        {
            throw runtime_error("Invalid syntax.");
        }
    }

public:
    Parser(const string &expr) : tokenizer(expr) {}
    unique_ptr<ASTNode> parse()
    {
        unique_ptr<ASTNode> root = parseExpression();
        if (tokenizer.getCurrentToken().type != TokenType::END)
        {
            throw runtime_error("Unexpected characters at end of expression.");
        }
        return root;
    }
};

int main()
{
    cout << "=== Infix Expression Parser and Evaluator ===\n";
    cout << "Supported operations: +, -, *, /, parentheses\n";
    cout << "Enter 'exit' to quit.\n\n";

    while (true)
    {
        cout << "Enter expression: ";
        string input;
        getline(cin, input);

        if (input.empty())
        {
            continue;
        }

        if (input == "exit")
        {
            break;
        }

        try
        {
            Parser parser(input);
            unique_ptr<ASTNode> ast = parser.parse();
            double result = ast->evaluate();
            cout << "Result: " << result << "\n\n";
        }
        catch (const exception &ex)
        {
            cout << "Error: " << ex.what() << "\n\n";
        }
    }

    cout << "Goodbye!\n";
    return 0;
}

