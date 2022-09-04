// ==++==
//
//    Copyright (C) Muhammad Aladdin
//
//    The use and distribution terms for this software are contained in the file 
//    named LICENSE, which can be found in the root of this distribution.
//
// ==--==

inline utf16_t unicode::to_utf16(const utf8_t& cp)
{
	return to_utf16( to_utf32(cp) );
}

inline utf16_t unicode::to_utf16(const utf32_t& cp)
{
	if (cp == helper::not_defined_in_unicode || unicode::is_utf16_reserved(cp))
		return helper::not_defined<utf16_t>();

	if (cp <= 0x10000) return utf16_t(cu16_t(cp));

	utf16_t value;
	utf32_t tmp = cp - 0x10000;

	value.count = 2;
	value[0] = helper::u16_lo_surrogate | cu16_t(tmp >> 10);
	value[1] = helper::u16_hi_surrogate | cu16_t(tmp & 0x3FF);

	return value;
}

inline utf16_t unicode::to_utf16(const cu16_t* stm)
{
	return to_utf16(stm, 0);
}

inline utf16_t unicode::to_utf16(const cu16_t* stm, cs_int32 at)
{
	if (stm[at] < helper::u16_surrogate_min || stm[at] > helper::u16_surrogate_max)
		return utf16_t(stm[at]);

	utf16_t value;
	value.count = 2;
	value[0] = stm[at];
	value[1] = stm[at+1];

	if ((value[0] < helper::u16_lo_surrogate || value[0] > helper::u16_lo_surrogate_end) &&
		(value[1] < helper::u16_hi_surrogate || value[1] > helper::u16_hi_surrogate_end))
			return helper::not_defined<utf16_t>();

	return value;
}

inline utf16_t unicode::to_utf16(const char* stm)
{
	return to_utf16(stm, 0, false);
}

inline utf16_t unicode::to_utf16(const char* stm, bool is_big)
{
	return to_utf16(stm, 0, is_big);
}

inline utf16_t unicode::to_utf16(const char* stm, cs_int32 at, bool is_big)
{
	utf16_t value;
	
	value[0] = stm[at++];
	if (is_big)
		value[0] = (value[0] << 8 | stm[at++]);
	else
		value[0] |= stm[at++];

	if (value[0] < helper::u16_surrogate_min || value[0] > helper::u16_surrogate_max)
	{
		value.count = 1;
		return value;
	}

	if (value[0] < helper::u16_lo_surrogate || value[0] > helper::u16_lo_surrogate_end)
		return helper::not_defined<utf16_t>();

	value[1] = stm[at++];
	if (is_big)
		value[1] = (value[1] << 8 | stm[at]);
	else
		value[1] |= stm[at];

	if (value[1] < helper::u16_hi_surrogate || value[1] > helper::u16_hi_surrogate_end)
		return helper::not_defined<utf16_t>();

	return value;
}

inline cs_int32 unicode::get_utf16_size(const cu16_t& cp)
{
	if (cp < helper::u16_surrogate_min && cp > helper::u16_surrogate_max) return 1;
	if (cp >= helper::u16_lo_surrogate && cp <= helper::u16_lo_surrogate_end) return 2;

	return helper::invalid;
}

inline bool unicode::in_unicode_range(const utf16_t& cp)
{
	return to_utf32(cp) <= helper::max_unicode_cp;
}

inline bool unicode::is_valid_seq(const utf16_t& cp)
{
	if (cp.count == 0 || cp.count > utf16_t::max_units) return false;

	if (cp.count == 1)
	{
		if (cp[0] < helper::u16_surrogate_min || cp[0] > helper::u16_surrogate_max) return true;
		return false;
	}

	return 
		((cp[0] >= helper::u16_lo_surrogate && cp[0] <= helper::u16_lo_surrogate_end) &&
		(cp[1] >= helper::u16_hi_surrogate || cp[1] <= helper::u16_hi_surrogate_end));
}

inline bool unicode::is_utf16_reserved(const utf8_t& cp)
{
	return is_utf16_reserved( to_utf32(cp) );
}

inline bool unicode::is_utf16_reserved(const utf32_t& cp)
{
	return cp >= helper::u16_surrogate_min && cp <= helper::u16_surrogate_max;
}
