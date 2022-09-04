// ==++==
//
//    Copyright (C) Muhammad Aladdin
//
//    The use and distribution terms for this software are contained in the file 
//    named LICENSE, which can be found in the root of this distribution.
//
// ==--==

#ifndef CHARSET_COMMON_HPP
#define CHARSET_COMMON_HPP

#include "../unicode/unicode.hpp"

namespace charset
{
namespace csi // character-set internals
{

template<typename type>
struct common_charset
{
	inline static bool is_defined(const ncp_t& cp)
	{
		return type::is_defined_imp( ccp_t((cs_uint8)cp) );
	}

	inline static bool is_defined(const ccp_t& cp)
	{
		return type::is_defined_imp(cp);
	}

	inline static bool is_charset_undefined(const ncp_t& cp)
	{
		return type::is_charset_undefined_imp( ccp_t((cs_uint8)cp) );
	}

	inline static bool is_charset_undefined(const ccp_t& cp)
	{
		return type::is_charset_undefined_imp(cp);
	}

	inline static bool is_unicode_undefined(const ncp_t& cp)
	{
		return type::is_unicode_undefined_imp( ccp_t((cs_uint8)cp) );
	}

	inline static bool is_unicode_undefined(const ccp_t& cp)
	{
		return type::is_unicode_undefined_imp(cp);
	}

	inline static bool unicode_in_charset(const utf8_t& cp)
	{
		return type::unicode_in_charset_imp( unicode::to_utf32(cp) );
	}

	inline static bool unicode_in_charset(const utf16_t& cp)
	{
		return type::unicode_in_charset_imp( unicode::to_utf32(cp) );
	}

	inline static bool unicode_in_charset(const utf32_t& cp)
	{
		return type::unicode_in_charset_imp(cp);
	}

	inline static ccp_t convert_to_charset(const utf8_t& cp)
	{
		return type::convert_to_charset_imp( unicode::to_utf32(cp) );
	}

	inline static ccp_t convert_to_charset(const utf16_t& cp)
	{
		return type::convert_to_charset_imp( unicode::to_utf32(cp) );
	}

	inline static ccp_t convert_to_charset(const utf32_t& cp)
	{
		return type::convert_to_charset_imp(cp);
	}

	inline static utf8_t convert_to_utf8(const ncp_t& cp)
	{
		const utf32_t value = type::convert_to_utf32_imp( ccp_t((cs_uint8)cp) );
		if (value > helper::max_unicode_cp) return helper::not_defined<utf8_t>();
		return unicode::to_utf8(value);
	}

	inline static utf8_t convert_to_utf8(const ccp_t& cp)
	{
		const utf32_t value = type::convert_to_utf32_imp(cp);
		if (value > helper::max_unicode_cp) return helper::not_defined<utf8_t>();
		return unicode::to_utf8(value);
	}

	inline static utf16_t convert_to_utf16(const ncp_t& cp)
	{
		const utf32_t value = type::convert_to_utf32_imp( ccp_t((cs_uint8)cp) );
		if (value > helper::max_unicode_cp) return helper::not_defined<utf16_t>();
		return unicode::to_utf16(value);
	}

	inline static utf16_t convert_to_utf16(const ccp_t& cp)
	{
		const utf32_t value = type::convert_to_utf32_imp(cp);
		if (value > helper::max_unicode_cp) return helper::not_defined<utf16_t>();
		return unicode::to_utf16(value);
	}

	inline static utf32_t convert_to_utf32(const ncp_t& cp)
	{
		const utf32_t value = type::convert_to_utf32_imp( ccp_t((cs_uint8)cp) );
		if (value > helper::max_unicode_cp) return helper::not_defined_in_unicode;
		return value;
	}

	inline static utf32_t convert_to_utf32(const ccp_t& cp)
	{
		const utf32_t value = type::convert_to_utf32_imp(cp);
		if (value > helper::max_unicode_cp) return helper::not_defined_in_unicode;
		return value;
	}
};

}
}

#endif // CHARSET_COMMON_HPP
