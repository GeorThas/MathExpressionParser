#include "diff.h"

Node* Num(){
    return new Node(zero);
}

Node* Var(){
    return new Node(one);
}

Node* Add(Node* node){

    Node* head = new Node(add);

    head->_lLink = diff(node->_lLink);
    head->_rLink = diff(node->_rLink);

    return head;
}

Node* Mul(Node* node) {
    // n1` * n2 + n1 * n2`
    Node* lbuf, * rbuf;

    Node* head = new Node(add);

    lbuf = new Node(mul);
    lbuf->_lLink = diff(node->_lLink);
    lbuf->_rLink = new Node(*(node->_rLink)); //

    rbuf = new Node(mul);
    rbuf->_lLink = new Node(*(node->_lLink));
    rbuf->_rLink = diff(node->_rLink);

    head->_lLink = lbuf;
    head->_rLink = rbuf;

    return head;
}

Node* Pow(Node* node){

    Node* head = new Node(mul);

    head->_lLink = node->_rLink;

    Node* rBufPow = new Node(power);

    rBufPow->_lLink = node->_lLink;

    Node* lBufSub = new Node(sub);

    lBufSub->_lLink = node->_rLink;

    lBufSub->_rLink = new Node(one);

    rBufPow->_rLink = lBufSub;

    head->_rLink = rBufPow;

    return head;

}

//Node* Mul(Node*)

Node* diff(Node* node) {

    Node* res = nullptr;
    char n = 0;

    switch (node->_token.getType()) {

    case (Token::NUM_LITERAL):
        res = Num();
        break;

    case (Token::VARIABLE):
        res = Var();
        break;

    case (Token::OPERATOR):

        n = node->_token.getStr()[0];
        switch (n) {

        case '+': //res = Add(node);
            break;
        case '-': //res = Sub(node);
            break;
        case '*': res = Mul(node);
            break;
        case '/': //res = Div(node);
            break;
        case '^': //res = Pow(node);
            break;
            //передавать не ветви, а саму ячейку
        }

        break;

    case (Token::FUNCTION):

        if (node->_token.getStr() == "cos"){}
            //res = Cos(node);
        else if (node->_token.getStr() == "sin"){}
            //res = Sin(node);

        break;
    }

    return res;
}