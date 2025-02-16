#include <map>
#include <stdexcept>
#include <format>
#include "Error.h"
#include "Token.h"


Token::Token(std::string tokenName, TokenType tokenType, OperationAssociativity opAssoc) : _tokenType{ tokenType }, _tokenName{ tokenName } //initialisation
{

	if (tokenType == OPERATOR && opAssoc == NONE)
	{
		//throw std::logic_error("Associativity required!");
	}
	else if (tokenType != OPERATOR && opAssoc != NONE)
	{
		throw std::logic_error("Non-operator token can't have an associativity!");
	}

	_opAssoc = opAssoc;


	
}


static const std::map<std::string, int> leftAssociativeOperatons=
{
		{"+", 2},
		{"-", 2},
		{"/", 3},
		{"*", 3}
	//	{"^", 5}
};

static const std::map<std::string, int> rightAssociativeOperatons =
{
	{"^", 5}
};

static const std::map<std::string, int> noneAssociativeOperatons =
{
	{"-", 4}
};

int Token::getPrecendance() const
{
	//static std::map<std::string, int> leftAssociativeOperatons = //Left-associative operations
	//{
	//	{"+", 2},
	//	{"-", 2},
	//	{"/", 3},
	//	{"*", 3}
	//	//{"^", 5}
	//};


	//static std::map<std::string, int> rightAssociativeOperatons = //Right-associative operations
	//{
	//	//{"-", 4}, // unary negation
	//	{"^", 5}
	//};

	//static std::map<std::string, int> noneAssociativeOperatons = //Right-associative operations
	//{
	//	{"-", 4}, // unary negation
	//	//{"^", 5}
	//};

	switch (_opAssoc)
	{
		case LEFT:
		
			if (leftAssociativeOperatons.count(_tokenName)) //contains()
			{
				return leftAssociativeOperatons.at(_tokenName) /*[_tokenName]*/;
			}
			else
			{
				throw Error("Unknown Operator!", Error::Syntax);
			}
			break;

		case RIGHT:

			if (rightAssociativeOperatons.count(_tokenName)) //contains()
			{
				return rightAssociativeOperatons.at(_tokenName);
			}
			else
			{
				throw Error("Unknown Operator!", Error::Syntax);
			}
			break;

		case NONE:

			if (noneAssociativeOperatons.count(_tokenName)) //contains()
			{
				return noneAssociativeOperatons.at(_tokenName);
			}
			else
			{
				throw Error("Unknown Operator!", Error::Syntax);
			}
			break;

			//throw std::logic_error(std::format("Token \"{}\" is not an operatator, impossible.", _tokenName));
			//break;
	}
}

Token::OperationAssociativity Token::getStrOpAssoc(std::string opName){

	//static std::map<std::string, int> leftAssociativeOperatons = //Left-associative operations
	//{
	//	{"+", 2},
	//	{"-", 2},
	//	{"/", 3},
	//	{"*", 3}
	//	//{"^", 5}
	//};


	//static std::map<std::string, int> rightAssociativeOperatons = //Right-associative operations
	//{
	//	{"-", 4}, // unary negation
	//	{"^", 5}
	//};


	if (rightAssociativeOperatons.count(opName)) //contains()
	{
		return RIGHT;
	}
	else if (leftAssociativeOperatons.count(opName))
	{
		return LEFT;
	}
	else
		return NONE;

}