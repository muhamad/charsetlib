#include <fstream>
#include <iostream>
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;

#include "charset.hpp"
using charset::windows1252;
using charset::conversion::utf16_charset;
using charset::conversion::basic_converter;

const char* state_message[] =
{
	"conversion completed without errors.",
	"end of file reached where data expected.",
	"can not write into stream.",
	"can not read from stream.",
	"lookahead is not supported in input stream.",
	"the UTF-16 BOM in input stream is invalid.",
	"the UTF-32 BOM in input stream is invalid.",
	"invalid UTF-8 byte found in input stream.",
	"invalid UTF-16 surrogate found in input stream.",
	"a Unicode code-point that exceeds 0x10FFFF has been found.",
	"a UTF-16 surrogate code-point found in UTF-32 input stream.",
	"a character-set code-point is beyond character-set limits.",
	"input/output character-set didn't define such code-point.",
	"input/output code-point is valid in character-set but it's not defined in Unicode."
};

int main()
{
	typedef basic_converter<windows1252, utf16_charset> wtu;

	ifstream ifs("fr.txt");
	ofstream ofs("fr2.txt", std::ios_base::binary);

	wtu c(ifs, ofs, false);
	c.run();

	if (c.failed()) cout << "Conversion failed with reason: ";
	cout << state_message[ c.state() ] << endl;
}
