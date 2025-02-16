#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Tokenizator.h"
#include "ExpressionTree.h"


int main() {

	std::string str = "cos(-x)^2+4*x";
	
	//std::vector<Token> tokensList;// , RPN_TokenList;

	//tokenize(str, tokensList);

	ExpressionTree exTree(str);

	exTree.writeElemTree();

	system("pause");


	return 0; // Indicate successful completion
}




