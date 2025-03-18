#pragma once

/* ############################################################################################## */

#include <cerrno>
#include <cmath>
#include <iomanip>
#include <limits>

/* ############################################################################################## */

#include "../Serializer/Serializer.hpp"

/* ############################################################################################## */

typedef enum type {
	UNKNOWN	 = 0,
	INTEGER	 = 1,
	FLOATING = 2,
	DOUBLE	 = 3
} type;

/* ############################################################################################## */

class ScalarConverter {
	private:
		ScalarConverter(void);
		ScalarConverter(ScalarConverter &source);
		ScalarConverter &operator=(ScalarConverter &source);
		~ScalarConverter(void);

		static type	getType(const std::string &value);
		static Data *createData(const char character, const int integer, const float singleFloat, const double doubleFloat);
	public:
		static Data *convert(const std::string &value);
};