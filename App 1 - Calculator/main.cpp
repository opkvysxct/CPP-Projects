#include <iostream>
#include <cmath>

class Calculator
{
private:
	double actualValue;
	void Init();
	double Calculate(char option, double first, double second);

public:
	Calculator();
	~Calculator();
};

void Calculator::Init()
{
	std::cout << "Calculator Initialized" << std::endl;
	std::cout << "Possible Options are" << std::endl;
	std::cout << std::endl;
	std::cout << "q End execution" << std::endl;
	std::cout << "+ Add" << std::endl;
	std::cout << "- Subtract" << std::endl;
	std::cout << "* Multiply" << std::endl;
	std::cout << "/ Divide" << std::endl;
	std::cout << "^ Power" << std::endl;
	std::cout << std::endl;

	std::cout << "Please enter starting number: ";
	std::cin >> this->actualValue;

	if (std::cin.fail())
	{
		std::cout << "Invalid input" << std::endl;
		return;
	}

	while (true)
	{
		char selectedOption;
		double secondNumber;
		std::cout << "Please enter desired option: ";
		std::cin >> selectedOption;
		if (std::cin.fail())
		{
			std::cout << "Invalid input" << std::endl;
			break;
		}
		if (selectedOption == 'q')
		{
			break;
		}
		std::cout << "Please enter second number: ";
		std::cin >> secondNumber;
		if (std::cin.fail())
		{
			std::cout << "Invalid input" << std::endl;
			break;
		}
		double result = this->Calculate(selectedOption, this->actualValue, secondNumber);
		std::cout << "Result: " << result << std::endl;
		this->actualValue = result;
	}
}

double Calculator::Calculate(char option, double first, double second)
{
	double computedValue;
	switch (option)
	{
	case '+':
		computedValue = first + second;
		break;
	case '-':
		computedValue = first - second;
		break;
	case '*':
		computedValue = first * second;
		break;
	case '/':
		if (second == 0)
		{
			std::cout << "Cannot divide by 0" << std::endl;
			second = 1;
		}
		computedValue = first / second;
		break;
	case '^':
		computedValue = pow(first, second);
		break;
	default:
		std::cout << "Error, option was NOT found" << std::endl;
		computedValue = 0;
		break;
	}
	return computedValue;
}

Calculator::Calculator()
{
	std::cout << "Calculator Created" << std::endl;
	this->Init();
}

Calculator::~Calculator()
{
	std::cout << "Calculator Destroyed" << std::endl;
}

int main(int argc, char const *argv[])
{
	Calculator calc = Calculator();
	return 0;
}