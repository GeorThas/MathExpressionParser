#pragma once
#include "Token.h"


class DIFFLIB_API Node {

public:

	Token _token;
	Node* _lLink;
	Node* _rLink;

public:
	Node(const Token& token) : _token(token) {

	}

};
