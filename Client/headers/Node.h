#pragma once
#include "Token.h"


class Node {

public:

	Token _token;
	Node* _lLink;
	Node* _rLink;

public:
	Node(const Token& token) : _token(token) {

	}

};
