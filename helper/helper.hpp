// ==++==
//
//    Copyright (C) Muhammad Aladdin
//
//    The use and distribution terms for this software are contained in the file 
//    named LICENSE, which can be found in the root of this distribution.
//
// ==--==

#ifndef CHARSET_HELPER_HPP
#define CHARSET_HELPER_HPP

#include "codepoint.hpp"

namespace charset
{
// character-set single-byte code-point
typedef char ncp_t;
// character-set maximum code-point (should not exceed 3-bytes)
typedef cs_uint32 ccp_t;


// UTF-8 code-unit
typedef cs_uint8  cu8_t;
// UTF-8 code-point
typedef csi::code_point<cu8_t, 4> utf8_t;

// UTF-16 code-unit
typedef cs_uint16 cu16_t;
// UTF-16 code-point
typedef csi::code_point<cu16_t, 2> utf16_t;

// UTF-32 code-unit
typedef cs_uint32 cu32_t;
// UTF-32 code point
typedef cu32_t utf32_t;

struct helper
{

	// maximum code-point that can be represented by Unicode
	static const cs_int32 max_unicode_cp = 0x10FFFF;
	// maximum code-point that can be represented by Charset
	static const cs_int32 max_charset_cp = 0x7FFFFFFF;

	// surrogate code-point for UTF-16
	static const cu16_t u16_lo_surrogate = 0xD800;
	static const cu16_t u16_lo_surrogate_end = 0xDBFF;
	static const cu16_t u16_hi_surrogate = 0xDC00;
	static const cu16_t u16_hi_surrogate_end = 0xDFFF;

	// UTF-16 multiple code-unit range
	static const cu16_t u16_surrogate_min = 0xD800;
	static const cu16_t u16_surrogate_max = 0xDFFF;

	// value used to define code-point state
	static const cs_uint32 not_defined_in_charset = 0xFFFFFFFF;
	static const cs_uint32 not_defined_in_unicode = 0xFFFFFFFE;

	// represent invalid index or invalid operation
	static const cs_int32 invalid = -1;

	// find element in array
	template<typename T, int size>
	inline static cs_int32 find_index(const T& value, const T (&list)[size])
	{
		for (int i=0; i<size; ++i)
			if (list[i] == value) return i;

		return invalid;
	}

	template<typename T, int size>
	inline static bool is_in(const T& value, const T (&list)[size])
	{ return find_index(value, list) != invalid; }

	template<typename T>
	inline static T not_defined(const cs_uint32 value = not_defined_in_unicode)
	{
		T cp;
		cp.all = value;
		cp.count = 0;
		return cp;
	}

};

}

#endif // CHARSET_HELPER_HPP
