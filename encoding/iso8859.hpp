// ==++==
//
//    Copyright (C) Muhammad Aladdin
//
//    The use and distribution terms for this software are contained in the file 
//    named LICENSE, which can be found in the root of this distribution.
//
// ==--==

#ifndef CHARSET_ISO8859_HPP
#define CHARSET_ISO8859_HPP

#include "code_page_x.hpp"

namespace charset
{
#define DEFINE_ISO8859_X(ID, CC) \
struct iso8859_ ## ID : public csi::code_page_x<iso8859_ ## ID, CC, 96> \
{ \
	static const utf32_t chars[array_size]; \
\
	inline static const char* get_name() { return "ISO/IEC 8859-" #ID; } \
\
	inline const char* get_description(); \
};

DEFINE_ISO8859_X(1, 191)
DEFINE_ISO8859_X(2, 191)
DEFINE_ISO8859_X(3, 184)
DEFINE_ISO8859_X(4, 191)
DEFINE_ISO8859_X(5, 191)
DEFINE_ISO8859_X(6, 146)
DEFINE_ISO8859_X(7, 188)
DEFINE_ISO8859_X(8, 155)
DEFINE_ISO8859_X(9, 191)
DEFINE_ISO8859_X(10, 191)
DEFINE_ISO8859_X(11, 183)
DEFINE_ISO8859_X(13, 191)
DEFINE_ISO8859_X(14, 191)
DEFINE_ISO8859_X(15, 191)
DEFINE_ISO8859_X(16, 191)

inline const char* iso8859_1::get_description() { return "Latin 1"; }
inline const char* iso8859_2::get_description() { return "Latin 2"; }
inline const char* iso8859_3::get_description() { return "Latin 3"; }
inline const char* iso8859_4::get_description() { return "Baltic"; }
inline const char* iso8859_5::get_description() { return "Cyrillic"; }
inline const char* iso8859_6::get_description() { return "Arabic"; }
inline const char* iso8859_7::get_description() { return "Greek"; }
inline const char* iso8859_8::get_description() { return "Hebrew"; }
inline const char* iso8859_9::get_description() { return "Turkish"; }
inline const char* iso8859_10::get_description() { return "Latin 6"; }
inline const char* iso8859_11::get_description() { return "Thai"; }
inline const char* iso8859_13::get_description() { return "Latin 7"; }
inline const char* iso8859_14::get_description() { return "Latin 8"; }
inline const char* iso8859_15::get_description() { return "Latin 9"; }
inline const char* iso8859_16::get_description() { return "Latin 10"; }

#undef DEFINE_ISO8859_X
}

#endif // CHARSET_ISO8859_HPP
