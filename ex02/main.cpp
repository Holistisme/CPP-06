#include "Base/Base.hpp"
#include "Base/A.hpp"
#include "Base/B.hpp"
#include "Base/C.hpp"
#include "InputLib/Input.hpp"
#include "ColorFormatLib/ColorFormat.hpp"

/* ############################################################################################## */

#include <ctime>

/* ############################################################################################## */

#define AUTHORIZE 1
#define FORBID	  2

/* ############################################################################################## */

bool canWhisper(const int change = 0);

Base *generate(void);
void identify(Base *p);
void identify(Base &p);

static void identifyBase(Base *base);

static void autoTest(void);
static void guessTest(void) ;

static void whatIsWrongWithUser(const Input &firstInput, const Input &secondInput);

/* ############################################################################################## */

int main(void) {
	try {
		std::srand(std::time(NULL));
		std::cout << "\nWelcome to the serializer program ”" << ColorFormat::formatString("RealType™", "magenta", "blink", "bold") << "“!" << std::endl;
		while (true) {
			std::cout << "_______________________________________________________________________________\n" << std::endl;
			std::cout << "You can enter ”" << ColorFormat::formatString("guess", "green", "italic")	 		 << "“ to try a bad game, ”"
										   << ColorFormat::formatString("auto", "blue", "italic")		 	 << "“ to test automatically or ”"
										   << ColorFormat::formatString("EXIT", "red", "italic")			 << "“ to quit!" << std::endl;
			std::cout << "_______________________________________________________________________________\n" << std::endl;

			Input userInput("What do you want to test?");
			if		(userInput.stringFormat() == "auto")	autoTest();
			else if (userInput.stringFormat() == "guess")	guessTest();
			else if (userInput.stringFormat() == "EXIT")	break;
			else											std::cout << ColorFormat::formatString("Unclear instructions!", "red", "bold") << std::endl;
		}
	} catch (std::exception &e) { std::cerr << ColorFormat::formatString("The following error has been encountered: ", "red", "bold") << e.what() << std::endl; }

	std::cout << "\nThanks for using ”" << ColorFormat::formatString("RealType™", "magenta", "blink", "bold") << "“!\n" << std::endl;
	return 0;
}

/* ############################################################################################## */

bool canWhisper(const int change) {
	static bool ability = false;

	if		(change == AUTHORIZE)	ability = true;
	else if (change == FORBID)		ability = false;

	return ability;
}

/* ############################################################################################## */

Base *generate(void) {
	int randomBase = std::rand() % 3;

	if (canWhisper())
		std::cout << ColorFormat::formatString("Whisper:", "italic") << " I will generate the following type: "
				  << ColorFormat::formatString(std::string(1, static_cast<char>(randomBase + 65)), "magenta") << std::endl;

	if (randomBase == 0)	return (new A);
	if (randomBase == 1)	return (new B);
							return (new C);

}

void identify(Base *p) {
	std::string type = "";

	if (dynamic_cast<A*>(p))		type = "A";
	else if (dynamic_cast<B*>(p))	type = "B";
	else if (dynamic_cast<C*>(p))	type = "C";

	if (not type.empty())
		std::cout << "- Detection of type " << ColorFormat::formatString(type, "green")		  << " by its "
											<< ColorFormat::formatString("pointer", "yellow") << '!' << std::endl;
	else
		std::cout << ColorFormat::formatString("Unknown type detection !", "red", "bold") << std::endl;
}

void identify(Base &p) {
	std::string type = "";

	try { A &a = dynamic_cast<A&>(p);	  (void)a; type = "A"; }
	catch (...)		{}

	if (type.empty()) {
		try	{ B &b = dynamic_cast<B&>(p); (void)b; type = "B"; }
		catch (...) {}
	}

	if (type.empty()) {
		try	{ C &c = dynamic_cast<C&>(p); (void)c; type = "C"; }
		catch (...) {}
	}

	if (not type.empty())
		std::cout << "- Detection of type " << ColorFormat::formatString(type, "green")		  << " by its "
											<< ColorFormat::formatString("reference", "blue") << '!' << std::endl;
	else
		std::cout << ColorFormat::formatString("Unknown type detection !", "red", "bold") << std::endl;
}

/* ############################################################################################## */

static void autoTest(void) {
	std::cout << ColorFormat::formatString("\n* Auto-TEST launched! *", "yellow", "bold") << std::endl;

	canWhisper(AUTHORIZE);
	for (size_t index = 0 ; index < 10 ; index++) {
		std::cout << "\n=== Test " << ColorFormat::formatUnsignedInteger(index + 1, "cyan") << " ===\n" << std::endl;
		Base *randomBase = generate();

		identifyBase(randomBase);

		delete randomBase;
	}
}

static void guessTest(void) {
	canWhisper(FORBID);

	Base *randomBase = generate();

	std::string answer;
	if (dynamic_cast<A*>(randomBase))		answer = "A";
	else if (dynamic_cast<B*>(randomBase))	answer = "B";
	else if (dynamic_cast<C*>(randomBase))	answer = "C";

	std::cout << "\nCan you guess the " << ColorFormat::rainbow("random base", "blink") << " ?\n" << std::endl;

	Input firstGuess;
	if	   (firstGuess.stringFormat() != answer) {	std::cout << ColorFormat::formatString("Ow, that's not true! I'll give you a second chance.\n", "red", "bold")		   << std::endl;
		Input secondGuess;
		if (secondGuess.stringFormat() != answer)	std::cout << ColorFormat::formatString("No effort you noob!", "red", "bold", "blink")								   << std::endl;
		else										std::cout << ColorFormat::formatString("You could have been better, but at least it's not shameful!", "green", "bold") << std::endl;
													whatIsWrongWithUser(firstGuess, secondGuess);
	}
	else											std::cout << ColorFormat::formatString("Congratulations, you made it on the first try!", "green", "bold", "blink")	   << std::endl;

	identifyBase(randomBase);
	delete randomBase;
}

static void identifyBase(Base *base) {
	std::cout << "\nBase identification..." << std::endl;

	identify(base); identify(*base);
}

static void whatIsWrongWithUser(const Input &firstInput, const Input &secondInput) {
	if (firstInput.stringFormat() == "Rick" and secondInput.stringFormat() == "Astley") {
		#ifdef __linux__
			system("xdg-open https://www.youtube.com/watch?v=dQw4w9WgXcQ > /dev/null 2>&1");
		#elif _WIN32
			system("start https://www.youtube.com/watch?v=dQw4w9WgXcQ > nul 2>&1");
		#elif __APPLE__
			system("open https://www.youtube.com/watch?v=dQw4w9WgXcQ > /dev/null 2>&1");
		#endif
		std::cout << ColorFormat::rainbow("\nWait wait wait...\nWhat is wrong with you ? I LOVE YOUR STUPIDITY!", "bold", "blink") << std::endl;
	}
}