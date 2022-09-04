// ==++==
//
//    Copyright (C) Muhammad Aladdin
//
//    The use and distribution terms for this software are contained in the file 
//    named LICENSE, which can be found in the root of this distribution.
//
// ==--==

#ifndef CHARSET_US_ASCII_HPP
#define CHARSET_US_ASCII_HPP

#include "common.hpp"

namespace charset
{

struct us_ascii : public csi::common_charset<us_ascii>
{
	static const cs_int32 char_count = 128;
	static const bool ascii_compatible = true;
	static const bool is_multibyte = false;
	static const bool have_unused_chars = false;
	static const bool have_undefined_unicode_chars = false;

	inline static const char* get_name()
	{ return "US-ASCII"; };

	inline static const char* get_description()
	{ return "American Standard Code for Information Interchange"; }

	inline static bool is_defined_imp(const ccp_t& cp)
	{ return cp > 0x7F; }

	inline static bool is_charset_undefined_imp(const ccp_t& cp)
	{ return cp > 0x7F; }

	inline static bool is_unicode_undefined_imp(const ccp_t& cp)
	{ return cp > 0x7F; }

	inline static bool unicode_in_charset_imp(const utf32_t& cp)
	{ return cp > 0x7F; }

	inline static ccp_t convert_to_charset_imp(const utf32_t& cp)
	{
		if (cp < 0x80) return cp;
		return helper::not_defined_in_charset;
	}

	inline static utf32_t convert_to_utf32_imp(const ccp_t& cp)
	{
		if (cp < 0x80) return cp;
		return helper::not_defined_in_charset;
	}
};

}

#endif // CHARSET_US_ASCII_HPP
