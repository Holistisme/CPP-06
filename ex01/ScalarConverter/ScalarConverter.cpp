#include "ScalarConverter.hpp"
#include "../ColorFormatLib/ColorFormat.hpp"

/* ############################################################################################## */

ScalarConverter::ScalarConverter(void)								 {								}
ScalarConverter::ScalarConverter(ScalarConverter &source)			 { (void) source;				}
ScalarConverter &ScalarConverter::operator=(ScalarConverter &source) { (void) source; return *this; }
ScalarConverter::~ScalarConverter(void)								 {								}

/* ############################################################################################## */

type ScalarConverter::getType(const std::string &value) {
	if		(value.empty())														return UNKNOWN;
	else if (value == "-inff" or value == "+inff" or value == "nanf")			return FLOATING;
	else if (value == "-inf"  or value == "+inf"  or value == "nan")			return DOUBLE;

	const bool	isSigned		= value[0] == '+' or value[0] == '-';
	if (isSigned ? not std::isdigit(value[1]) : not std::isdigit(value[0]))		return UNKNOWN;

	bool		hasComma		= false;
	const bool	hasFloatingMark = value[value.length() - 1] == 'f';

	for (size_t index = isSigned ; index < value.length() - hasFloatingMark ; index++) {
		if (value[index] == '.' and index
								and std::isdigit(value[index - 1])
								and index != value.length() - (hasFloatingMark ? 2 : 1)
								and not hasComma)
			hasComma = true;
		else if (not std::isdigit(value[index]))   return UNKNOWN;
	}

	if		(not hasComma and not hasFloatingMark)	return INTEGER;
	else if	(hasComma and hasFloatingMark)			return FLOATING;
	else if (hasComma)								return DOUBLE;

	return UNKNOWN;
}

Data *ScalarConverter::createData(const char character, const int integer, const float singleFloat, const double doubleFloat) {
	const bool validInteger = not (std::isnan(singleFloat) or std::isinf(singleFloat))
								and singleFloat >= std::numeric_limits<int>::min()
								and singleFloat <= std::numeric_limits<int>::max();
	const bool validCharacter = validInteger and integer >= 0 and integer < 128
									and std::isprint(character);

	Data *data			 = new Data;
	data->character		 = validCharacter ? character : '?';
	data->integer		 = validInteger	  ? integer	  : 0;
	data->singleFloating = singleFloat;
	data->doubleFloating = doubleFloat;
	return data;
}

Data *ScalarConverter::convert(const std::string &value) {
	const type type	   = getType(value);
	const bool special = value == "-inff" or value == "+inff" or value == "nanf"
					  or value == "-inf"  or value == "+inf"  or value == "nan";

	if (value.length() == 3 and value[0] == '\'' and (value[2] == '\''))
		return createData(value[1],
				static_cast<int>(value[1]),
				static_cast<float>(value[1]),
				static_cast<double>(value[1]));
	else if (type == INTEGER) {
		errno = 0;
		const long strtol = std::strtol(value.c_str(), NULL, 10);

		if (not (errno == ERANGE) and strtol >= std::numeric_limits<int>::min()
								and strtol <= std::numeric_limits<int>::max()) {
			const int atoi = std::atoi(value.c_str());
			return createData(static_cast<char>(atoi),
							atoi,
							static_cast<float>(atoi),
							static_cast<double>(atoi));
		}
	}
	else if (type == FLOATING) {
		errno = 0;
		const float strtof = std::strtof(value.c_str(), NULL);

		if (special or not (errno == ERANGE or std::isinf(strtof)))
			return createData(static_cast<char>(strtof),
						static_cast<int>(strtof),
						strtof,
						static_cast<double>(strtof));
	}
	else if (type == DOUBLE) {
		errno = 0;
		const double strtod = std::strtod(value.c_str(), NULL);

		if (special or not (errno == ERANGE or std::isinf(strtod)))
			return createData(static_cast<char>(strtod),
						static_cast<int>(strtod),
						static_cast<float>(strtod),
						strtod);
	}
	std::cout << ColorFormat::formatString("Type conversion is impossible!", "red", "blink") << std::endl;
	return NULL;
}