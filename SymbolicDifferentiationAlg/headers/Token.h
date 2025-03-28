#pragma once

#include <string>
#include "Export.h"




class DIFFLIB_API Token
{
	public:

	enum TokenType
	{
		OPERATOR,      // �������/�������� ��������
		L_PARENTHESIS, // ����������� ������
		R_PARENTHESIS, // ����������� ������
		NUM_LITERAL,   // �����
		FUNCTION,      // �������
		SEPARATOR,      // ����������� ���������� �������
		VARIABLE        // ����������
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


