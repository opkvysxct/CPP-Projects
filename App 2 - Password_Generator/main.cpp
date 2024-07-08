// VYSX 2024
#include <iostream>
#include <map>
#include <string>
#include <random>
#include <vector>

enum OptionEnum
{
	Special,
	Number,
	Big,
	Small
};

struct Option
{
	bool realValue;
	std::string displayText;
	char inputValue;
	OptionEnum correspondingEnum;
};

class PasswordGenerator
{
private:
	void InitConfig();
	void CreatePassword();
	char AddChar(OptionEnum option);
	std::default_random_engine randomGenerator;
	std::map<std::string, Option> options;
	std::vector<OptionEnum> availableOptions;
	int passLength;
	int asciiSpecial[8] = {
		33,
		35,
		36,
		37,
		38,
		47,
		63,
		64,
	};
	int asciiNums[2] = {
		48,
		57};
	int asciiBig[2] = {
		65,
		90};
	int asciiSmall[2] = {
		97,
		122};

public:
	PasswordGenerator(/* args */);
	~PasswordGenerator();
};

void PasswordGenerator::InitConfig() // Setting up config
{
	std::cout << "Please enter password length: ";
	std::cin >> this->passLength;
	if (std::cin.fail())
	{
		std::cout << "Invalid input" << std::endl;
		return;
	}

	for (auto option = this->options.begin(); option != this->options.end(); ++option)
	{
		std::cout << option->first << " characters? [Y/N] : ";
		std::cin >> option->second.inputValue;
		if (std::cin.fail())
		{
			std::cout << "Invalid input" << std::endl;
			return;
		}
		else if (option->second.inputValue == 'Y' || option->second.inputValue == 'y')
		{
			option->second.realValue = true;
		}
		else
		{
			option->second.realValue = false;
		}
	}
	for (auto option = this->options.begin(); option != this->options.end(); ++option)
	{
		if (option->second.realValue == true)
		{
			this->availableOptions.insert(this->availableOptions.begin(), option->second.correspondingEnum);
		}
	}
	this->CreatePassword();
}

void PasswordGenerator::CreatePassword() // Creating password
{
	std::cout << "Generating password" << std::endl;
	std::uniform_int_distribution<int> distribution(0, this->availableOptions.size() - 1);
	std::string password = "";
	for (int i = 0; i < this->passLength; i++)
	{
		int generatedNumber = distribution(this->randomGenerator);
		password += this->AddChar(static_cast<OptionEnum>(this->availableOptions[generatedNumber]));
	}
	std::cout << "Generated password is: " << password << std::endl;

	char tryAgain;
	std::cout << "Try Again? [Y/N] or change config [C] : ";
	std::cin >> tryAgain;
	if (std::cin.fail())
	{
		std::cout << "Invalid input" << std::endl;
		return;
	}
	else if (tryAgain == 'C' || tryAgain == 'c')
	{
		this->InitConfig();
	}
	else if (tryAgain == 'Y' || tryAgain == 'y')
	{
		this->CreatePassword();
	}
	else
	{
		return;
	}
}

char PasswordGenerator::AddChar(OptionEnum option)
{
	char toReturn;
	switch (option)
	{
	case Special:
	{
		std::uniform_int_distribution<int> distribution(0, 7);
		int generatedNumber = distribution(this->randomGenerator);
		toReturn = asciiSpecial[generatedNumber];
		break;
	}
	case Number:
	{
		std::uniform_int_distribution<int> distribution(asciiNums[0], asciiNums[1]);
		int generatedNumber = distribution(this->randomGenerator);
		toReturn = static_cast<char>(generatedNumber);
		break;
	}
	case Big:
	{
		std::uniform_int_distribution<int> distribution(asciiBig[0], asciiBig[1]);
		int generatedNumber = distribution(this->randomGenerator);
		toReturn = static_cast<char>(generatedNumber);
		break;
	}
	case Small:
	{
		std::uniform_int_distribution<int> distribution(asciiSmall[0], asciiSmall[1]);
		int generatedNumber = distribution(this->randomGenerator);
		toReturn = static_cast<char>(generatedNumber);
		break;
	}
	default:
	{
		toReturn = ' ';
		break;
	}
	}
	return toReturn;
}

PasswordGenerator::PasswordGenerator()
{
	std::cout << "Password Generator Created" << std::endl;
	randomGenerator.seed(time(0));

	Option bigOption;
	bigOption.displayText = "Use big";
	bigOption.correspondingEnum = OptionEnum::Big;

	Option smallOption;
	smallOption.displayText = "Use small";
	smallOption.correspondingEnum = OptionEnum::Small;

	Option numberOption;
	numberOption.displayText = "Use number";
	numberOption.correspondingEnum = OptionEnum::Number;

	Option specialOption;
	specialOption.displayText = "Use special";
	specialOption.correspondingEnum = OptionEnum::Special;

	this->options["Big"] = bigOption;
	this->options["Small"] = smallOption;
	this->options["Number"] = numberOption;
	this->options["Special"] = specialOption;

	this->InitConfig();
}

PasswordGenerator::~PasswordGenerator()
{
	std::cout << "Password Generator Destroyed" << std::endl;
}

int main(int argc, char const *argv[])
{
	PasswordGenerator passwordGenerator = PasswordGenerator();
	return 0;
}