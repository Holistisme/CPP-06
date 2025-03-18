#include "Serializer/Serializer.hpp"
#include "ScalarConverter/ScalarConverter.hpp"
#include "InputLib/Input.hpp"
#include "ColorFormatLib/ColorFormat.hpp"

/* ############################################################################################## */

static void test(const std::string &value = "42.42f");
static uintptr_t serializeData(Data *data);
static void checkData(const uintptr_t &raw);
static void displayData(Data *data);

/* ############################################################################################## */

int main(void) {
	try {
		std::cout << std::fixed << std::setprecision(1) << std::endl;
		std::cout << "Welcome to the serializer program ”" << ColorFormat::formatString("Serialization™", "yellow", "blink", "bold") << "“!" << std::endl;
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
			if (userInput.stringFormat() == "auto") {
				std::cout << ColorFormat::formatString("\n* Auto-TEST launched! *", "yellow", "bold") << std::endl;
				test();
			}
			else if (userInput.stringFormat() == "EXIT")
				break;
			else
				test(userInput.stringFormat());
		}
	} catch (std::exception &e) { std::cerr << ColorFormat::formatString("The following error has been encountered: ", "red", "bold") << e.what() << std::endl; }

	std::cout << "\nThanks for using ”" << ColorFormat::formatString("Serialization™", "yellow", "blink", "bold") << "“!\n" << std::endl;
	return 0;
}

static void test(const std::string &value) {
	std::cout << "\nCreating a scalar conversion with " << ColorFormat::formatString(value, "cyan") << '.' << std::endl;
    Data* original = ScalarConverter::convert(value);

	if (original) {
		displayData(original);
		uintptr_t serialized = serializeData(original);
		checkData(serialized);
		delete original;
	}
}

static uintptr_t serializeData(Data *data) {
	uintptr_t		   raw = Serializer::serialize(data);
	std::ostringstream ossData;	 ossData << data;
	std::ostringstream ossRaw;	 ossRaw	 << raw;

	std::cout << "\nSerialization of " << ColorFormat::formatString(ossData.str(), "magenta", "italic") << " into "
									   << ColorFormat::formatString(ossRaw.str(), "blue", "italic")		<< " aka "
									   << ColorFormat::formatUnsignedInteger(raw, "yellow")				<< '.' << std::endl;
	return raw;
}

static void checkData(const uintptr_t &raw) {
	std::ostringstream oss; oss << raw;
	std::cout << "\nDeserialization of " << ColorFormat::formatString(oss.str(), "blue", "italic") << " aka "
									   	 << ColorFormat::formatUnsignedInteger(raw, "yellow")	   << '.' << std::endl;
	displayData(Serializer::deserialize(raw));
}

static void displayData(Data *data) {
	std::ostringstream oss; oss << data;

    std::cout << "Data content from " << ColorFormat::formatString(oss.str(), "green", "italic") << ':' << std::endl;
	std::cout << "  - Character: "	  << data->character												<< std::endl;
	std::cout << "  - Integer: "	  << data->integer													<< std::endl;
	std::cout << "  - Float: "		  << data->singleFloating									 << 'f' << std::endl;
	std::cout << "  - Double: "		  << data->doubleFloating											<< std::endl;
}