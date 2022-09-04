// ==++==
//
//    Copyright (C) Muhammad Aladdin
//
//    The use and distribution terms for this software are contained in the file 
//    named LICENSE, which can be found in the root of this distribution.
//
// ==--==

#ifndef CHARSET_CODE_PAGE_X_HPP
#define CHARSET_CODE_PAGE_X_HPP

#include "common.hpp"

namespace charset
{
namespace csi
{

template<typename type, int cc, int az>
struct code_page_x : public common_charset< code_page_x<type, cc, az> >
{
	static const cs_int32 array_size = az;
	static const cs_int32 cp_count = 256;

	static const cs_int32 char_count = cc;
	static const bool ascii_compatible = true;
	static const bool is_multibyte = false;
	static const bool have_unused_chars = (char_count != cp_count);
	static const bool have_undefined_unicode_chars = false;

	static const cs_int32 offset = cp_count - array_size;

	inline static bool is_defined_imp(const ccp_t& cp)
	{
		if (cp <= 0x7F) return true;
		if (cp >= cp_count) return false;

		return type::chars[cp - offset] <= helper::max_unicode_cp;
	}

	inline static bool is_charset_undefined_imp(const ccp_t& cp)
	{
		if (cp <= 0x7F) return false;
		if (cp >= cp_count) return true;

		return type::chars[cp - offset] == helper::not_defined_in_charset;
	}

	inline static bool is_unicode_undefined_imp(const ccp_t& cp)
	{
		if (cp <= 0x7F) return false;
		if (cp >= cp_count) return true;

		return type::chars[cp - offset] == helper::not_defined_in_unicode;
	}

	inline static bool unicode_in_charset_imp(const utf32_t& cp)
	{
		if (cp <= 0x7F) return true;
		return helper::find_index(cp, type::chars) != helper::invalid;
	}

	inline static ccp_t convert_to_charset_imp(const utf32_t& cp)
	{
		if (cp <= 0x7F) return cp;
		const cs_int32 r = helper::find_index(cp, type::chars);

		if (r == helper::invalid) return helper::not_defined_in_charset;
		return r+offset;
	}

	inline static utf32_t convert_to_utf32_imp(const ccp_t& cp)
	{
		if (cp <= 0x7F) return cp;
		if (cp >= cp_count) return helper::not_defined_in_charset;

		const utf32_t r = type::chars[cp - offset];

		switch(r)
		{
		case helper::not_defined_in_charset:
		case helper::not_defined_in_unicode:
			return helper::not_defined_in_unicode;

		default:
			return r;
		}
	}
};

}
}

#endif // CHARSET_CODE_PAGE_X_HPP
