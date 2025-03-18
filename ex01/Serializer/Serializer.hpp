#pragma once

/* ############################################################################################## */

typedef struct Data {
	char   character;
	int	   integer;
	float  singleFloating;
	double doubleFloating;
} Data;

typedef unsigned long uintptr_t;

/* ############################################################################################## */

class Serializer {
	private:
		Serializer(void);
		Serializer(Serializer &source);
		Serializer &operator=(Serializer &source);
		~Serializer(void);
	public:
		static uintptr_t serialize(Data* ptr);
		static Data* deserialize(uintptr_t raw);
};