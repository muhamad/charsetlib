// ==++==
//
//    Copyright (C) Muhammad Aladdin
//
//    The use and distribution terms for this software are contained in the file 
//    named LICENSE, which can be found in the root of this distribution.
//
// ==--==

inline utf32_t unicode::to_utf32(const utf8_t& cp)
{
	if (cp.count == 0) return helper::not_defined_in_unicode;
	if (cp.count == 1) return utf32_t(cp.units[0]);

	// result code point
	utf32_t value = (cp.units[cp.count - 1] & 0x3F);

	// embed all code-units but first
	for(cs_int32 bits = 6, i = cp.count - 2; i > 0; --i, bits += 6)
		value |= (cp.units[i] & 0x3F) << bits;

	// number of bits to shift first code-unit
	const cs_int32 shifts = (cp.count - 1) * 6;

	// load first code-unit
	value |= (cp.units[0] & (0x1F >> (cp.count - 2))) << shifts;

	return value;
}

inline utf32_t unicode::to_utf32(const utf16_t& cp)
{
	if (cp.count == 0) return helper::not_defined_in_unicode;
	if (cp.count == 1) return utf32_t(cp.units[0]);

	return ((utf32_t(cp.units[0] & 0x3FF) << 10) | (cp.units[1] & 0x3FF)) + 0x10000;
}

inline utf32_t unicode::to_utf32(const char* stm)
{
	return to_utf32(stm, 0, false);
}

inline utf32_t unicode::to_utf32(const char* stm, bool is_big)
{
	return to_utf32(stm, 0, is_big);
}

inline utf32_t unicode::to_utf32(const char* stm, cs_int32 at, bool is_big)
{
	utf32_t value;

	if (is_big)
		value = (cu32_t(stm[at]) << 24) | (cu32_t(stm[at+1]) << 16) |
				(cu32_t(stm[at+2]) << 8) | cu32_t(stm[at+3]);
	else
		value = cu32_t(stm[at]) | (cu32_t(stm[at+1]) << 8) |
			   (cu32_t(stm[at+2]) << 16) | (cu32_t(stm[at+3]) << 24);

	return value;
}

inline bool unicode::in_unicode_range(const utf32_t& cp)
{
	return cp <= helper::max_unicode_cp;
}
