#pragma once
#include <vector>
#include "Node.h"

#ifndef MYCLASS_H
#define MYCLASS_H


#ifdef MYCLASS_EXPORTS
#define MYCLASS_API __declspec(dllexport)
#else
#define MYCLASS_API __declspec(dllimport)
#endif


class MYCLASS_API ExpressionTree
{

public:

	ExpressionTree(const std::string& expression);

	~ExpressionTree();

	void writeElemTree();


private: 
	
	Node* head;

	//std::vector<Token> tokensList;

	//Node* buildTreeFromRPNTokensListFunc(std::vector<Token>& tokenList, int& tokenListLength);

	Node* shuntingYardAlgTree(const std::vector<Token>& tokensList);

	void deleteTree(Node* node);

	void ElemTree(Node* node);

	const std::vector<Token> tokenize(const std::string& expression);

};

#endif