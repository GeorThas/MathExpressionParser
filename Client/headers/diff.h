#include "Node.h"
#include "Export.h"

Token zero("0", Token::NUM_LITERAL, Token::NONE);

Token one("1", Token::NUM_LITERAL, Token::NONE);

Token add("+", Token::OPERATOR, Token::LEFT);

Token sub("-", Token::OPERATOR, Token::LEFT);

Token mul("*", Token::OPERATOR, Token::LEFT);

Token power("^", Token::OPERATOR, Token::RIGHT);

Node* DIFFLIB_API diff(Node* node);

Node* Add(Node* n1);

Node* Sub(Node* n1);

Node* Mul(Node* n1);

Node* Div(Node* n1);

Node* Pow(Node* n1);

Node* Num();

Node* Var();

Node* Cos(Node* n1);

Node* Sin(Node* n1);

class DIFFLIB_API AbstractExpresssion{
    public:
    virtual Node* diff() const = 0;

};

class Number : AbstractExpresssion{
    public: 
    Node* diff(){
        return new Node(zero);
    }
};

class Variable : AbstractExpresssion{
    public: 
    Node* diff(){
        
        return new Node(one);
    }
};

class Addition : public AbstractExpresssion{
    Node* diff(Node* n1){

    }
};



