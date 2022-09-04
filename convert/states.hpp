// ==++==
//
//    Copyright (C) Muhammad Aladdin
//
//    The use and distribution terms for this software are contained in the file 
//    named LICENSE, which can be found in the root of this distribution.
//
// ==--==

#ifndef CHARSET_STATES_HPP
#define CHARSET_STATES_HPP

namespace charset
{
namespace conversion
{

// conversion states
enum states
{
	OK,
	UnexpectedEndOfFile,
	WriteError,
	ReadError,
	NoUnget,
	InvalidUTF16BOM,
	InvalidUTF32BOM,
	InvalidUTF8Byte,
	InvalidUTF16Surrogate,
	OutOfRangeUnicodeCodePoint,
	UTF32InUTF16ReservedArea,
	OutOfRangeCharsetCodePoint,
	CodePointNotDefinedInCharset,
	CodePointNotDefinedInUnicode
};

}
}

#endif // CHARSET_STATES_HPP
