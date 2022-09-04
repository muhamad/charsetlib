// ==++==
//
//    Copyright (C) Muhammad Aladdin
//
//    The use and distribution terms for this software are contained in the file 
//    named LICENSE, which can be found in the root of this distribution.
//
// ==--==

#ifndef CHARSET_UNICODE_TAGS_HPP
#define CHARSET_UNICODE_TAGS_HPP

#include "../unicode/unicode.hpp"

namespace charset
{
namespace conversion
{

// UTF-8 character-set tag
struct utf8_charset
{
	typedef cu8_t  unit_type;
	typedef utf8_t cp_type;

	static const cs_int32 id = 0;
	static const bool is_multibyte = false;
};

// UTF-16 character-set tag
struct utf16_charset
{
	typedef cu16_t  unit_type;
	typedef utf16_t cp_type;

	static const cs_int32 id = 1;
	static const bool is_multibyte = false;
};

// UTF-32 character-set tag
struct utf32_charset
{
	typedef cu32_t  unit_type;
	typedef utf32_t cp_type;

	static const cs_int32 id = 2;
	static const bool is_multibyte = false;
};

}

namespace csi
{
	template<typename> struct is_tag_class { static const bool value = false; };

	template<> struct is_tag_class<conversion::utf8_charset> { static const bool value = true; };
	template<> struct is_tag_class<conversion::utf16_charset> { static const bool value = true; };
	template<> struct is_tag_class<conversion::utf32_charset> { static const bool value = true; };
}

}

#endif // CHARSET_UNICODE_TAGS_HPP
