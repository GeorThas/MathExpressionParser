#include "ShuntingYardAlg.h"
#include "Error.h"
#include "Node.h"
#include <iostream>
#include <stack>
#include <cmath>
#include <tuple>
#include <format>

void shuntingYardArray(const std::vector<Token>& expr, std::vector<Token>& outQueue)
{
	std::stack<Token> stack;
	auto fromStackToQueue = [&]() { outQueue.push_back(stack.top()); stack.pop(); }; 

	for (const auto& token : expr) 
	{
		switch (token.getType())
		{
			/*case Token::INT_LITERAL:
			case Token::FLOAT_LITERAL:*/
		case Token::NUM_LITERAL:
		case Token::VARIABLE:
			outQueue.push_back(token);
			break;
		case Token::L_PARENTHESIS:
		case Token::FUNCTION:
			stack.push(token);
			break;
		case Token::OPERATOR:
			if (!stack.empty())
			{
				while (stack.top().getType() == Token::OPERATOR && ((stack.top().getPrecendance() > token.getPrecendance())
					|| (stack.top().getPrecendance() == token.getPrecendance() && token.getAsc() == Token::LEFT)))
				{
					fromStackToQueue();
					if (stack.empty())
						break;
				}
			}
			stack.push(token);
			break;

		case Token::R_PARENTHESIS:
			if (stack.empty())
				throw Error("Non-balanced on paranthesis expression!", Error::Syntax);
			while (stack.top().getType() != Token::L_PARENTHESIS)
			{
				fromStackToQueue();
				if (stack.empty())
					throw Error("Non-balanced on paranthesis expression!", Error::Syntax);
			}
			stack.pop();
			if (!stack.empty() && stack.top().getType() == Token::FUNCTION)
				fromStackToQueue();
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

	while (!stack.empty())
	{
		if (stack.top().getType() == Token::L_PARENTHESIS)
			throw Error("Paranthesis-unbalanced expression!", Error::Syntax);
		else
			fromStackToQueue();
	}
}

Node* shuntingYardAlgTree(const std::vector<Token>& expr) {


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

	for (const auto& token : expr)
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

/*
double countRPN(const std::vector<Token>& expr)
{
	std::stack<double> stack;

	auto getOneToken = [&]() // ������� 1 �����
	{
		if (stack.empty())
			throw Error("Not enough arguments in function!", Error::Syntax);


		double x = stack.top();
		stack.pop();
		return x;
	};

	auto getTwoTokens = [&]() // ������� 2 ������
	{
		double x = getOneToken(),
		y = getOneToken();
		return std::tuple{ y,x };
	};

	auto checkedDivision = [&](double a, double b) // �������� �� ������������
	{
		if (b == 0.f)
			throw Error("Division by zero", Error::Math);
		return a / b;
	};

	double res;
	for (auto& token : expr)
	{
		const std::string& str = token.getStr();
		switch (token.getType())
		{
		/*case Token::INT_LITERAL:

			stack.push(std::stoi(str));
			break;

		case Token::FLOAT_LITERAL:

			stack.push(std::stof(str));
			break;
		case Token::NUM_LITERAL:

			stack.push(std::stof(str));
			break;
		case Token::VARIABLE:

			//stack.push(str);
			break;

		case Token::OPERATOR:


			switch (token.getAsc())
			{
			case Token::LEFT:
			{
				auto [a, b] = getTwoTokens();
				if (str == "+")
					res = a + b;
				else if (str == "-")
					res = a - b;
				else if (str == "*")
					res = a * b;
				else if (str == "/")
					res = checkedDivision(a, b);
				else if (str == "^")
					res = std::pow(a, b);
				else
					throw Error("Unknown operator!", Error::Syntax);
				break;

			}
			case Token::RIGHT: // � �������� �������� ������ ���� ������������������ ��������
			{
				auto a = getOneToken();
				if (str == "-")
					res = -a;
				else
					throw Error("Unknown operator!", Error::Syntax);

				break;

			}
			case Token::NONE:
				throw std::logic_error("Operator must have associativity!");
				break;

			}


			stack.push(res);
			break;

		case Token::FUNCTION:

			if (str == "log")
			{
				auto [a, b] = getTwoTokens();
				if (a <= 0.f || a == 1.0f)
					throw Error(std::format("log(a,x): not defined for a = {}", a), Error::Math);
				if (b <= 0.f)
					throw Error("log(a,x): out of function's domain", Error::Math);

				res = std::log(b) / std::log(a);
			}
			else if (str == "log2")
			{
				auto a = getOneToken();
				if (a <= 0.f)
					throw Error("log2(x): out of function's domain", Error::Math);

				res = std::log2(a);
			}
			else if (str == "ln")
			{
				auto a = getOneToken();
				if (a <= 0.f)
					throw Error("ln(x): out of function's domain", Error::Math);

				res = std::log(a);
			}
			else if (str == "lg")
			{
				auto a = getOneToken();
				if (a <= 0.f)
					throw Error("lg(x): out of function's domain", Error::Math);

				res = std::log10(a);
			}
			else if (str == "max")
			{
				auto [a, b] = getTwoTokens();
				res = a > b ? a : b;
			}
			else if (str == "min")
			{
				auto [a, b] = getTwoTokens();
				res = a < b ? a : b;
			}
			else if (str == "sqrt")
			{
				auto a = getOneToken();
				res = std::sqrt(a);
			}
			else if (str == "sin")
			{
				auto a = getOneToken();
				res = std::sin(a);
			}
			else if (str == "cos")
			{
				auto a = getOneToken();
				res = std::cos(a);
			}
			else if (str == "tg")
			{
				auto a = getOneToken();
				res = std::tan(a);
			}
			else if (str == "ctg")
			{
				auto a = getOneToken();
				res = 1 / std::tan(a);
			}
			else
				throw Error("Unknown function!", Error::Syntax);


			stack.push(res);
			break;

		default:
			break;
		}
	}
	return stack.top();
}*/