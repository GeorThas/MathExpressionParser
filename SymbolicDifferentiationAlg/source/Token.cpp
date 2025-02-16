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

	}
}

Token::OperationAssociativity Token::getStrOpAssoc(std::string opName)
{
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