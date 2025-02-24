#pragma once

#include <string>

class Token
{
	public:

	enum TokenType
	{
		OPERATOR,      // унарный/бинарный оператор
		L_PARENTHESIS, // открывающая скобка
		R_PARENTHESIS, // закрывающая скобка
		NUM_LITERAL,   // число
		FUNCTION,      // функция
		SEPARATOR,      // разделитель аргументов функции
		VARIABLE        // переменная
	};

	enum OperationAssociativity
	{
		NONE,
		RIGHT,
		LEFT
	};




	Token(std::string tokenName, TokenType tokenType, OperationAssociativity opAssoc = NONE);

	int getPrecendance() const;

	static OperationAssociativity getStrOpAssoc(std::string tokenName); //

	//getters
	const TokenType& getType() const
	{
		return _tokenType;
	}

	const OperationAssociativity& getAsc() const
	{
		return _opAssoc;
	}

	const std::string& getStr() const
	{
		return _tokenName;
	}

	private:
	TokenType _tokenType;
	OperationAssociativity _opAssoc;
	std::string _tokenName;

	public:

	void setStr(std::string tokenName)
	{
		_tokenName = tokenName;
	}
};

