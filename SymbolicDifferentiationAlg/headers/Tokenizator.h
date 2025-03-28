#pragma once
#include <vector>
#include <string>
#include "Token.h"

enum State
{
	Start, // s0 
	ParenthOperTokenization, // s1 
	IntToBuf, // s2 
	NumToBuf, // s3 
	FuncToBuf, // s4 
	VarToBuf, // s5 
	BufTokenization // s6 
	//NumToBuf
};


std::string GetTokensList(std::vector<Token>&);

void tokenize(const std::string& expr, std::vector<Token>& tokens);


