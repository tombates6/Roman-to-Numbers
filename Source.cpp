#include <iostream>
#include <string>
#include <sstream>

/* This is the Roman Numerals Converter, made by Tom Bates on 1/20/20. It takes any roman numeral and converts it
* to its decimal value, or vice versa. It can handle subtractive notation and numbers higher than 9000. It also
* notifies the user when they input invalid numbers, except it doesn't check for correct Roman numeral notation.
* If I had more time, I would have used the ROMAN_NUMERALS string to make sure the input was legal by checking the numerals'
* positions in the string.
*/




const std::string ROMAN_NUMERALS = "IVXLCDM";
const int HUNDREDS = 3;
const int TENS = 2;
const int ONES = 1;
void numToRoman(std::string toConvert);
void romanToNum(std::string& toConvert);
int numeralConverter(char& romNumeral);
void outputNumerals(int decimalVal, const char& highVal, const char& midVal, const char& lowVal);


int main() {
	std::cout << "-Welcome to the Roman Numeral Converter! Enter any whole decimal number or\n";
	std::cout << "Roman numeral, and see what the converted number looks like!\n";
	std::cout << "-If you receive the message \"Invalid Input\", you probably\n";
	std::cout << "entered a letter it didn't recognize. Make sure to only enter the Roman numerals \n";
	std::cout << "as capital letters, like MDCLXVI. Have fun!\n";
	std::cout << "-P.S. If you would like to quit, just type STOP.\n";
	
	std::string toConvert;
	while (toConvert != "STOP") {

		std::cout << "Enter your number: ";
		std::getline(std::cin, toConvert);
		char firstChar = toConvert.front();

		try {
			if (firstChar >= '0' && firstChar <= '9') {
				std::cout << "Your decimal number in Roman numerals is: ";
				numToRoman(toConvert);
			}
			else if (ROMAN_NUMERALS.find(firstChar) != std::string::npos) {
				std::cout << "Your Roman numeral to decimal conversion is: ";
				romanToNum(toConvert);
			}
			else throw(1);
		}
		catch (int m) {
			std::cout << "Invalid Input" << std::endl;
		}
		std::cout << std::endl;
	}
	return 0;
}

/******************************Function Definitions****************************************/

void numToRoman(std::string toConvert) {
/*Since M is the largest Roman numeral, I decided to print it as many times as there are thousands in the number.
* The rest of this function uses the outputNumerals function to print each decimal place in descending order.
* Except for the throw-catch statement in main, I did not account for fractions or negative numbers.
*/

	int decimalVal = 0;

	if (toConvert.size() >= 4) {
		decimalVal = std::stoi(toConvert.substr(0, toConvert.size() - 3));
		for (int i = 0; i < decimalVal; ++i) {
			std::cout << 'M';
		}
		toConvert = toConvert.substr(toConvert.size() - 3);
	}

	if (toConvert.size() == HUNDREDS) {

		decimalVal = toConvert.front() - '0';
		outputNumerals(decimalVal, 'M', 'D', 'C');
		toConvert.erase(toConvert.begin());
	}
	if (toConvert.size() == TENS) {
		decimalVal = toConvert.front() - '0';
		outputNumerals(decimalVal, 'C', 'L', 'X');
		toConvert.erase(toConvert.begin());
	}
	if (toConvert.size() == ONES) {
		decimalVal = toConvert.front() - '0';
		outputNumerals(decimalVal, 'X', 'V', 'I');
		toConvert.erase(toConvert.begin());
	}
	std::cout << std::endl;
}

void romanToNum(std::string& toConvert) {
/*This takes two values at a time and compares them to see if they are in subtraction notation.
* If so, then the difference of the two is added, then two new numbers are examined.
* If not, then only the larger value is added and only one new number is examined.
* This function does not check to see if the Roman numerals are in correct order. 
*/

	int decimalSum = 0;
		for (int i = 0; i < toConvert.size(); ++i) {

			int lastValue = numeralConverter(toConvert.at(i));
			int newValue = 0;

			if ((toConvert.size() - i) > 1) {
				newValue = numeralConverter(toConvert.at(i + 1));
			}

			if (lastValue < newValue) {
				decimalSum += (newValue - lastValue);
				++i;
			}
			else {
				decimalSum += lastValue;
			}
		}
	std::cout << decimalSum << std::endl;

}

int numeralConverter(char & romNumeral) {
/* Using a switch-case statement, this function converts Roman Numeral input to its respective decimal value.
* This is helpful when making comparisons int the functions it is used in.
*/

	int toReturn;
	switch (romNumeral) {
	case 'I':
		toReturn = 1;
		break;
	case 'V':
		toReturn = 5;
		break;
	case 'X':
		toReturn = 10;
		break;
	case 'L':
		toReturn = 50;
		break;
	case 'C':
		toReturn = 100;
		break;
	case 'D':
		toReturn = 500;
		break;
	case 'M':
		toReturn = 1000;
		break;
	}
	return toReturn;
}

void outputNumerals(int decimalVal, const char& highVal, const char& midVal, const char& lowVal) {
/* This is used exclusively by the numToRoman function as a helper function. It takes the special cases first,
*  then adds the remaining digits at the end.
*/
	while (decimalVal != 0) {
		if (decimalVal == 4) {
			std::cout << lowVal << midVal;
			decimalVal = 0;
		}
		else if (decimalVal == 9) {
			std::cout << lowVal << highVal;
			decimalVal = 0;
		}
		else if (decimalVal >= 5) {
			std::cout << midVal;
			decimalVal -= 5;
		}
		else {
			for (int i = 0; i < decimalVal; ++i) {
				std::cout << lowVal;
				--decimalVal;
			}
		}

	}

}
