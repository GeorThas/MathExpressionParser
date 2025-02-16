#include "ExpressionTree.h"
#include "Tokenizator.h"
#include <stack>
#include <iostream>
#include <format> 
#include "Error.h"

/*
Node* ExpressionTree::buildTreeFromRPNTokensListFunc(std::vector<Token>& tokenList, int& tokenListLength) {


	Node* node = nullptr;//

	if (tokenListLength < 0)//tokenList.empty();
		return node;

	 node = new Node(tokenList[tokenListLength--]);

	//std::cout << node->_token.getStr() << " " << tokenListLength << "\n";

	//tokenListLength--;

	if ( ((node->_token.getType() != Token::OPERATOR) && (node->_token.getType() != Token::FUNCTION)))
		return node;


	if (node->_token.getType() == Token::FUNCTION || node->_token.getAsc() == Token::NONE) //��� ���������� ��������� cos/sin � �������� ���������
		node->_rLink = nullptr;
	else if (node->_rLink == nullptr)
		node->_rLink = buildTreeFromRPNTokensListFunc(tokenList, tokenListLength);


	if ( ((node->_token.getType() != Token::OPERATOR) && (node->_token.getType() != Token::FUNCTION)))
		return node;


	if (node->_lLink == nullptr)
		node->_lLink = buildTreeFromRPNTokensListFunc(tokenList, tokenListLength);


	if ( ((node->_token.getType() != Token::OPERATOR) && (node->_token.getType() != Token::FUNCTION)))
		return node;

	/////


};


Node* buildTreeFromRPNTokensListFunc_v2(std::vector<Token>& tokenList, int& tokenListLength) {

	if (tokenListLength < 0 || tokenList.empty()) // �������� �� ������ ������
		return nullptr;

	Node* node = new Node(tokenList[tokenListLength--]); // ������� ���� � ��������� ����� �������

	// ��������� ��� ������
	// ���� ��� �� �������� � �� �������, ���������� ����
	if (node->_token.getType() != Token::OPERATOR && node->_token.getType() != Token::FUNCTION) {
		return node;
	}

	// ��������� ������� ���������
	if (node->_token.getType() == Token::FUNCTION && node->_token.getAsc() == Token::NONE) {
		node->_rLink = nullptr; // ��� ������� ��� ���������� � �������� ���������
	}
	else {
		node->_rLink = buildTreeFromRPNTokensListFunc_v2(tokenList, tokenListLength);
	}

	// ��������� ������ ���������
	node->_lLink = buildTreeFromRPNTokensListFunc_v2(tokenList, tokenListLength);

	return node; // ���������� ����������� ����
}
*/

Node* ExpressionTree::shuntingYardAlgTree(const std::vector<Token>& expression) {


	std::stack<Token> operators;
	std::deque<Node*> values;
	//std::vector<Token> 
	auto fromStackToTree = [&]() {

		Node* right = nullptr, * left = nullptr;


		if (!values.empty()) {
			right = values.front();
			values.pop_front();
		}


		if (!values.empty()) {
			left = values.front();
			values.pop_front();
		}

		Node* opNode = new Node(operators.top());
		operators.pop();

		if (left == nullptr) {
			left = right;
			right = nullptr;
		}

		opNode->_lLink = left;
		opNode->_rLink = right;


		values.push_front(opNode);

		};
	//[&] ��������, ��� ��� ����������, ����������� �� ������

	for (const auto& token : expression)
	{
		switch (token.getType())
		{
			/*case Token::INT_LITERAL:
			case Token::FLOAT_LITERAL:*/
		case Token::NUM_LITERAL:
		case Token::VARIABLE:
			values.push_front(new Node(token));//
			break;
		case Token::L_PARENTHESIS:
		case Token::FUNCTION:
			operators.push(token);
			break;
		case Token::OPERATOR:
			if (!operators.empty())
			{
				while (operators.top().getType() == Token::OPERATOR && ((operators.top().getPrecendance() > token.getPrecendance())
					|| (operators.top().getPrecendance() == token.getPrecendance() && token.getAsc() == Token::LEFT)))
				{

					fromStackToTree();

					if (operators.empty())
						break;
				}
			}

			operators.push(token);
			break;

		case Token::R_PARENTHESIS:
			if (operators.empty())
				throw Error("Non-balanced on paranthesis expression!", Error::Syntax);
			while (operators.top().getType() != Token::L_PARENTHESIS)
			{

				fromStackToTree();

				if (operators.empty())
					throw Error("Non-balanced on paranthesis expression!", Error::Syntax);
			}
			operators.pop();
			if (!operators.empty() && operators.top().getType() == Token::FUNCTION) {

				fromStackToTree();

			}


			break;

			/*case Token::SEPARATOR: // ����� ���������!
				if (stack.empty())
					throw Error("Paranthesis or separator missed!", Error::Syntax);
				while (stack.top().getType() != Token::L_PARENTHESIS)
				{
					fromStackToQueue();
					if (stack.empty())
						throw Error("Paranthesis-unbalanced expression!", Error::Syntax);
				}
				break;*/
		}
	}

	while (!operators.empty())
	{
		if (operators.top().getType() == Token::L_PARENTHESIS)
			throw Error("Paranthesis-unbalanced expression!", Error::Syntax);
		else {
			fromStackToTree();


		}
	}

	return values.front();;
}

void ExpressionTree::deleteTree(Node* node) {

	if (node == nullptr) {
		return;
	}

	deleteTree(node->_lLink);
	deleteTree(node->_rLink);

	//std::cout << node->_token.getStr() << "\n";
	delete node;
	node = nullptr;
};

void ExpressionTree::ElemTree(Node* node) {

	if (node == nullptr) {
		return;
	}

	ElemTree(node->_lLink);
	ElemTree(node->_rLink);

	//std::cout << node->_token.getStr() << "\n";
	std::cout << node->_token.getStr() << "\n";
};

void ExpressionTree::writeElemTree(){
	ExpressionTree::ElemTree(ExpressionTree::head);
}

const std::vector<Token> ExpressionTree::tokenize(const std::string& expression)
{
	std::vector<Token> tokensList;

	State state = Start;

	std::string validOperators = "+-*^/"; // ���������� ��������
	std::string validFunctions = "sincos";

	bool isDigit, isLetter, isOp, isParanth, isPoint, isSep, isLParanth, isRParanth; // ���� ��������

	std::string buffer; //����� ��� ����� � �������
	Token::TokenType bufferTokenType = Token::VARIABLE; // ��� �������� ������

	for (auto& s : expression)
	{
		// ���������� ��� �������
		isDigit = std::isdigit(s); //�����
		isLetter = std::isalpha(s); //�����
		isLParanth = s == '(';
		isRParanth = s == ')';
		isParanth = isLParanth || isRParanth; // ������
		isPoint = s == '.';
		isSep = s == ',';
		isOp = validOperators.find(s) != validOperators.npos; //���������� ��������

		// ���� ��� ������� �����������, ������ ������ � ����������
		if (!(isDigit || isLetter || isParanth || isPoint || isSep || isOp))
			throw Error(std::format("Unknown symbol: {}", s), Error::Syntax);

		// ����� ���������
		switch (state)
		{
		case Start:

			if (isOp || isParanth)
			{
				state = ParenthOperTokenization;
			}
			else if (isDigit)
			{
				state = IntToBuf;
				bufferTokenType = Token::NUM_LITERAL; //020524 !!
			}
			else if (isLetter)
			{
				//state = FuncToBuf;
				state = VarToBuf;
			}
			else if (isPoint || isSep)
			{
				throw Error(std::format("Unexpected symbol: \"{}\"", s), Error::Syntax);
			}

			break;

		case ParenthOperTokenization:

			if (isDigit)
			{
				state = NumToBuf;//IntToBuf;
				bufferTokenType = Token::NUM_LITERAL; //???
			}
			else if (isLetter)
			{
				//state = FuncToBuf;
				state = VarToBuf;
			}
			//else if (isPoint || isSep || isOp)
			//{
			//	throw Error(std::format("Unexpected symbol: \"{}\"", s), Error::Syntax);
			//}

			if (isPoint || isSep /*|| isOp*/)
			{
				throw Error(std::format("Unexpected symbol: \"{}\"", s), Error::Syntax);
			}

			break;
			//v1
		case IntToBuf: // ����� ������ ������, ��������� � ����. �������

			if (isDigit) //020524!!!
				bufferTokenType = Token::NUM_LITERAL;//Token::FLOAT_LITERAL;

			if (isPoint)
				state = NumToBuf;

			if (isParanth || isOp || isSep)
			{
				state = BufTokenization;
			}
			else if (isLetter) //020524!!!
			{
				throw Error(std::format("Unexpected symbol: \"{}\"", s), Error::Syntax);
			}

			break;

			//v2 110524
		case NumToBuf://FloatToBuf:

			if (isDigit) //020524!!!
				bufferTokenType = Token::NUM_LITERAL;//Token::FLOAT_LITERAL;

			if (isParanth || isOp || isSep)
			{
				state = BufTokenization;
			}
			else if (isPoint || isLetter) //020524!!!
			{
				throw Error(std::format("Unexpected symbol: \"{}\"", s), Error::Syntax);
			}

			break;

		case FuncToBuf:

			bufferTokenType = Token::FUNCTION;

			if (isLParanth)
			{
				//bufferTokenType = Token::FUNCTION;
				state = BufTokenization;
			}
			else if (isOp /*|| isRParanth*/ || isSep)
			{
				throw Error(std::format("Unexpected symbol \"{}\"", s), Error::Syntax); //������
			}

			break;

		case VarToBuf:

			bufferTokenType = Token::VARIABLE;

			if (isLParanth)
			{
				//state = FuncToBuf; //
				state = BufTokenization;
				bufferTokenType = Token::FUNCTION;
			}
			else if (isOp || isSep || isParanth)
			{
				state = BufTokenization;
			}
			else if (isPoint)
			{
				throw Error(std::format("Unexpected symbol: \"{}\"", s), Error::Syntax);
			}

			break;

		case BufTokenization:

			if (isParanth || isOp) //v1 110524 ?
			{
				state = ParenthOperTokenization;
			}
			else if (isDigit)
			{
				state = IntToBuf;
				bufferTokenType = Token::NUM_LITERAL;//INT_LITERAL;//
			}
			else if (isLetter)
			{
				//state = FuncToBuf;
				state = VarToBuf;
				bufferTokenType = Token::VARIABLE;//
			}
			else if (isPoint || isSep)
			{
				throw Error(std::format("Unexpected symbol: \"{}\"", s), Error::Syntax);
			}

			break;

		default:
			break;
		}

		auto tokenize_Op_Paranth_Sep = [&]() //������-��������� ����������� ��������, ������ � ������������
		{
			if (isOp)
			{
				// ��������� (-x). ������ ������� ��������� ������������ ��������, ������� ������� � ������
				if (tokensList.size() == 0 || tokensList[tokensList.size() - 1].getType() == Token::L_PARENTHESIS)
				{
					tokensList.push_back({ std::string{s}, Token::OPERATOR, /*Token::RIGHT*/Token::NONE });
				}
				else
				{
					tokensList.push_back({ std::string{s}, Token::OPERATOR, /*Token::LEFT*/ Token::getStrOpAssoc(std::string{s}) } );
				}

			}
			else if (isParanth)
			{
				tokensList.push_back({ std::string{s}, isRParanth ? Token::R_PARENTHESIS : Token::L_PARENTHESIS });
			}
			else if (isSep)/// �� �����
			{
				tokensList.push_back({ std::string{s}, Token::SEPARATOR });
			}
		};

		// ��������
		switch (state)
		{
		case ParenthOperTokenization:
			tokenize_Op_Paranth_Sep();
			break;
		case IntToBuf: //v1 110524
			buffer.push_back(s);
			break;
		case NumToBuf:
			buffer.push_back(s);
			break;
		case VarToBuf:
			buffer.push_back(s);
			break;
		case FuncToBuf:
			buffer.push_back(s);
			break;
		case BufTokenization:
		tokensList.push_back({ buffer, bufferTokenType });
			buffer.clear();
			tokenize_Op_Paranth_Sep();
			break;
		}

	}

	if (!buffer.empty())
	tokensList.push_back({ buffer, bufferTokenType });

	return tokensList;
}

ExpressionTree::ExpressionTree(const std::string& expression) {

	ExpressionTree::head = shuntingYardAlgTree(ExpressionTree::tokenize(expression));
};

ExpressionTree::~ExpressionTree() {

	ExpressionTree::deleteTree(ExpressionTree::head);
};