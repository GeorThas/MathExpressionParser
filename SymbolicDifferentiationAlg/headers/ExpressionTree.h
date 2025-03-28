#pragma once
#include <vector>
#include "Export.h"
#include "Node.h"


class DIFFLIB_API ExpressionTree
{

public:

	ExpressionTree(const std::string& expression);

	~ExpressionTree();

	void writeElemTree();

	Node* getHead(){
		return head; //
	}


private: 
	
	Node* head;

	Node* shuntingYardAlgTree(const std::vector<Token>& tokensList);

	void deleteTree(Node* node);

	void ElemTree(Node* node);

	const std::vector<Token> tokenize(const std::string& expression);

};

