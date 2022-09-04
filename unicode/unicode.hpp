// ==++==
//
//    Copyright (C) Muhammad Aladdin
//
//    The use and distribution terms for this software are contained in the file 
//    named LICENSE, which can be found in the root of this distribution.
//
// ==--==

#ifndef CHARSET_UNICODE_HPP
#define CHARSET_UNICODE_HPP

#include "../helper/helper.hpp"

namespace charset
{

// Unicode utility functions for UTF-8 -16 -32
struct unicode
{
	// convert UTF-X code-point to UTF-8
	inline static utf8_t to_utf8(const utf16_t& cp);
	inline static utf8_t to_utf8(const utf32_t& cp);

	// get UTF-8 code-point from UTF-8 code-unit stream
	inline static utf8_t to_utf8(const cu8_t* stm);
	inline static utf8_t to_utf8(const cu8_t* stm, cs_int32 at);

	// convert UTF-X code-point to UTF-16
	inline static utf16_t to_utf16(const utf8_t& cp);
	inline static utf16_t to_utf16(const utf32_t& cp);

	// get UTF-16 code-point from UTF-16 code-unit stream
	inline static utf16_t to_utf16(const cu16_t* stm);
	inline static utf16_t to_utf16(const cu16_t* stm, cs_int32 at);

	// get UTF-16 code-point from endian byte-stream
	inline static utf16_t to_utf16(const char* stm);
	inline static utf16_t to_utf16(const char* stm, bool is_big);
	inline static utf16_t to_utf16(const char* stm, cs_int32 at, bool is_big);

	// convert UTF-X code-point to UTF-32
	inline static utf32_t to_utf32(const utf8_t& cp);
	inline static utf32_t to_utf32(const utf16_t& cp);

	// get UTF-32 code-point from endian byte-stream
	inline static utf32_t to_utf32(const char* stm);
	inline static utf32_t to_utf32(const char* stm, bool is_big);
	inline static utf32_t to_utf32(const char* stm, cs_int32 at, bool is_big);

	// get number of code-units in single code-point
	inline static cs_int32 get_utf8_size(const cu8_t& cp);
	inline static cs_int32 get_utf16_size(const cu16_t& cp);

	// is input character fall in Unicode defined range
	inline static bool in_unicode_range(const utf8_t& cp);
	inline static bool in_unicode_range(const utf16_t& cp);
	inline static bool in_unicode_range(const utf32_t& cp);

	// validate code-units of input code-point
	// return true for valid sequence; otherwise false
	inline static bool is_valid_seq(const utf8_t& cp);
	inline static bool is_valid_seq(const utf16_t& cp);

	// check if input code-point is reserved for UTF-16
	// return true for reserved code-point; otherwise false
	inline static bool is_utf16_reserved(const utf8_t& cp);
	inline static bool is_utf16_reserved(const utf32_t& cp);
};

#include "utf8.inl"
#include "utf16.inl"
#include "utf32.inl"

}

#endif // CHARSET_UNICODE_HPP
