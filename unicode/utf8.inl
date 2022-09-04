// ==++==
//
//    Copyright (C) Muhammad Aladdin
//
//    The use and distribution terms for this software are contained in the file 
//    named LICENSE, which can be found in the root of this distribution.
//
// ==--==

inline utf8_t unicode::to_utf8(const utf16_t& cp)
{
	return to_utf8( to_utf32(cp) );
}

inline utf8_t unicode::to_utf8(const utf32_t& cp)
{
	if (cp == helper::not_defined_in_unicode) return helper::not_defined<utf8_t>();

	// 0x00 - 0x7F => 1 code-point
	if (cp < 0x80) return utf8_t(cs_uint8(cp));

	utf8_t value;

	// 0x0080 - 0x07FF => 2 code-points
	if (cp < 0x800) value.count = 2;
	// 0x0800 - 0xFFFF => 3 code-points
	else if (cp < 0x10000) value.count = 3;
	// 0x10000 - 0x10FFFF => 4 code-points
	else value.count = 4;

	utf32_t tmp = cp;

	// the code-unit form 2nd to 4th is 10xxxxxx
	for(cs_int32 i = value.count - 1; i > 0; --i)
	{
		value[i] = (2 << 6) | (cs_uint8(tmp) & 0x3F);
		tmp >>= 6;
	}

	// depending on number of code-units the most significant bits
	// take the form: 110, 1110 and 11110 for 2, 3 and 4 code-units
	// the remaining bits comes from what's left in tmp variable
	value[0] = (0xF0 << (4 - value.count)) | cu8_t(tmp);

	return value;
}

inline utf8_t unicode::to_utf8(const cu8_t* stm)
{
	return to_utf8(stm, 0);
}

inline utf8_t unicode::to_utf8(const cu8_t* stm, cs_int32 at)
{
	cu8_t unit = cu8_t(stm[at]);

	if (unit < 0x80) return utf8_t(unit);

	if (unit == 0xC0 || unit == 0xC1 || (unit >= 0xF5 && unit <= 0xFF))
		return helper::not_defined<utf8_t>();

	utf8_t value;

	// 11110xxx
	if ((unit & 0xF0) == 0xF0) value.count = 4;
	// 1110xxxx
	else if ((unit & 0xE0) == 0xE0) value.count = 3;
	// 110xxxxx
	else if ((unit & 0xC0) == 0xC0) value.count = 2;
	// invalid sequence
	else
		return helper::not_defined<utf8_t>();

	// save code-units
	for (cs_int32 i=0; i<value.count; ++i) value.units[i] = stm[at + i];

	// check sequence
	for (cs_int32 i=1; i<value.count; ++i)
	{
		if ((value[i] & 0x80) != 0x80)
			return helper::not_defined<utf8_t>();
	}

	return value;
}

inline cs_int32 unicode::get_utf8_size(const cu8_t& cp)
{
	if (cp == 0xC0 || cp == 0xC1 || (cp >= 0xF5 && cp <= 0xFF))
		return helper::invalid;

	if ((cp & 0xF0) == 0xF0) return 4;
	if ((cp & 0xE0) == 0xE0) return 3;
	if ((cp & 0xC0) == 0xC0) return 2;

	return (cp < 0x80)? 1: helper::invalid;
}

inline bool unicode::in_unicode_range(const utf8_t& cp)
{
	return to_utf32(cp) <= helper::max_unicode_cp;
}

inline bool unicode::is_valid_seq(const utf8_t& cp)
{
	if (cp.count == 0 || cp.count > utf8_t::max_units) return false;

	if (cp.count == 1)
	{
		if (cp[0] < 0x80) return true;
		return false;
	}

	if (cp[0] == 0xC0 || cp[0] == 0xC1 || (cp[0] >= 0xF5 && cp[0] <= 0xFF))
		return false;

	if ( get_utf8_size(cp[0]) != cs_int32(cp.count) ) return false;

	// check sequence
	for (cs_int32 i=1; i<cp.count; ++i)
		if ((cp[i] & 0x80) != 0x80) return false;

	return true;
}
