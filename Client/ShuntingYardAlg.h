#pragma once
#include <vector>
#include "Node.h"
 

void shuntingYardArray(const std::vector<Token>& expr, std::vector<Token>& outQueue);

Node* shuntingYardAlgTree(const std::vector<Token>& expr);

double countRPN(const std::vector<Token>& expr);