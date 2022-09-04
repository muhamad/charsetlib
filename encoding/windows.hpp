// ==++==
//
//    Copyright (C) Muhammad Aladdin
//
//    The use and distribution terms for this software are contained in the file 
//    named LICENSE, which can be found in the root of this distribution.
//
// ==--==

#ifndef CHARSET_WINDOWS_HPP
#define CHARSET_WINDOWS_HPP

#include "code_page_x.hpp"

namespace charset
{

struct windows874 : public csi::code_page_x<windows874, 225, 128>
{
	static const utf32_t chars[array_size];
	inline static const char* get_name() { return "Windows-874"; }
	inline static const char* get_description() { return "Thai"; }
};

#define DEFINE_WINDOWS_X(ID, CC) \
struct windows125 ## ID : public csi::code_page_x<windows125 ## ID, CC, 128> \
{ \
	static const utf32_t chars[array_size]; \
\
	inline static const char* get_name() { return "Windows-125" #ID; } \
\
	inline static const char* get_description(); \
};

DEFINE_WINDOWS_X(0, 251)
DEFINE_WINDOWS_X(1, 255)
DEFINE_WINDOWS_X(2, 251)
DEFINE_WINDOWS_X(3, 239)
DEFINE_WINDOWS_X(4, 249)
DEFINE_WINDOWS_X(5, 232)
DEFINE_WINDOWS_X(6, 256)
DEFINE_WINDOWS_X(7, 244)
DEFINE_WINDOWS_X(8, 247)

inline const char* windows1250::get_description() { return "Central Europe"; }
inline const char* windows1251::get_description() { return "Cyrillic"; }
inline const char* windows1252::get_description() { return "Latin I"; }
inline const char* windows1253::get_description() { return "Greek"; }
inline const char* windows1254::get_description() { return "Turkish"; }
inline const char* windows1255::get_description() { return "Hebrew"; }
inline const char* windows1256::get_description() { return "Arabic"; }
inline const char* windows1257::get_description() { return "Baltic"; }
inline const char* windows1258::get_description() { return "Vietnam"; }

#undef DEFINE_WINDOWS_X
}

#endif // CHARSET_WINDOWS_HPP
