#include "ScalarConverter/ScalarConverter.hpp"
#include "InputLib/Input.hpp"
#include "ColorFormatLib/ColorFormat.hpp"

/* ############################################################################################## */

static void autoTest(void);

/* ############################################################################################## */

int main(void) {
	try {
		std::cout << "\nWelcome to the type conversion program ”" << ColorFormat::formatString("Scalar_Convertion™", "green", "blink", "bold") << "“!" << std::endl;
		while (true) {
			ColorFormat nanf(		 "nanf",  "yellow", "italic");
			ColorFormat positiveInff("+inff", "yellow", "italic");
			ColorFormat negativeInff("-inff", "yellow", "italic");
			ColorFormat nan(		 "nan",	  "blue",	"italic");
			ColorFormat positiveInf("+inf",	  "blue",	"italic");
			ColorFormat negativeInf("-inf",	  "blue",	"italic");

			std::cout << "_______________________________________________________________________________\n" << std::endl;

			std::cout << "You can enter a " << ColorFormat::formatString("precise string", "yellow", "italic") << ", ”"
											<< ColorFormat::formatString("auto", "blue", "italic")			   << "“ to test automatically or ”"
											<< ColorFormat::formatString("EXIT", "red", "italic")			   << "“ to quit!" << std::endl;
	
			std::cout << "\nThe formatting of a " << ColorFormat::formatString("character", "cyan", "underline") << " must be enclosed in quotes: ”"
												  << ColorFormat::formatString("'", "cyan")						 << "” ("
												  << ColorFormat::formatString("example", "italic")				 << ": "
												  << ColorFormat::formatString("'a'", "cyan", "bold")			 << ")." << std::endl;
			
			std::cout << "\nThe program accepts " << ColorFormat::formatString("positive integer signs", "underline")	<< " and the "
												  << ColorFormat::formatString("following special values", "underline") << ":" << std::endl;
			std::cout << "- "	 << nanf.getFormattedString() << ", " << positiveInff.getFormattedString() << ", " << negativeInff.getFormattedString()
					  << " for " << ColorFormat::formatString("floats", "yellow", "bold") << "." << std::endl;
			std::cout << "- "	 << nan.getFormattedString()  << ", " << positiveInf.getFormattedString()  << ", " << negativeInf.getFormattedString()
					  << " for " << ColorFormat::formatString("doubles", "blue", "bold") << "."	 << std::endl;

			std::cout << "_______________________________________________________________________________\n" << std::endl;

			Input userInput("What do you want to test?");
			if		(userInput.stringFormat() == "auto")	autoTest();
			else if (userInput.stringFormat() == "EXIT")	break;
			else											ScalarConverter::convert(userInput.stringFormat());
		}
	} catch (std::exception &e) { std::cerr << ColorFormat::formatString("The following error has been encountered: ", "red", "bold") << e.what() << std::endl; }

	std::cout << "\nThanks for using ”" << ColorFormat::formatString("Scalar_Convertion™", "green", "blink", "bold") << "“!\n" << std::endl;
	return 0;
}

static void autoTest(void) {
	std::cout << ColorFormat::formatString("\n* Auto-TEST launched! *\n", "yellow", "bold") << std::endl;
	const std::string tests[28] = {
		"'a'",	 "'0'",	  "' '",
		"42",	 "-42",	  "0",	   "2147483647", "2147483648",
		"42.0f", "-4.2f", "nanf",  "+inff",		 "-inff",
		"42.0",	 "-4.2",  "nan",   "+inf",		 "-inf",
		"abc",	 "7f",	  "",	   "	   ",
		"+42",	 "-0",	  "00042", ".42",		 "42.", "42.42.42"
	};

	for (size_t index = 0 ; index < 28 ; index++) {
		std::cout << "=== Test " << ColorFormat::formatUnsignedInteger(index, "cyan", "bold") << " : "
								 << ColorFormat::formatString(tests[index], "green", "bold")  << " ===" << std::endl;
		ScalarConverter::convert(tests[index]);
		std::cout << std::endl;
	}
}