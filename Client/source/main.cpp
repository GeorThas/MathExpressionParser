#pragma once
#include <string>
#include "ExpressionTree.h"


int main() {

	std::string str = "cos(-x)^2+4*x";
	
	ExpressionTree exTree(str);

	exTree.writeElemTree();

	system("pause");


	return 0; // Indicate successful completion
}
